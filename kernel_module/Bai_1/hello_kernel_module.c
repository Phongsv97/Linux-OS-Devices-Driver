/*

hello world kernel module 

*/

#include <linux/module.h>
#include <linux/kernel.h>

#define DRIVER_AUTHOR   "LE TRONG PHONG <phongxxx@gmail.com>"
#define DRIVER_DESC     "Hello world kernel module"


static int __init init_hello(void)
{
    printk("Hello kernel module \n");
    return 0;
}

static void __exit exit_hello(void)
{
    printk("Goodby kernel module \n");
}

module_init(init_hello);
module_exit(exit_hello);

MODULE_LICENSE("PhongLT9");
MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_SUPPORTED_DEVICE("test");
