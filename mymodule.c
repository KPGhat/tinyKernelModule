#include "include/mymodule.h"

static struct proc_ops fops = {
    .proc_open = my_open,
    .proc_release = my_release,
    .proc_read = my_read,
    .proc_write = my_write
};

static ssize_t my_read(struct file* file, char __user* user_buffer, size_t length, loff_t* offset) {
    printk(KERN_INFO "[+] Calling our very own custom module introduction.");
    // printk(KERN_INFO "[+] result length %d.", result_len);
    // printk(KERN_INFO "[+] result content %s.", result);
    if (*offset > 0)
        return 0;
    
    int result_len = strlen(result);
    if ( result_len == 0 ) {
        strcpy(result, USAGE);
    }

    printk(KERN_INFO "[+] Reading result.");
    if ( copy_to_user(user_buffer, result, result_len) )
        return -EFAULT;
    *offset = result_len;
    return result_len;
}

static ssize_t my_write(struct file* file, const char __user* user_buffer, size_t length, loff_t* offset) {
    char buffer[BUFSIZE];
    ssize_t retlen;
    if(*offset > 0 || length > BUFSIZE)
		return -EFAULT;
    if ( copy_from_user(buffer, user_buffer, length) )
        return -EFAULT;
    int buffer_len = strlen(buffer);
    printk(KERN_INFO "[+] user_buffer %s.", buffer);

    if ( ( retlen = readfunc(funcname, buffer, length) ) < 0 )
        return retlen;
    printk(KERN_INFO "[+] funcname %s.", funcname);
    
    if ( (retlen = readdata(data, buffer + retlen + 1, length - retlen - 1)) < 0)
        return retlen;
    
    printk(KERN_INFO "[+] data %s.", data);

    int i;
    for (i = 0; i < FUNCNUM; i++) {
        if ( strcmp(funcname, funclist[i]) == 0 ) {
            printk(KERN_INFO "[+] Calling our very own module function %s.", funcname);
            memset(result, 0, sizeof(char) * RESULTLEN);
            retlen = (*func[i])(result, data);
            result[retlen++] = '\n';
            result[retlen] = '\0';
            break;
        }
    }
    *offset = buffer_len;
    return buffer_len;
}

static int my_open(struct inode* inode, struct file* file) {
    if (fileLock) {
 		return -EBUSY;
 	}
 	fileLock = true;
 	try_module_get(THIS_MODULE);
 	return 0;
}

static int my_release(struct inode *inode, struct file *file) {
 	/* Decrement the open counter and usage count. Without this, the module would not unload. */
 	fileLock = false;
 	module_put(THIS_MODULE);
 	return 0;
}



// Custom init and exit methods
static int __init mymodule_init(void) {
    init_func();
    proc_entry = proc_create("modulecrypto", 0666, NULL, &fops);
    printk(KERN_INFO "[+] Module loaded.");
    return 0;
}

static void __exit mymodule_exit(void) {
    proc_remove(proc_entry);
    printk(KERN_INFO "[-] Module removed.");
}

module_init(mymodule_init);
module_exit(mymodule_exit);