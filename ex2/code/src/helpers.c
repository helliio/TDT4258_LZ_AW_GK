#include <stdbool.h>

void sleep()
{
	while(true)
	    __asm("wfi");
}