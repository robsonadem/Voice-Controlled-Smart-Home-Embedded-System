/*============================================================================
 * fan_control.c
 *	Module for fan Control.
 *==========================================================================*/
#include <p32xxxx.h>
#include <inttypes.h>

#define fan_bit_mask 0x2
static int fan_status;

void fan_init(){
// Use PORTB as FAN outputs
    TRISA = 0x0;
    ANSELA = 0;
    PORTA &= ~fan_bit_mask;//PORTAbits.RA1= 0;
    fan_status = 0;
}
void fan_switch(int control_signal)
{
    if(control_signal){
        PORTA |= fan_bit_mask;//PORTAbits.RA1= 1;
        fan_status=1;
    }
    else{
        PORTA &= ~fan_bit_mask;//PORTAbits.RA1= 0;
        fan_status=0;
    }
    
}

int get_fan_status(){
    return fan_status; 
}

