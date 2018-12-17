/*============================================================================
 * timer.h
 *	Header for the timer module.
 *==========================================================================*/

#ifndef _timer_h_
#define _timer_h_

#include <inttypes.h>

void timer_init();
uint16_t timer_read();
uint16_t timer_ms_elapsed(uint16_t t1, uint16_t t2);

#endif

