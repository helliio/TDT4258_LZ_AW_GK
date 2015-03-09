#include <stdbool.h>
#include "efm32gg.h"

#include "defines.h"

void sleep()
{
	while(true)
	    __asm("wfi"); // wait for interupt
}

// Timer is not usable in EM2
void enable_deep_sleep()
{
	// Disable DAC as we cannot use it anyway
	*DAC0_CH0CTRL = 0;
    *DAC0_CH1CTRL = 0;

    *SCR |= SCR_SLEEPDEEP;
}

void disable_deep_sleep()
{
	// Enable DAC
	*DAC0_CH0CTRL = 1;
    *DAC0_CH1CTRL = 1;

    *SCR &=~ SCR_SLEEPDEEP;
}

void enable_sleep_on_exit()
{
	*SCR |= SCR_SLEEPONEXIT;
}


void gpio_clear_interrupt(){ *GPIO_IFC = 0xff;}
void timer1_clear_interrupt(){ *TIMER1_IFC = 1;}