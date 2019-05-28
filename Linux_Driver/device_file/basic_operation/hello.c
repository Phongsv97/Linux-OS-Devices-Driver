#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/reboot.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/string.h>

MODULE_AUTHOR("PHONGLT9");
MODULE_LICENSE("GPL");
MODULE_VERSION("1");

static struct class *class_name;
static struct device *device_name;
static struct cdev my_cdev;
static dev_t dev;

static int dev_open(struct inode *, struct file *);
static int dev_close(struct inode *, struct file *);

static const struct file_operations fops = {
	.open = dev_open,
	.release = dev_close,
};


static int dev_open(struct inode *inodep, struct file *filep)
{
	pr_info("open is called\n");
	return 0;
}

static int dev_close(struct inode *inodep, struct file *filep)
{
	pr_info("close is called\n");
	return 0;
}

static int __init exam_init(void)
{
	int ret;

	ret = alloc_chrdev_region(&dev, 6, 1, "hello");
	if (ret) {
		pr_info("Can not register major number\n");
		return ret;
	}
	pr_info("Register successfully major no is %d\n", MAJOR(dev));

	cdev_init(&my_cdev, &fops);
	my_cdev.owner = THIS_MODULE;
	my_cdev.dev = dev;

	ret = cdev_add(&my_cdev, dev, 1);

	if (ret < 0) {
		pr_info("cdev_add error\n");
		return ret;
	}

	class_name = class_create(THIS_MODULE, "hello");
	if (IS_ERR(class_name)) {
		pr_info("create class failed\n");
		return PTR_ERR(class_name);
	}
	pr_info("create successfully class\n");

	device_name = device_create(class_name, NULL, dev, NULL, "ex_hello");
	if (IS_ERR(device_name)) {
		pr_info("Create device failed\n");
		return PTR_ERR(device_name);
	}
	pr_info("create device success\n");

	return 0;
}

static void __exit exam_exit(void)
{
	pr_info("goodbye\n");
	cdev_del(&my_cdev);
	device_destroy(class_name, dev);
	class_destroy(class_name);
	unregister_chrdev_region(dev, 1);
}

module_init(exam_init);
module_exit(exam_exit);
