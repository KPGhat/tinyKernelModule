#include "include/util.h"

bool is_split(const char c);
bool is_space(const char c);

bool is_split(const char c) {
    return c == '\n' || c == '\r' || c == '\0' || c == '|';
}

bool is_space(const char c) {
    return c == ' ' || c == '\t';
}

void init_func(void) {
    func[0] = base64_encode;
    func[1] = base64_decode;
    func[2] = easter_egg;

    funclist[0] = "base64 encode";
    funclist[1] = "base64 decode";
    funclist[2] = "easter egg";
}

ssize_t readfunc(char * funcname, const char * user_buffer, size_t length) {
    size_t start, end, funclen, funcstart;
    
    memset(funcname, 0, sizeof(char) * FUNCLEN);
    start = end = funclen = funcstart = 0;

    // Clear the start space
    while ( is_space(user_buffer[start]) ) {
        start++;
    }

    end = start;
    while ( end <= length && ! is_split(user_buffer[end]) ) {
        if (funclen >= FUNCLEN) 
            return -ENOMEM;

        // Compress the middle space
        if (is_space(user_buffer[end]) ) {
            strncpy(funcname + funcstart, user_buffer + start, end - start + 1);
            start = end;
            funclen++;
            funcstart = funclen;
            while ( is_space(user_buffer[++start]) );
            end = start;
        } else {
            end++;
            funclen++;
        }
    }
    strncpy(funcname + funcstart, user_buffer + start, funclen - funcstart);

    // Clear the end space
    if ( is_space(funcname[funclen-1]) ) {
        funcname[--funclen] = '\0';
    }
    return end;
}

ssize_t readdata(char * data, const char * user_buffer, size_t length) {
    size_t start, end, datalen;

    memset(data, 0, sizeof(char) * DATALEN);
    start = end = datalen = 0;

    //data can be any format
    while (end < length) {
        if (datalen >= DATALEN)
            return -ENOMEM;
        end++;
        datalen++;
    }
    strncpy(data, user_buffer + start, datalen);
    return datalen;
}

ssize_t easter_egg(char * res, const char * data) {
    strcpy(res, "Wait to finish");
    return true;
}

EXPORT_SYMBOL(init_func);
EXPORT_SYMBOL(readfunc);
EXPORT_SYMBOL(readdata);
EXPORT_SYMBOL(easter_egg);
