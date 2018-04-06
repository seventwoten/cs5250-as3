#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

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

int onebyte_release(struct inode *inode, struct file *filep)
{
    return 0;
}

ssize_t onebyte_read(struct file *filep, char *buf, size_t count, loff_t *f_pos)
{
    // if the device has been read before, return 0
    if (*f_pos > 0)
        return 0;

    // copy byte to user space
    if (copy_to_user(buf, onebyte_data, 1) != 0)
        return -EFAULT;

    else
    {
        (*f_pos)++;
        return 1;
    }

    return 0;
}

ssize_t onebyte_write(struct file *filep, const char *buf, size_t count, loff_t *f_pos)
{
    // copy byte from user
    if(count <= 1 && copy_from_user(onebyte_data, buf, count) == 0)
        return count;
    else
        return -EFAULT;

    return 0;
}

static int onebyte_init(void)
{
    int result; 
    // register the device
    result = register_chrdev(MAJOR_NUMBER, "onebyte", &onebyte_fops);
    if (result < 0){
        return result;
    }

    // allocate one byte of memory for storage
    // kmalloc is just like malloc, the second parameter is
    // the type of memory to be allocated. 
    // To release the memory allocated by kmalloc, use kfree. 

    onebyte_data = kmalloc(sizeof(char), GFP_KERNEL);
    if (!onebyte_data){
        onebyte_exit();
        // cannot allocate memory
        // return no memory error, negative signifies a failure
        return -ENOMEM;
    }

    // initialise the value to be X 
    *onebyte_data = 'X';
    printk(KERN_ALERT "This is a onebyte device module\n");

    return 0;
}

static void onebyte_exit(void)
{
    // if the pointer is pointing to something
    if (onebyte_data){
        // free the memory and assign the pointer to NULL
        kfree(onebyte_data);
        onebyte_data = NULL;
    }
    // unregister the device
    unregister_chrdev(MAJOR_NUMBER, "onebyte");
    printk(KERN_ALERT "Onebyte device module is unloaded\n");
}

MODULE_LICENSE("GPL");
module_init(onebyte_init);
module_exit(onebyte_exit);
