#include <inttypes.h>
#include <plib.h>
#include <xc.h>

#include "analog_in.h"

// Configuration word 1 for ADC:
// Turn module on | Output in integer format | Trigger mode auto | Enable autosa
#define ADC_CONFIG1     ADC_FORMAT_INTG | ADC_CLK_AUTO | ADC_AUTO_SAMPLING_OFF 
// ADC ref external | Disable offset test | Disable scan mode | Perform 2 samples | Use dual buffers | Use alternate mode
#define ADC_CONFIG2     ADC_VREF_AVDD_AVSS | ADC_OFFSET_CAL_DISABLE | ADC_SCAN_OFF | ADC_SAMPLES_PER_INT_1 
// Use ADC internal clock | Set sample time
//Use PB clock (default)), 15*Tad, conversion 4 
#define ADC_CONFIG3      ADC_CONV_CLK_PB | ADC_SAMPLE_TIME_9 | ADC_CONV_CLK_3Tcy2  

// Do not assign channels to scan
#define ADC_CONFIG_SCAN  0
#define ADC_CONFIG_PORT  0

void analog_in_init() {
    CloseADC10();
    OpenADC10(ADC_CONFIG1, ADC_CONFIG2, ADC_CONFIG3, ADC_CONFIG_PORT, ADC_CONFIG_SCAN);
    EnableADC10(); // Enable the ADC
}


int32_t analog_in_read(uint8_t analogPIN){

    SetChanADC10(analogPIN << 16);
    AcquireADC10();

    while( AD1CON1bits.SAMP );      // wait until acquisition is done
    while( ! AD1CON1bits.DONE );    // wait until conversion done
 
    return ReadADC10(0);
}


