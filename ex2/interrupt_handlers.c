#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"

/* TIMER1 interrupt handler */
int sound = 100;
void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
    if (sound < 1000){
        sound += 100;
    }
    if (sound >= 1000){
        sound = 100;
    }  
    *TIMER1_IFC = 1;    
    *DAC0_CH0DATA = sound;
    *DAC0_CH1DATA = sound;
    
    

    /*
    TODO feed new samples to the DAC
    remember to clear the pending interrupt by writing 1 to TIMER1_IFC
    */  
}

/* GPIO even pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_EVEN_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
}

/* GPIO odd pin interrupt handler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    /* TODO handle button pressed event, remember to clear pending interrupt */
}
