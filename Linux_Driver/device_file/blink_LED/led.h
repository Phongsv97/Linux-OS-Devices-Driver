#ifndef __LED__
#define __LED__

/*define MUX*/
#define MUX         0x020E0078
#define GPIO1_IO25  0x05

/*define GPIO reg*/
#define GPIO_BASE 0x0209C000

#define OFFSET_GPIO1_DR     0x00
#define OFFSET_GPIO1_GDIR   0x04

#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

#define LED_PIN 25

void setup_led();
int led_on();
int led_off();

#endif