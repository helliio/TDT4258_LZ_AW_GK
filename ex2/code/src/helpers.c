#include <stdbool.h>
#include "efm32gg.h"

void sleep()
{
	while(true)
	    __asm("wfi");
}

void gpio_clear_interrupt(){ * GPIO_IFC = 0xff;}

void timer1_clear_interrupt(){ * TIMER1_IFC = 1;}