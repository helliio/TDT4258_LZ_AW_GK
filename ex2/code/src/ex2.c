#include <stdint.h>
#include <stdbool.h>

#include "efm32gg.h"
#include "defines.h"

int main(void) 
{  
    setupDAC();
    setupTimer(sample_period);
    setupNVIC();
    setupGPIO();
    setup_energy_saving();
    
    lisa_gikk_til_skolen();

    sleep();
    return 0;
}

