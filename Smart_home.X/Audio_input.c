/* 
 * File:   Audio_input.h
 * Author: Tianyu and Robson
 * This is  the delay module 
 * Created on September 1, 2018
 */

#include "Audio_input.h"
#include <inttypes.h>
#include "analog_in.h"
#include <p32xxxx.h>
#include <stdio.h>
#include "UART.h"
#include <string.h>
#include <math.h>

#define INDICATOR 0x80



int voice;
int ABSvoice;
uint16_t time;
int length;
int Record[20];
int loop;
int ZC;
int ZC_last;
int zcNum;
uint64_t energy;
int clipStatus;
int GapCnt;

void voiceInitial() {
    voice = 0;
    ABSvoice = 0;
    time = 0;

    loop = 0;
    length = 0;
    ZC = 0;
    ZC_last = 0;
    zcNum = 0;
    energy = 0;
    clipStatus = 0;
    GapCnt = 0;


    int i;
    for (i = 0; i < 20; i++) {
        Record[i] = 0;
    }
}

void swapStart() {
    int i;
    for (i = 0; i < 19; i++) {
        Record[i] = Record[i + 1];
    }
}

int avgStart() {
    int t;
    int sum = 0;
    for (t = 0; t < 20; t++) {
        sum = sum + Record[t];
    }
    return floor((float) sum / (float) 20);

}

int zeroCrossing(int a, int b) {
    if (a > 0 && b < 0) {
        return 1;
    }
    if (a < 0 && b > 0) {
        return 1;
    } else return 0;
}

int energyNorm() {
    return floor((float) energy / (float) length);
}

int idle() {
    voiceInitial();

    char str[10];

    while (1) {
        voice = analog_in_read(13);

        ABSvoice = abs(voice - 512);
        Record[19] = ABSvoice;

        int s = avgStart();

        if (s > 30) {

            length = length + 1;
            PORTB |= INDICATOR;
            GapCnt = 0;
            clipStatus = 1;
            swapStart();


            ZC = voice - 512;
            if (zeroCrossing(ZC, ZC_last)) {
                zcNum = zcNum + 1;
            }
            ZC_last = ZC;

            energy = energy + ABSvoice;

        }
        if (clipStatus && s < 30) {
            PORTB |= INDICATOR;
            length = length + 1;
            GapCnt = GapCnt + 1;
            if (GapCnt > 150) {
                clipStatus = 0;
            }
            swapStart();

            ZC = voice - 512;
            if (zeroCrossing(ZC, ZC_last)) {
                zcNum = zcNum + 1;
            }
            ZC_last = ZC;
            energy = energy + ABSvoice;

        } else if (!clipStatus && s < 30) {
            PORTB &= ~INDICATOR;


            clipStatus = 0;
            swapStart();




            if ((zcNum < 175 && zcNum > 110) ) {

                return 1;
            }
            zcNum = 0;
            energy = 0;
            length = 0;
        }
    }

    PORTB &= ~INDICATOR;
    //    sprintf(str, "%d", energy);
    //    uart_write_string(str);
    //    uart_write('\r');
    //    uart_write('\n');

}

