#include "include/crypto.h"

bool is_valid(const char c, int* table);

bool is_valid(const char c, int* table) {
    if (table[c] == 0)
        return false;
    return true;
}

ssize_t base64_encode(char * res, const char * data) {
    // base64 code table
    char base64_table[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // 计算经过base64编码后的字符串长度
    int res_len, str_len = strlen(data);
    if (str_len % 3 == 0) {
        res_len = str_len / 3 * 4;
    } else {
        res_len = (str_len / 3 + 1) * 4;
    }
    res[res_len] = '\0';

    // 以3个8位字符为一组进行编码
    int i, j;
    for (i = 0, j = 0; i < res_len - 2; j += 3, i += 4) {
        res[i] = base64_table[data[j] >> 2];                                     // 取出第一个字符的前6位并找出对应的结果字符
        res[i + 1] = base64_table[(data[j] & 0x3) << 4 | (data[j + 1] >> 4)];     // 将第一个字符的后位与第二个字符的前4位进行组合并找到对应的结果字符
        res[i + 2] = base64_table[(data[j + 1] & 0xf) << 2 | (data[j + 2] >> 6)]; // 将第二个字符的后4位与第三个字符的前2位组合并找出对应的结果字符
        res[i + 3] = base64_table[data[j + 2] & 0x3f];                           // 取出第三个字符的后6位并找出结果字符
    }

    if (str_len % 3 == 1) {
        res[i - 2] = '=';
        res[i - 1] = '=';
    } else if (str_len % 3 == 2) {
        res[i - 1] = '=';
    }

    return res_len;
}

ssize_t base64_decode(char * res, const char * data) {
    // 根据base64表，以字符找到对应的十进制数据
    int table[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 62, 0, 0, 0,
        63, 52, 53, 54, 55, 56, 57, 58,
        59, 60, 61, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
        13, 14, 15, 16, 17, 18, 19, 20, 21,
        22, 23, 24, 25, 0, 0, 0, 0, 0, 0, 26,
        27, 28, 29, 30, 31, 32, 33, 34, 35,
        36, 37, 38, 39, 40, 41, 42, 43, 44,
        45, 46, 47, 48, 49, 50, 51
    };

    int res_len, str_len = strlen(data);
    if (str_len % 4 != 0) {
        return 0;
    }
    if (strstr(data, "==")) {
        res_len = str_len / 4 * 3 - 2;
    }
    else if (strstr(data, "=")) {
        res_len = str_len / 4 * 3 - 1;
    } else {
        res_len = str_len / 4 * 3;
    }
    res[res_len] = '\0';

    // 以4个字符为一位进行解码
    int i, j;
    for (i = 0, j = 0; j <= str_len; j += 3, i += 4) {
        if ( !is_valid(data[i], table) || !is_valid(data[i+1], table) || !is_valid(data[i+2], table) ) {
            strcpy(res, "Error decode format!");
            return strlen(res);
        }
        res[j] = ((char)table[data[i]]) << 2 | (((char)table[data[i + 1]]) >> 4);           // 取出第一个字符对应base64表的十进制数的前6位与第二个字符对应base64表的十进制数的后2位进行组合
        res[j + 1] = (((char)table[data[i + 1]]) << 4) | (((char)table[data[i + 2]]) >> 2); // 取出第二个字符对应base64表的十进制数的后4位与第三个字符对应bas464表的十进制数的后4位进行组合
        res[j + 2] = (((char)table[data[i + 2]]) << 6) | ((char)table[data[i + 3]]);        // 取出第三个字符对应base64表的十进制数的后2位与第4个字符进行组合
    }

    return res_len;
}

EXPORT_SYMBOL(base64_encode);
EXPORT_SYMBOL(base64_decode);
