/*============================================================================
 * main.c
 *	
 *==========================================================================*/


#include <p32xxxx.h>
#include <plib.h>
#include <xc.h>
#include "light_control.h"
#include "analog_in.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include "plib.h"
#include "xc.h"
void main() {
    // Initialize modules
    light_init();
    window_init();
    fan_init();
    analog_in_init();
//    screen_init();
    command_init();
    uart_init();
    while (1) {
        voice_cmd_run();
//        voice_cmd_run();
//        fan_switch(1);
//        window_switch(1);
//        light_switch(1);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        fan_switch(0);
//        window_switch(0);
//        light_switch(0);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);
//        delay_ms(250);

//        //        uint32_t voice = analog_in_read(1); 
//        //        sprintf(str, "%d", voice);
//        //        uart_write_string(str);
//        //        uart_write('\r');
//        //        uart_write('\n');
    }

}



//int main(void)
//{
//        /* Holds the value at which OCx Pin to be driven high */
//        unsigned int pulse_start ;
//        /* Holds the value at which OCx Pin to be driven low */
//        unsigned int pulse_stop;
//        RPA0R = 0x5;
//        ANSELACLR =0x1;
//        //TRISACLR= 0x1;
//        //PORTASET= 0x1;
//        //while(1);
//        /* Turn off OC1 module */
//         CloseOC1();
//        /* Configure output compare1 interrupt */
//        //ConfigIntOC1(OC_INT_PRIOR_5 | EXT_INT_SUB_PRI_2);
//        /* Configure OC1 module for required pulse width */
//         pulse_start = 0x0;
//         pulse_stop = 234;
//         PR2 = 3125 ;
//         T2CON = 0x8070;
//        /* Configure Output Compare module to 'initialise OCx pin
//        low and generate continuous pulse'mode */
//         OpenOC1(OC_ON | OC_IDLE_CON | OC_TIMER2_SRC |
//         OC_CONTINUE_PULSE,
//         pulse_stop, pulse_start);
//        /* Generate continuous pulse till TMR2 reaches 0xff00 */
//          while(1);
////            while(TMR2<= 0xff00);
////            asm("nop");
////            CloseOC1();
////            return 0;
//}
