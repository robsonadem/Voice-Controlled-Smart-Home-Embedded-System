/*============================================================================
 * window_control.c
 *	Module for window Control.
 *==========================================================================*/
#include <p32xxxx.h>
#include <inttypes.h>
#include <plib.h>
static int window_status;
/* Holds the value at which OCx Pin to be driven high */
static unsigned int pulse_start ;
/* Holds the value at which OCx Pin to be driven low */
static unsigned int pulse_stop;

void window_init(){
// Use PORTB as WINDOW outputs
    
        RPA0R = 0x5;
        ANSELACLR =0x1;
        window_status = 0;
        CloseOC1();
        PR2 = 3125 ;//50HZ
        T2CON = 0x8070;
        pulse_start = 0;
        pulse_stop = 234;
        /* Configure Output Compare module to 'initialise OCx pin
        low and generate continuous pulse'mode */
       OpenOC1(OC_ON | OC_IDLE_CON | OC_TIMER2_SRC |OC_CONTINUE_PULSE,pulse_stop, pulse_start);
}

void servoRotate0() //open
{
  pulse_start = 0;
  pulse_stop = 200; //234;
  SetPulseOC1(pulse_start, pulse_stop);
}

void servoRotate90() //close
{
  pulse_start = 0;
  pulse_stop = 330;
  SetPulseOC1(pulse_start, pulse_stop);
}

void window_switch(int control_signal)
{
    if(control_signal){
        servoRotate0();//open
        window_status=1;
    }
    else{
        servoRotate90();//close
        window_status=0;
    }
    
}

int get_window_status(){
    return window_status; 
}


void servoRotate_NEG90() //open all the way 
{
  pulse_start = 0;
  pulse_stop = 90;
  SetPulseOC1(pulse_start, pulse_stop);
}




