#ifndef _BASE64_H
#define _BASE64_H

#include <linux/module.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/types.h>
  
ssize_t base64_encode(char * res, const char * data);
ssize_t base64_decode(char * res, const char * data);

#endif  
