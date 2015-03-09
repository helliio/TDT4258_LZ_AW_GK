#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "defines.h"

void setupDAC()
{
    *CMU_HFPERCLKEN0    |=  1 << 17;
    *DAC0_CTRL          =   0x50010;
    *DAC0_CH0CTRL       =   1;
    *DAC0_CH1CTRL       =   1;
}

void setupNVIC()
{
    * ISER0 |= 1<<1;
    * ISER0 |= 1<<11;
    * ISER0 |= 1<<12;   
}

void setupGPIO()
{
    *CMU_HFPERCLKEN0   |=   CMU2_HFPERCLKEN0_GPIO; /* enable GPIO clock*/
    *GPIO_PA_CTRL       =   2;  /* set high drive strength */
    *GPIO_PA_MODEH      =   0x55555555; /* set pins A8-15 as output */
    *GPIO_PA_DOUT       =   0x0000; /* turn on LEDs D1-D8 (LEDs are active low) */
    *GPIO_PC_MODEL      =   0x33333333;
    *GPIO_PC_DOUT       =   0xff;
    *GPIO_EXTIPSELL     =   0x22222222;
    *GPIO_EXTIFALL      =   0xff;
    *GPIO_IEN           =   0xff;
}

/* function to setup the timer */
void setupTimer(uint16_t period)
{
    *CMU_HFPERCLKEN0 |= 1<<6;
    *TIMER1_TOP = period;
    *TIMER1_IEN = 1;
    *TIMER1_CMD = 1;
}


void setup_energy_saving()
{
	*SCR = SCR_SLEEPDEEP | SCR_SLEEPONEXIT;
}