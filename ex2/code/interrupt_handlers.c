#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "sound.h"

void interrupt_handler();
/* TIMER1 interrupt handler */

int     base_sample_period  = 2500;
int     sample_period       = 2500;
bool    trigger_sound       = false;


void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  
    *TIMER1_IFC = 1; 
    if (trigger_sound) play_piano_sound(); 
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

    * GPIO_IFC = 0xff;

    uint32_t gipi_button_pushed = *GPIO_PC_DIN;
    
    // Mask to see if a button is pushed
    uint32_t sw1 = gipi_button_pushed & 0x01;
    uint32_t sw2 = gipi_button_pushed & 0x02;
    uint32_t sw3 = gipi_button_pushed & 0x04;
    uint32_t sw4 = gipi_button_pushed & 0x08;
    uint32_t sw5 = gipi_button_pushed & 0x10;
    uint32_t sw6 = gipi_button_pushed & 0x20;
    uint32_t sw7 = gipi_button_pushed & 0x40;
    uint32_t sw8 = gipi_button_pushed & 0x80;

    trigger_sound = true;
    piano_position = 0;

    enum TONE tone;

    if      (!sw1)  tone = C;
    else if (!sw2)  tone = D;
    else if (!sw3)  tone = E;
    else if (!sw4)  tone = F;
    else if (!sw5)  tone = G;
    else if (!sw6)  tone = A;
    else if (!sw7)  tone = B;
    else if (!sw8)  tone = C2;

    set_tone(tone);
}


