#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "defines.h"

/* Declaration of peripheral setup functions */
void setupTimer(uint32_t period);
void setupDAC();
void setupNVIC();

/* Your code will start executing here */
int main(void) 
{  
    /* Call the peripheral setup functions */

    setupDAC();
    setupTimer(sample_period);
    setupNVIC();
    setupGPIO();
    
    lisa_gikk_til_skolen();

    sleep();
    return 0;
}

void setupNVIC()
{
    * ISER0 |= 1<<1;
    * ISER0 |= 1<<11;
    * ISER0 |= 1<<12;   
}