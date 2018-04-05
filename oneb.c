#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define MAJOR_NUMBER 61

/* declare function prototypes */
int onebyte_open(struct inode *inode, struct file *filep);
int onebyte_release(struct inode *inode, struct file *filep);
ssize_t onebyte_read(struct file *filep, char *buf, size_t count, loff_t *f_pos); 
ssize_t onebyte_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos);
static void onebyte_exit(void);

/*definition of file_operation structure */ 
struct file_operations onebyte_fops = {
    read:    onebyte_read,
    write:   onebyte_write,
    open:    onebyte_open,
    release: onebyte_release
};

char *onebyte_data = NULL;

int onebyte_open(struct inode *inode, struct file *filep)
{
    return 0;
}

int onebyte_release(struct inode *inode, struct file *filep);
{
    return 0;
}

ssize_t onebyte_read(struct file *filep, char *buf, size_t count, loff_t *f_pos); 
{
    return 0;
}

ssize_t onebyte_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos);
{
    return 0;
}

static void onebyte_exit(void);
{
    return;
}

MODULE_LICENSE("GPL");
module_init(onebyte_init);
module_exit(onebyte_exit);