int waitingforcommand() {
    voiceInitial();

    time = ((uint64_t) 40000000 * (uint64_t) 250) / (uint64_t) 256000;
    char str[10];
    

    while (loop < 40) {
        TMR1 = 0;
        while (TMR1 < time) {
            voice = analog_in_read(13);
            ABSvoice = abs(voice - 512);
            Record[19] = ABSvoice;

            int s = avgStart();

            if (s > 30) {
                PORTB |= INDICATOR;
                length = length + 1;

                GapCnt = 0;
                clipStatus = 1;
                swapStart();

                ZC = voice - 512;
                if (zeroCrossing(ZC, ZC_last)) {
                    zcNum = zcNum + 1;
                }
                ZC_last = ZC;

                energy = energy + ABSvoice;

            }
            if (clipStatus && s < 30) {
                
                length = length + 1;
                GapCnt = GapCnt + 1;
                if (GapCnt > 200) {
                    clipStatus = 0;
                    GapCnt=0;
                }
                swapStart();

                ZC = voice - 512;
                if (zeroCrossing(ZC, ZC_last)) {
                    zcNum = zcNum + 1;
                }
                ZC_last = ZC;
                energy = energy + ABSvoice;

            } else if (!clipStatus && s < 30) {
                PORTB &= ~INDICATOR;


                clipStatus = 0;
                swapStart();
                //light
                if ((zcNum < 250 && zcNum > 160) ) {

                    return 1;
                }
                //window
                if ((zcNum < 97 && zcNum > 57) ) {

                    return 2;
                }
//                //music
//                if (zcNum < 94 && zcNum > 74 && energyNorm() > 27 && energyNorm() < 33) {
//
//                    return 3;
//                }
                //cooling
                if ((zcNum < 150 && zcNum > 100) ) {
                    
                    return 4;
                }
                zcNum = 0;
                energy = 0;
                length = 0;
            }
        }


        loop = loop + 1;
        //    sprintf(str, "%d", energy);
        //    uart_write_string(str);
        //    uart_write('\r');
        //    uart_write('\n');

    }
    loop = 0;
    PORTB &= ~INDICATOR;
    return 0;
}



int ONOFF() {
    voiceInitial();

    time = ((uint64_t) 40000000 * (uint64_t) 250) / (uint64_t) 256000;
    char str[10];
    

    while (loop < 40) {
        TMR1 = 0;
        while (TMR1 < time) {
            voice = analog_in_read(13);
            ABSvoice = abs(voice - 512);
            Record[19] = ABSvoice;

            int s = avgStart();

            if (s > 30) {
                PORTB |= INDICATOR;
                length = length + 1;

                GapCnt = 0;
                clipStatus = 1;
                swapStart();

                ZC = voice - 512;
                if (zeroCrossing(ZC, ZC_last)) {
                    zcNum = zcNum + 1;
                }
                ZC_last = ZC;

                energy = energy + ABSvoice;

            }
            if (clipStatus && s < 30) {
                
                length = length + 1;
                GapCnt = GapCnt + 1;
                if (GapCnt > 200) {
                    clipStatus = 0;
                    GapCnt=0;
                }
                swapStart();

                ZC = voice - 512;
                if (zeroCrossing(ZC, ZC_last)) {
                    zcNum = zcNum + 1;
                }
                ZC_last = ZC;
                energy = energy + ABSvoice;

            } else if (!clipStatus && s < 30) {
                PORTB &= ~INDICATOR;


                clipStatus = 0;
                swapStart();
                //Turn On
                if ((zcNum < 497 && zcNum > 331) ) {

                    return 1;
                }
                // Off
                if ((zcNum < 188 && zcNum > 90) ) {

                    return 2;
                }

                
                zcNum = 0;
                energy = 0;
                length = 0;
            }
        }


        loop = loop + 1;
        //    sprintf(str, "%d", energy);
        //    uart_write_string(str);
        //    uart_write('\r');
        //    uart_write('\n');

    }
    loop = 0;
    PORTB &= ~INDICATOR;
    return 0;
}





