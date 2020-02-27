#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define MAGIC_NO    100
#define CMD1  _IOW(MAGIC_NO, 0, char*)
#define CMD2 _IOW(MAGIC_NO, 1, char*)
 
#define MAX_SIZE    50

MODULE_AUTHOR("PHONGLT9");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

char *kernel_buff;

struct _vchar_drv {
    dev_t dev_numb;
    struct class *dev_class;
    struct device *dev;
    struct cdev *my_cdev;
}vchar_drv;

static int dev_open(struct inode *i_node, struct file *file_p)
{
    printk("Handle open\n");
    return 0;
}

static int dev_close(struct inode *i_node, struct file *file_p)
{
    printk("Handle close\n");
    return 0;

}

static ssize_t dev_read(struct file *filp, char __user *user_buff, size_t len, loff_t *off)
{
	printk("Handle read event start from %lld, %zu bytes\n", *off, len);
	
	if(copy_to_user(user_buff, kernel_buff, MAX_SIZE))
		return -EFAULT;
	*off += len;

	return len;
}

static ssize_t dev_write(struct file *filp, const char __user *user_buff, size_t len, loff_t *off)
{
	printk("Handle write event start from %lld, %zu bytes\n", *off, len);

	if(copy_from_user(kernel_buff, user_buff, len))
		return -EFAULT;
	
	*off += len;

	return len;
}


static struct file_operations fops = {
    .owner 	= THIS_MODULE,
    .open 	= dev_open,
    .release 	= dev_close,
    .read	= dev_read,
    .write 	= dev_write,
};

static int __init vchar_drv_init(void)
{
    int ret = 0;
    /* Init device number */
    vchar_drv.dev_numb = 0;
    ret = alloc_chrdev_region(&vchar_drv.dev_numb, 0, 1, "device_numb");
    if(ret < 0) {
        printk("Failed to register device number\n");
        goto failed_register_dev_numb;
    }
    printk("MAJOR : %d, MINOR : %d", MAJOR(vchar_drv.dev_numb), MINOR(vchar_drv.dev_numb));

    /* Create device file */
    vchar_drv.dev_class = class_create(THIS_MODULE, "class_vchar_dev");
    if(vchar_drv.dev_class == NULL) {
        printk("Failed to create a device class\n");
        goto failed_create_dev_class;
    }

    vchar_drv.dev = device_create(vchar_drv.dev_class, NULL, vchar_drv.dev_numb, NULL, "vchar_device_super");
    if(IS_ERR(vchar_drv.dev)) {
        printk("Failed to create a device\n");
        goto failed_create_dev;
    }
    /* Alocation kernel buffer*/
    kernel_buff = kzalloc(MAX_SIZE, GFP_KERNEL);
    if(kernel_buff == NULL)
	    return -1;

    /* Register entry point*/
    vchar_drv.my_cdev = cdev_alloc();
    cdev_init(vchar_drv.my_cdev, &fops);
    ret = cdev_add(vchar_drv.my_cdev, vchar_drv.dev_numb, 1);
    if(ret < 0){
        printk("failed add charater device to the system\n");
        goto failed_allocate_cdev;
    }

    printk("Initialize vchar driver successfully\n");

    failed_register_dev_numb : 
        return ret;
    failed_create_dev_class :
        unregister_chrdev_region(vchar_drv.dev_numb, 1);
    failed_create_dev :
        class_destroy(vchar_drv.dev_class);
    failed_allocate_cdev :
        printk("do something\n");
    return 0;
}

static void __exit vchar_drv_exit(void)
{
    /* Device destroy */
    device_destroy(vchar_drv.dev_class, vchar_drv.dev_numb);
    /* Class destroy */
    class_destroy(vchar_drv.dev_class);
    /* Unregister devive numb */
    unregister_chrdev_region(vchar_drv.dev_numb, 1);
    /* Delete device */
    cdev_del(vchar_drv.my_cdev);
    /* Free kernel buff */
    kfree(kernel_buff);

    printk("Exit vchar driver\n");
}

module_init(vchar_drv_init);
module_exit(vchar_drv_exit);

