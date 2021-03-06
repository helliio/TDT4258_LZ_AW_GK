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
    
    lisa_gikk_til_skolen();
    enable_sleep_on_exit();

    enable_deep_sleep();
    sleep();
    return 0;
}