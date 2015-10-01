/* 
 * File:   Main.c
 * Author: Hatake_Chin
 *
 * Created on July 26, 2012, 9:42 PM
 */

//Include the header file
#include <htc.h>
#include "adc.h"
#include "system.h"
#include "lcd.h"

/*******************************************************************************
* DEVICE CONFIGURATION WORDS                                                   *
*******************************************************************************/
__CONFIG(0x3F32);

/*******************************************************************************
* PRIVATE FUNCTION PROTOTYPES                                                  *
*******************************************************************************/
void initialize(void);

void main(void)
{
    unsigned int total;
    unsigned int i;
    unsigned int voltage;

    TRISA0 = 1;
    TRISB = 0b00000001;
    initialize();

//    while (SW1 == 1)continue;
    LCD_putstr("Voltage:");
    adc_on();
    __delay_ms(1);

    while(1)
    {
	total = 0;	                           //clear the ADC result
	for (i = 0; i<10; i++)
	{
            total = (total + ui_adc_read());	   // accumulate the adc reading
	}
            total = total/10;                      // obtain average value(10x)
            voltage =(float)(total *(5.0/1024)*1000); // value in decimal

            unsigned char value_[4] = {0};
            unsigned char remainder = 0;
            for(unsigned int j = 0; j < 4; j++)    // A loop where to store each
            {                                      // digit in separate array
                remainder = voltage%10;
                voltage =  voltage/10;
                value_[j] = remainder + 0x30;      // ASCII value
            }

            LCD_goto(0,0x40);	                   //goto 2nd line
            LCD_putchar(value_[3]);    
            LCD_putchar('.');
            LCD_putchar(value_[2]);    
            LCD_putchar(value_[1]);        
    }
	adc_off();

	while(1) continue; 	// Infinate loop at the end of program, prevent the PIC from reset
 }
//            LCD_putchar(value_[0]);
            //extract 3 single digit from ad_result
//            value1 = voltage/1000;
//            value2 = voltage%1000;
//            value3 = value2%100;
//            value2 = value2/100;
//            value4 = value3%10;
//            value3 = value3/10;
//
//
//            // convert 3 digit into ASCII
//            value1 = value1 + 0x30;
//            value2 = value2 + 0x30;
//            value3 = value3 + 0x30;
//            value4 = value4 + 0x30;
void initialize(void)
{
    adc_initialize();
    __delay_ms(10);
    LCD_initialize();
    LCD_clear();
}