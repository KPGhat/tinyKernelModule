#ifndef _UTIL_H
#define _UTIL_H

#include <linux/string.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/init.h>

#include "crypto.h"
#include "modvar.h"

void init_func(void);
ssize_t readfunc(char * funcname, const char * user_buffer, size_t length);
ssize_t readdata(char * data, const char * user_buffer, size_t length);
ssize_t easter_egg(char * res, const char * data);

#endif