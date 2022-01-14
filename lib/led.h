//-------| lib/led.h |-------//
#ifndef	LED_H
#define	LED_H 


#include <unistd.h> // usleep()

#define FPGA_LED 0x12400000//LED의 physical address


unsigned short *LED;


#endif
