#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
int sound = 100;
int sound_value = 100;
void interrupt_handler();
/* TIMER1 interrupt handler */

void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
    if (sound < 1000){
        sound += sound_value;
    }
    if (sound >= 1000){
        sound = sound_value;
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
    interrupt_handler();
}

/* GPIO odd pin interrupt handvoid interrupt_handler()ler */
void __attribute__ ((interrupt)) GPIO_ODD_IRQHandler() 
{
    interrupt_handler();
}

void interrupt_handler(){

    *GPIO_IFC = 0xff;
    uint32_t input = *GPIO_PC_DIN;
    uint32_t sw7 = input & 0x40;
    uint32_t sw5 = input & 0x10;
    if (sw7 != 0 && sound_value < 200){
        sound_value += 10;
    }
    if (sw5 != 0 && sound_value > 100){
        sound_value -= 10;
    }
    
}


