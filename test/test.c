#include <stdio.h>
#include <string.h>

#define FUNCLEN 1000
#define ENOMEM 1

int is_split(const char c);
int is_space(const char c);
int readfunc(char * funcname, const char * user_buffer, size_t length);


int main() {
    char funcname[FUNCLEN];
    char ubuf[] = "base64   encrypt  6667         1111      \n  66677\n";
    unsigned long end = readfunc(funcname, ubuf, strlen(ubuf));
    if ( end < 0) {
        puts("ERROR");
        return 0;
    } else {
        printf("len:%ld\n", end);
    }
    puts(funcname);
    printf("%ld\n", strlen(funcname));
}

int is_split(const char c) {
    return c == '\n' || c == '\r' || c == '\0';
}

int is_space(const char c) {
    return c == ' ' || c == '\t';
}

int readfunc(char * funcname, const char * user_buffer, size_t length) {
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

        // Clear the middle space
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