void traning() {

    char str[10];


    time = ((uint64_t) 40000000 * (uint64_t) 250) / (uint64_t) 256000;


    PORTA |= INDICATOR;
    while (loop < 8) {
        TMR1 = 0;
        //        PORTA |= INDICATOR;
        while (TMR1 < time) {
            voice = analog_in_read(13);
            //           num=num+1;
            ABSvoice = abs(voice - 512);
            Record[19] = ABSvoice;

            int s = avgStart();

            if (s > 30) {
                length = length + 1;
                PORTA |= INDICATOR;
                GapCnt = 0;
                clipStatus = 1;
                swapStart();
                //                swapEnd();

                ZC = voice - 512;
                if (zeroCrossing(ZC, ZC_last)) {
                    zcNum = zcNum + 1;
                }
                ZC_last = ZC;
                //uart_write('1');
                energy = energy + ABSvoice;


            }
            if (clipStatus && s < 30) {
                //                PORTA |= INDICATOR;
                length = length + 1;
                GapCnt = GapCnt + 1;
                if (GapCnt > 150) {
                    clipStatus = 0;
                }
                swapStart();
                //                swapEnd();
                ZC = voice - 512;
                if (zeroCrossing(ZC, ZC_last)) {
                    zcNum = zcNum + 1;
                }
                ZC_last = ZC;
                energy = energy + ABSvoice;


                //                uart_write('1');
            } else if (!clipStatus && s < 30) {
                //                PORTA &= ~INDICATOR;
                //                num=num+1;
                clipStatus = 0;
                swapStart();
                //                swapEnd();

                //                uart_write('2');
            }

        }

        loop = loop + 1;

    }

    loop = 0;
    PORTA &= ~INDICATOR;

    sprintf(str, "Length: %d, ", length);
    uart_write_string(str);




    sprintf(str, "Energy: %d,  ", energy);
    uart_write_string(str);



    sprintf(str, "ZC: %d", zcNum);
    uart_write_string(str);
    uart_write('\r');
    uart_write('\n');
}

int idle_train() {
    voiceInitial();

    char str[10];

    while (1) {
        voice = analog_in_read(13);

        ABSvoice = abs(voice - 512);
        Record[19] = ABSvoice;

        int s = avgStart();

        if (s > 30) {

            length = length + 1;
            PORTA |= INDICATOR;
            GapCnt = 0;
            clipStatus = 1;
            swapStart();


            ZC = voice - 512;
            if (zeroCrossing(ZC, ZC_last)) {
                zcNum = zcNum + 1;
            }
            ZC_last = ZC;

            energy = energy + ABSvoice;

        }
        if (clipStatus && s < 30) {
            PORTA |= INDICATOR;
            length = length + 1;
            GapCnt = GapCnt + 1;
            if (GapCnt > 150) {
                clipStatus = 0;
            }
            swapStart();

            ZC = voice - 512;
            if (zeroCrossing(ZC, ZC_last)) {
                zcNum = zcNum + 1;
            }
            ZC_last = ZC;
            energy = energy + ABSvoice;

        } else if (!clipStatus && s < 30) {
            PORTA &= ~INDICATOR;


            clipStatus = 0;
            swapStart();

            sprintf(str, "Length: %d, ", length);
            uart_write_string(str);


            sprintf(str, "Energy: %d,  ", energy);
            uart_write_string(str);

            sprintf(str, "ZC: %d", zcNum);
            uart_write_string(str);
            uart_write('\r');
            uart_write('\n');


            if (zcNum < 273 && zcNum > 212) {

                return 1;
            }
            zcNum = 0;
            energy = 0;
            length = 0;
        }
    }


    //    sprintf(str, "%d", energy);
    //    uart_write_string(str);
    //    uart_write('\r');
    //    uart_write('\n');

}

