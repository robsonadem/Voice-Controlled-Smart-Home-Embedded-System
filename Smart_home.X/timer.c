#include <p32xxxx.h>

#include "timer.h"

#define CLOCK_FREQ 40000000

void timer_init()
{
    T1CON = 0x8030;	// Enable Timer 1.  Prescaler = 256
    TMR1 = 0;		// Reset.
}

uint16_t timer_read()
{
    return(TMR1);
}

uint16_t timer_ms_elapsed(uint16_t t1, uint16_t t2)
{
    if (t2 > t1)
    {
        return((uint32_t)(t2 - t1)*256/(uint32_t)(CLOCK_FREQ/1000));
    }
    else
    {
        return((uint32_t)((uint32_t)65536 + t2 - t1)*256/(uint32_t)(CLOCK_FREQ/1000));
    }
  
}
void delay_ms(uint32_t time_ms)
{
    uint16_t d;

    TMR1=0;
    d=((uint64_t)40000000*(uint64_t)time_ms)/(uint64_t)256000;
    while(TMR1<d)
    {
        
    }
}
