#ifndef _MODVAR_H
#define _MODVAR_H

#define FUNCNUM 3
#define FUNCLEN 64
#define DATALEN 1024
#define RESULTLEN 1024

extern char data[DATALEN];
extern char funcname[FUNCLEN];
extern char * funclist[FUNCNUM];
extern ssize_t (* func[FUNCNUM])(char *, const char *);
extern char result[RESULTLEN];

#endif