int waitingforcommand_train() {
    voiceInitial();

    time = ((uint64_t) 40000000 * (uint64_t) 250) / (uint64_t) 256000;
    char str[10];
    PORTA |= INDICATOR;

    while (loop<16) {
        TMR1 = 0;
        while (TMR1<time) {
            voice = analog_in_read(13);
            ABSvoice = abs(voice - 512);
            Record[19] = ABSvoice;

            int s = avgStart();

            if (s > 30) {

                length = length + 1;

                GapCnt = 0;
                clipStatus = 1;
                swapStart();

                ZC = voice - 512;
                if (zeroCrossing(ZC, ZC_last)) {
                    zcNum = zcNum + 1;
                }
                ZC_last = ZC;

                energy = energy + ABSvoice;

            }
            if (clipStatus && s < 30) {

                length = length + 1;
                GapCnt = GapCnt + 1;
                if (GapCnt > 150) {
                    clipStatus = 0;
                }
                swapStart();

                ZC = voice - 512;
                if (zeroCrossing(ZC, ZC_last)) {
                    zcNum = zcNum + 1;
                }
                ZC_last = ZC;
                energy = energy + ABSvoice;

            } else if (!clipStatus && s < 30) {



                clipStatus = 0;
                swapStart();
                sprintf(str, "Length: %d, ", length);
                uart_write_string(str);


                sprintf(str, "Energy: %d,  ", energy);
                uart_write_string(str);

                sprintf(str, "ZC: %d", zcNum);
                uart_write_string(str);
                uart_write('\r');
                uart_write('\n');

                //light
                if (zcNum < 250 && zcNum > 160 ) {

                    return 1;
                }
                //window
                if (zcNum < 166 && zcNum > 134 && energyNorm() > 26 && energyNorm() < 30) {

                    return 2;
                }
                
                zcNum = 0;
                energy = 0;
                length = 0;
            }
        }


        loop = loop + 1;
        //    sprintf(str, "%d", energy);
        //    uart_write_string(str);
        //    uart_write('\r');
        //    uart_write('\n');

    }
    loop = 0;
    PORTA &= ~INDICATOR;
    delay_ms(250);
    delay_ms(250);
    delay_ms(250);
    return 0;
}








//void output() {
//    int a ;
//    for (a =0;a  < 62000; a++)
//    {
//        uart_write_string(record[a]);
//        uart_write('\r');
//        uart_write('\n');
//    }
//}







//void input_climping()
//{
//    char str[10];
//    analog_in_init();
//    time = ((uint64_t)40000000*(uint64_t)250)/(uint64_t)256000;
//    PORTA|= INDICATOR;
//    
//    while (listentime < 20) {
//        TMR1=0;
//        while (TMR1 < time) {
//            uint32_t voice = analog_in_read(13);
//            sprintf(str, "%d", voice);
//            uart_write_string(str);
//            uart_write('\r');
//            uart_write('\n');
//        }
//        listentime = listentime + 1;
//    }
//    PORTA &= ~INDICATOR;
//    listentime = 0;
//    
//}

//void input_climping()
//{
//    char str[10];
//    uint32_t record[1000];
//    analog_in_init();
//    time = ((uint64_t)40000000*(uint64_t)0.0226)/(uint64_t)256000;
//    A|= INDICATOR;
//    
//    
//    while (1) {
//        
//            uint32_t voice = analog_in_read(13);
//            
//            sprintf(str, "%d", voice);
//            uart_write_string(str);
//            uart_write('\r');
//            uart_write('\n');
//        
//        
//    }
//    PORTA &= ~INDICATOR;
//    listentime = 0;
//    
//}


//sampling at 15388Hz
//void input_climping()
//{
//    char str[1000];
//    char str1[10];
//    char samplefreq[64];
//    uint64_t Hz = 0;
//    analog_in_init();
//    time = ((uint64_t)40000000*(uint64_t)250)/(uint64_t)256000;
//    PORTA|= INDICATOR;
//    sprintf(str, "%d", 111111);
//    while (listentime < 4) {
//        TMR1=0;
//        while (TMR1 < time) {
////            uint32_t voice = analog_in_read(13);
////            Hz =Hz+1;
////            sprintf(str1, "%d", 5678);
////            strcat(str,str1);
////            strcat(str,"\r\n");
//        }
//        listentime = listentime + 1;
//    }



//    int t=0;
//    
//    while(t<10)
//    {
////    sprintf(samplefreq, "%d", Hz);
////    uart_write_string(samplefreq);
////     sprintf(str, "0 %d\n", 1111);
//     sprintf(str1, "%d", 456);
//     strcat(str,str1);
//     t=t+1;
//    }
////     sprintf(str1, "%d", 789);
////     strcat(str,str1);
////     sprintf(str1, "%d", 10);
////     strcat(str,str1);
//     uart_write_string(str);
////    PORTA &= ~INDICATOR;
////    listentime = 0;
//    
//}