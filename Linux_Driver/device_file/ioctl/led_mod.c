#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/uaccess.h>   
#include <linux/slab.h>
#include <linux/string.h>

MODULE_AUTHOR("PHONGLT9");
MODULE_LICENSE("GPL");
MODULE_VERSION("1.0");

/*define MUX*/
#define MUX         0x020E0078
#define GPIO1_IO25  0x05

/*define GPIO reg*/
#define GPIO_BASE 0x0209C000
#define OFFSET_GPIO1_DR     0x00
#define OFFSET_GPIO1_GDIR   0x04

#define GPIO_INPUT  0
#define GPIO_OUTPUT 1
#define LED_PIN     25

#define MAGIC_NO    100
#define ON  _IOW(MAGIC_NO, 0, char*)
#define OFF _IOW(MAGIC_NO, 1, char*)

static void __iomem *io;
static void __iomem *gpio;
static unsigned long temp;

struct _vchar_drv {
    dev_t dev_numb;
    struct class *dev_class;
    struct device *dev;
    struct cdev *my_cdev;
    int count;
}vchar_drv;

static int dev_open(struct inode *, struct file *);
static int dev_close(struct inode *, struct file *);
static long dev_ioctl(struct file *, unsigned int, unsigned long);

static void setup_led(void);
static int led_on(void);
static int led_off(void);

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = dev_open,
    .release = dev_close,
    .unlocked_ioctl = dev_ioctl,
};

int led_off()
{
    /*turn off led*/
	temp = ioread32(io + OFFSET_GPIO1_DR);
	temp &= ~( 1 << LED_PIN);
	iowrite32(temp , (io +OFFSET_GPIO1_DR));
    return 0;
}

int led_on()
{
    /*turn on led*/
	temp = ioread32(io + OFFSET_GPIO1_DR);
	temp |= ( 1 << LED_PIN);
	iowrite32(temp , (io +OFFSET_GPIO1_DR));
    return 1;
}

void setup_led()
{
    /*set up mux -- enable GPIO1*/
    gpio = ioremap(MUX, 0x100);
    if(gpio == NULL)
        pr_alert("fail map base address\n");

    temp = ioread32(gpio);
    temp = temp & (~GPIO1_IO25);
    temp = temp | ( GPIO1_IO25);
    iowrite32(temp, gpio);

    /*set up gpio INPUT - OUTPUT*/
    io = ioremap(GPIO_BASE, 0x100);
    if(io == NULL)
        pr_alert("fail map base address\n");

    temp = ioread32(io + OFFSET_GPIO1_GDIR);
    temp = temp | (GPIO_OUTPUT << LED_PIN);
    iowrite32(temp, io + OFFSET_GPIO1_GDIR);
}

static int dev_open(struct inode *i_node, struct file *file_p)
{
    vchar_drv.count++;
    printk("Handle open : %d\n", vchar_drv.count);
    return 0;
}

static int dev_close(struct inode *i_node, struct file *file_p)
{
    printk("Handle close\n");
    return 0;
}

static long dev_ioctl(struct file * filep, unsigned int cmd, unsigned long arg)
{
    switch(cmd) {
        case ON:
            printk("LED ON\n");
            setup_led();
            led_on();
            break;
        case OFF:
            printk("LED OFF\n");
            setup_led();
            led_off();
            break;
        default :
            printk("Invalid cmd\n");
    }
    return 0;
}

static int __init vchar_drv_init(void)
{
    int ret = 0;
    /* Init device number */
    vchar_drv.dev_numb = 0;
    ret = alloc_chrdev_region(&vchar_drv.dev_numb, 0, 1, "vchar_device");
    if(ret < 0) {
        printk("Failed to register device number\n");
        goto failed_register_dev_numb;
    }
    printk("MAJOR : %d, MINOR : %d", MAJOR(vchar_drv.dev_numb), MINOR(vchar_drv.dev_numb));

    /* Create device file */
    vchar_drv.dev_class = class_create(THIS_MODULE, "class_vchar_dev_led");
    if(vchar_drv.dev_class == NULL) {
        printk("Failed to create a device class\n");
        goto failed_create_dev_class;
    }

    vchar_drv.dev = device_create(vchar_drv.dev_class, NULL, vchar_drv.dev_numb, NULL, "ioctl_led_dev");
    if(IS_ERR(vchar_drv.dev)) {
        printk("Failed to create a device\n");
        goto failed_create_dev;
    }

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
    device_destroy(vchar_drv.dev_class, vchar_drv.dev_numb);
    class_destroy(vchar_drv.dev_class);
    unregister_chrdev_region(vchar_drv.dev_numb, 1);
    cdev_del(vchar_drv.my_cdev);

    printk("Exit vchar driver\n");
}

module_init(vchar_drv_init);
module_exit(vchar_drv_exit);

