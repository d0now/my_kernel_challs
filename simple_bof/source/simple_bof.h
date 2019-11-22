/*
 * super_ez_kern.h
 * d0now@stealien
*/

#ifndef _SUPER_EZ_KERN_H_
#define _SUPER_EZ_KERN_H_

/* Includes */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <linux/device.h>
#include <linux/slab.h>
#include <asm/current.h>
#include <linux/uaccess.h>
#include <linux/ioctl.h>
#include <linux/string.h>
#include <linux/fcntl.h>
#include <linux/syscalls.h>
#include <linux/unistd.h>
#include <linux/file.h>

/* driver name */
#define DRIVER_NAME "chardev"

/*
 * DB Settings
*/

#define DB_PATH "/tmp/database.bin"

/* global variables */
static const unsigned int MINOR_BASE = 0;
static const unsigned int MINOR_NUM  = 1;
static unsigned int sbof_major;
static struct cdev sbof_cdev;
static struct class *sbof_class = NULL;
uint32_t global_number;

/* Function pre-defines */
static int sbof_open(struct inode *, struct file *);
static int sbof_release(struct inode *, struct file *);
static ssize_t sbof_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos);
static ssize_t sbof_write(struct file *, const char *, size_t, loff_t *);

char global_buf[0x1000];
size_t global_buf_size;

#endif