 /*
 * MAIN Generated Driver File
 * 
 * @file main.c
 * 
 * @defgroup main MAIN
 * 
 * @brief This is the generated driver implementation file for the MAIN driver.
 *
 * @version MAIN Driver Version 1.0.0
*/

/*
© [2025] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/
#include "mcc_generated_files/system/system.h"
#include "lcd.h"
#include "dht.h"
#include "esp8266.h"
/*
    Main application
*/

struct dht_sensor dht_11;

void myTimer0ISR(){

}

int main(void)
{
    SYSTEM_Initialize();
    Timer0_OverflowCallbackRegister(myTimer0ISR);
    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts 
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global Interrupts 
    // Use the following macros to: 

    // Enable the Global Interrupts 
    INTERRUPT_GlobalInterruptEnable(); 

    // Disable the Global Interrupts 
    //INTERRUPT_GlobalInterruptDisable(); 
    ADCC_Initialize();
    lcd_init();
    lcd_clear();
    uint16_t acd_result;
    bool response;
    while(1){
        acd_result = ADCC_GetSingleConversion(channel_ANC2);
        //sensor_read(&dht_11);

        char str1[16];
        char str2[4];
        //dht_11.Temp = 25;
        //sprintf(str, "%u", dht_11.Temp);
        
        
        if (acd_result<800){
            sprintf(str1, "Water: empty");
        }else{
            sprintf(str1, "Water: Full");
        }
        sprintf(str2, "%hu", acd_result);
        
        lcd_clear();
        lcd_set_cursor(1,1);
        lcd_print_string(str1);
        lcd_set_cursor(2,1);
        //lcd_print_string(str2);
        
        ESP8266_Initialize(WIFI_MODE_STATION);
        
        response = ESP8266_CheckCommunication();  
        
        sprintf(str2, "%i", response);
        lcd_print_string(str2);
        
        __delay_ms(4000);
        
    }    
}