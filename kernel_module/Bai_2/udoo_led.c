#include <stdio.h>
#include <sys/module.h>
#include <linux/kernel.h>
#include <linux/io.h>

#define DRIVER_DESC     "UDOO GPIO BLINK LED PIN25"
#define DRIVER_AUTHOR   "Phong LT9 <phongxxx@gmail.com>"

#define GPIO_BASE 0x0209C000h

#define OFFSET_GPIO1_DR     0x00h
#define OFFSET_GPIO1_GDIR   0x04h

#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

#define LED_PIN 25

static void __iomem *io;
static unsigned long temp;


static int __init init_led(void)
{
    pr_info("hello kernel \n");

    io = ioremap(GPIO_BASE, 0x100);

    if(io == NULL){
        pr_alert("fail map base address\n");
        return -1;
    }

    /*write config mod for pin 25*/
    temp = ioread32(io + GPIO1_GDIR_OFFSET);
    pr_info("before config reg : %ld", temp);

    /*set config mode output for pa17*/	
	temp = temp & (~(1 << LED_PIN));
	
    /**/
	temp = iowrite32(temp, (io + GPIO1_GDIR_OFFSET)); 
	pr_info("after config reg %ld\n", temp);

	/*turn on led*/
	temp = ioread32(io + OFFSET_GPIO1_DR);
	pr_info("before data reg %ld\n", temp);
	temp |= ( 1 << LED_PIN);
	iowrite32(temp , (io +OFFSET_GPIO1_DR));
	pr_info("after data reg %ld\n", temp);

    return 0;
}

static void __exit exit_led(void)
{
    /*turn off led*/
	temp = ioread32(io + OFFSET_GPIO1_DR);
	temp &= ~( 1 << LED_PIN);
	iowrite32(temp , (io +OFFSET_GPIO1_DR));
	pr_info("exit module");	
}

module_init(init_led);
module_exit(exit_led);

MODULE_AUTHOR(DRIVER_AUTHOR);
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("PhongLT9");
MODULE_SUPPORTED_DEVICE("Udoo NEo");