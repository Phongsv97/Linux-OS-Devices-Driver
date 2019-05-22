/*
    Despcription :
    - setup GPIO feature for udoo neo board

*/

#ifndef __GPIO_UDOO_NEO__
#define __GPIO_UDOO_NEO__

#define write_reg(addr, value)  *((unsigned long int *)addr) = value)
#define read_reg(addr, mask)    *((unsigned long int *)addr)&mask


#define GPIO_BASE   0x0209C000h
#define GPIO1_DR    (GPIO_BASE + 0x00h)
#define GPIO1_GDIR  (GPIO_BASE + 0x04h)

#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

#define LED_PIN 25  

#endif