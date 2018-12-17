/*============================================================================
 * light_control.c
 *	Module for Light Control.
 *==========================================================================*/
#include <p32xxxx.h>
#include <inttypes.h>
static int light_status;
#define light_bit_mask 0x4
void light_init(){
// Use PORTA as LED outputs

    T1CON = 0x8030;
    TRISA = 0x0;
    ANSELA = 0;
    PORTA &= ~light_bit_mask;
    //PORTAbits.RA2= 0;
    light_status = 0;
}
void light_switch(int control_signal)
{
    if(control_signal==1){
        PORTA |= light_bit_mask;//PORTAbits.RA2= 1;
        light_status=1;
    }
    else if(control_signal==0){
        PORTA &= ~light_bit_mask;//PORTAbits.RA2= 0;
        light_status=0;
    }
    
}

int get_light_status(){
    return light_status; 
}


