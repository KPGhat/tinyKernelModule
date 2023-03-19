#ifndef _MYMODULE_H
#define _MYMODULE_H

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

#include "util.h"

#define BUFSIZE 2048

MODULE_LICENSE("GPL");
MODULE_AUTHOR("A Student");
MODULE_DESCRIPTION("A simple example Linux module.");
MODULE_VERSION("0.01");

static struct proc_dir_entry* proc_entry;
static bool fileLock = false;

char data[DATALEN] = {0};
char funcname[FUNCLEN];
char * funclist[FUNCNUM];
ssize_t (* func[FUNCNUM])(char *, const char *);
char result[RESULTLEN] = {0};

static const char USAGE[] = "Usage:\n\t\twrite data to the proc entry we make\nContent format:\n\t\tfunction to call (Existing function: base64 encode and decode, easter egg...)\n\t\tdata to be processed\nFor example:\n\t\tbase64 encode|data to be encode\n";

static int my_open(struct inode *, struct file *);
static int my_release(struct inode *, struct file *);
static ssize_t my_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t my_write(struct file *, const char __user *, size_t, loff_t *);

#endif