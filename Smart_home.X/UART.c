/* 
 * File:   uart.c
 * Author: Tianyu Zhu & Robson Adem
 * Main model that runs the program
 * Created on September 20, 2018, 8:19 AM
 */
#include <p32xxxx.h>
#include <inttypes.h>
#include <time.h>

#include "UART.h"



void uart_init() {
#pragma config FNOSC = FRCPLL, POSCMOD = OFF
#pragma config FPLLIDIV = DIV_2, FPLLMUL = MUL_20
#pragma config FPBDIV = DIV_1, FPLLODIV = DIV_2
#pragma config FWDTEN = OFF, JTAGEN = OFF, FSOSCEN = OFF
    
    
    TRISB = 0x2000;
    ANSELB = 0x2000;
//    PORTA &= ~0x8;
    
//    TRISA = 0xff;
//    TRISB = 0xff;
////    TRISB == 0x678E;
//    ANSELA = 0x2;
//    ANSELB = 0x0;
////    CNPUA = 0xc;
////    CNPUB = 0x780;
//
//    //Set RPA4 as input for U1RX
//    U1RXR = 0x2;
//    //set output pin to RPA0
  //RPA0R = 0x1;
//    
//    U1MODEbits.BRGH = 0;
//    U1BRG = 257;
//    
//    U1MODEbits.ON = 1;                  // UART1 is enabled
//    U1STAbits.URXEN = 1;                // UART1 receiver is enabled
//     
//    U1STAbits.UTXEN = 1;                // UART1 transmitter is enabled
}

void uart_write(char c)
{
    while(U1STAbits.UTXBF);
    {
       
        
    }
    U1TXREG = c;   
    
}

char uart_read()
{
    while(!U1STAbits.URXDA)
    {
        
    }
    return U1RXREG;
}

int uart_read_ready()
{
    if(U1STAbits.URXDA)
    {
        return 1;
    }
    else return 0;
}

int uart_write_ready()
{
    if(!U1STAbits.UTXBF)
    {
        return 1;
    }
    else return 0;
}

char uart_read_nb()
{
   if(!uart_read_ready()) 
   {
       return NULL;
   }
   return U1RXREG;
}

void uart_write_nb(char c)
{
    if(!uart_write_ready())
    {
        return;
    }
    U1TXREG = c; 
}


void uart_write_string(char* string)
{
    while(*string)
    {
        uart_write(*string);
        string = string+1;
    }
}

void uart_read_string(char* string, int str_size)
{
    int count = 0; 
    while(count<str_size)
    {
        *string = uart_read();
        
        
        
        //backspace condition
        if(*string == 8 && count>0 )
        {
            uart_write(8);
            uart_write(' ');
            uart_write(8);
            string--;
            count--;

        }            //end reading if enter is pressed
        else if (*string == 13) 
        {
            uart_write(13);
            *string = 0;
            uart_write('\n'); //go to the next line
            break;
        } 
        else if (*string != 13 && *string != 8) 
        {
            uart_write(*string);
            count++;
            string++;
        }
        
    }
    
    
    
}
