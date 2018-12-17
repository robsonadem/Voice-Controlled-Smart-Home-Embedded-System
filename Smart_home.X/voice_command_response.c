/*============================================================================
 *  voice_command_response.c
 *      State machine for voice_command_response
 *==========================================================================*/


#include "timer.h"
#include "UART.h"
#include "Audio_input.h"

typedef enum
{
   IDLE = 0,
   WAIT_FOR_COMMAND,
   LIGHT,
   COOLING,
   WINDOW,
   MUSIC
          
} command_state_def;

static command_state_def state;

void command_init()
{
    state = IDLE;
}

void voice_cmd_run()
{
    
    
    switch (state)
    {
        case IDLE:
            uart_write_string("Idle\r\n");
//            printState(0);
            
            if(idle()==1)
            {
                state=WAIT_FOR_COMMAND;
                delay_ms(250);
                delay_ms(250);
            }
            
            break;
            
        case WAIT_FOR_COMMAND:
            uart_write_string("WAIT_FOR_COMMAND\r\n");
//            printState(1);
            int command = waitingforcommand();
            if(command==1)
            {
                state = LIGHT;
                delay_ms(250);
                delay_ms(250);
                
            }
            if(command==2)
            {
                state = WINDOW;
                delay_ms(250);
                delay_ms(250);
            }
//            if(command==3)
//            {
//                state = MUSIC;
//            }
            if(command==4)
            {
                state = COOLING;
                delay_ms(250);
                delay_ms(250);
            }
            if (command==0)
            {
                state = IDLE;
                delay_ms(250);
                delay_ms(250);
            }
            break;

        case LIGHT:
             uart_write_string("Light\r\n");
//             printState(2);
             int command1 = ONOFF();
             if(command1==1)
             {
                 light_switch(1);
                 uart_write_string("light_ON\r\n");
                 state = WAIT_FOR_COMMAND;
             }
             if(command1==2)
             {
                 light_switch(0);
                 uart_write_string("light_OFF\r\n");
                 state = WAIT_FOR_COMMAND;
             }
             if(command1==0)
             {
                 state = WAIT_FOR_COMMAND;
             }

            break;

        case COOLING:
            uart_write_string("COOLING\r\n");
//            printState(3);
            int command2 = ONOFF();
             if(command2==1)
             {
                 fan_switch(1);
                 uart_write_string("Cooling_ON\r\n");
                 state = WAIT_FOR_COMMAND;
             }
             if(command2==2)
             {
                 fan_switch(0);
                 uart_write_string("Cooling_OFF\r\n");
                 state = WAIT_FOR_COMMAND;
             }
             if(command2==0)
             {
                 state = WAIT_FOR_COMMAND;
             }
            break;

        case WINDOW:
            uart_write_string("WINDOW\r\n");
//            printState(4);
            int command3 = ONOFF();
             if(command3==1)
             {
                 window_switch(1);
                 uart_write_string("Window_ON\r\n");
                 state = WAIT_FOR_COMMAND;
             }
             if(command3==2)
             {
                 window_switch(0);
                 uart_write_string("Window_OFF\r\n");
                 state = WAIT_FOR_COMMAND;
             }
             if(command3==0)
             {
                 state = WAIT_FOR_COMMAND;
             }
            break;
            
        case MUSIC:
            uart_write_string("MUSIC\r\n");
            break;
    }
}







 
