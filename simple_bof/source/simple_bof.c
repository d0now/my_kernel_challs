/*
 * simple_bof.c
 * d0now@pwnsuky
*/

/* Include header. */
#include "simple_bof.h"

MODULE_LICENSE("GPL");

struct file_operations sbof_fops = {
    .open    = sbof_open,
    .release = sbof_release,
    .read    = sbof_read,
    .write   = sbof_write,
};

/* Initialize module */
static int __init sbof_init(void) {

    int minor = 0;
    dev_t dev;

    if (alloc_chrdev_region(&dev, MINOR_BASE, MINOR_NUM, DRIVER_NAME) != 0)
        goto err;

    sbof_major = MAJOR(dev);
    dev          = MKDEV(sbof_major, MINOR_BASE);

    cdev_init(&sbof_cdev, &sbof_fops);
    sbof_cdev.owner = THIS_MODULE;

    if (cdev_add(&sbof_cdev, dev, MINOR_NUM) != 0) {
        unregister_chrdev_region(dev, MINOR_NUM);
        goto err;
    }

    sbof_class = class_create(THIS_MODULE, "sbofdev");
    if (IS_ERR(sbof_class)) {
        cdev_del(&sbof_cdev);
        unregister_chrdev_region(dev, MINOR_NUM);
        return -1;
    }

    device_create(sbof_class, NULL, MKDEV(sbof_major, minor), NULL, "sbofdev%d", minor);

    global_number = 0;

    printk(KERN_INFO "simple_bof loaded\n");
    return 0;

err:
    printk(KERN_INFO "simple_bof not loaded.\n");
    return 0;
}

/* Cleanup module */
static void __exit sbof_cleanup(void) {

    int minor = 0;
    dev_t dev = MKDEV(sbof_major, MINOR_BASE);

    device_destroy(sbof_class, MKDEV(sbof_major, minor));
    class_destroy(sbof_class);
    cdev_del(&sbof_cdev);
    unregister_chrdev_region(dev, MINOR_NUM);

    printk(KERN_INFO "simple_bof removed.\n");
    return;
}
 
static int sbof_open(struct inode *inode, struct file *file) {
    printk(KERN_INFO "sbof_open() called.\n");
    return 0;
}

static int sbof_release(struct inode *inode, struct file *file) {

    char buf[0x100];

    printk(KERN_INFO "sbof_release() called.\n");

    memcpy(buf, global_buf, global_buf_size);
    printk(KERN_INFO "buf = \"%10s\"\n", buf);

    return 0;
}

static ssize_t sbof_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos) {

    printk(KERN_INFO "sbof_read() called.\n");

    return 0;
}

static ssize_t sbof_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos) {

    printk(KERN_INFO "sbof_write() called.\n");

    copy_from_user(global_buf, buf, count);
    global_buf_size = count;

    return 0;
}

module_init(sbof_init);
module_exit(sbof_cleanup);