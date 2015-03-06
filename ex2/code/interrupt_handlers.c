#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "values.h"
#include "drum_sound.h"

int sound = 0;
int sound_value = 0;
void interrupt_handler();
/* TIMER1 interrupt handler */



int i = 0;
int button_pushed = -1;

int * sound_sample_left;

void __attribute__ ((interrupt)) TIMER1_IRQHandler() 
{  

    *TIMER1_IFC = 1; 

    if (button_pushed == 7)
    {
       play_drum_sound(); 
    }
    else
    {
        sound = 0;
    }

    display_power_bar();
}

void display_power_bar()
{
     * GPIO_PA_DOUT = 0xff00 >> (sound * 8 / 0xfff);
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

    uint32_t input = *GPIO_PC_DIN;
    uint32_t sw7 = input & 0x40;
    uint32_t sw5 = input & 0x10;
    if (sw7 == 0){
        button_pushed = 7; 
    }

    // * GPIO_PA_DOUT =  * GPIO_PA_DOUT << 8;
}

void play_drum_sound()
{
    sound = drum_sound[i];
    i++;

    *DAC0_CH0DATA = sound;
    *DAC0_CH1DATA = sound;


    if (i >= lenght_of_drum_sound)
    {
        button_pushed = -1;
        i = 0;
    }

}