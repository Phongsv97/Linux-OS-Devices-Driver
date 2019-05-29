#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <led.h>

static void __iomem *io;
static void __iomem *gpio;
static unsigned long temp;

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
}

void setup_led()
{
    /*set up mux -- enable GPIO1*/
    gpio = ioremap(MUX, 0x100);
    if(gpio == NULL){
        pr_alert("fail map base address\n");
        return -1;
    }  
    temp = ioread32(gpio);
    temp = temp & (~GPIO1_IO25);
    temp = temp | ( GPIO1_IO25);
    iowrite32(temp, gpio);

    /*set up gpio INPUT - OUTPUT*/
    io = ioremap(GPIO_BASE, 0x100);
    if(io == NULL){
        pr_alert("fail map base address\n");
        return -1;
    }
    temp = ioread32(io + OFFSET_GPIO1_GDIR);
    temp = temp | (GPIO_OUTPUT << LED_PIN);
    iowrite32(temp, io + OFFSET_GPIO1_GDIR);
}

