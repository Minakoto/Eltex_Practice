#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#define MSG_LEN 25
#define PROC_ENTRY "entry"

static int len,temp;
static char *msg;
 
ssize_t read_proc(struct file*, char*, size_t, loff_t*);
ssize_t write_proc(struct file*, const char*, size_t, loff_t*);
void create_new_proc_entry(void);
int proc_init (void);
void proc_cleanup(void);


ssize_t read_proc(struct file *filp, char *buf, size_t count, loff_t *offp ) {
    if(count > temp) {
        count = temp;
    }
    temp = temp - count;
    int retval = copy_to_user(buf, msg, count);
    printk("Read result: %d", retval);
    if(count == 0)
        temp = len;
    return count;
}
 
ssize_t write_proc(struct file *filp, const char *buf, size_t count, loff_t *offp) {
    int retval = copy_from_user(msg, buf, count);
    printk("Write result: %d", retval);
    len = count;
    temp = len;
    return count;
}
 
static const struct proc_ops proc_fops = {
    proc_read: read_proc,
    proc_write: write_proc,
};
 
void create_new_proc_entry(void) { //use of void for no arguments is compulsory now
    proc_create(PROC_ENTRY, 0, NULL, &proc_fops);
    msg = kmalloc(MSG_LEN * sizeof(char), GFP_KERNEL);
}

int proc_init (void) {
    create_new_proc_entry();
    return 0;
}
 
void proc_cleanup(void) {
    remove_proc_entry(PROC_ENTRY, NULL);
    kfree(msg);
}
 
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Anisimov Viktor Mikhailovich");
module_init(proc_init);
module_exit(proc_cleanup);