/*
 * File:   dht.c
 * Author: Jules
 *
 * Created on June 2, 2025, 5:49 PM
 */

#include "mcc_generated_files/system/system.h"

typedef struct dht_sensor{
    unsigned char Check, T_byte1, T_byte2, RH_byte1, RH_byte2, Ch;
    unsigned Temp, RH, RH_ref, Sum;
} dht_sensor;


void send_start_signal(void) {
    IO_RB4_SetDigitalOutput();
    IO_RB4_SetLow();
    __delay_ms(18);
    IO_RB4_SetHigh();
    __delay_us(10);
    IO_RB4_SetDigitalInput();
}

void is_sensor_start_detected(dht_sensor *dht) {
    dht->Check = 0;
    __delay_us(40);
    if (IO_RB4_GetValue() == 0) {
        __delay_us(30);
        if (IO_RB4_GetValue() == 1) {
            dht->Check = 1;
            __delay_us(40);
        }
    }
}

char ReadData(void) {
    char i, j;
    for (j = 0; j < 8; j++) {
        while (!IO_RB4_GetValue()); //Wait until input goes high
        __delay_us(30);
        
        //If input is low after 30us then the bit is a 0
        if (IO_RB4_GetValue() == 0)
            i &= ~(1 << (7 - j)); //Clear bit (7-b)
        else {
            i |= (1 << (7 - j)); //Set bit (7-b)
            while (IO_RB4_GetValue());
        } //Wait until PORTD.F0 goes LOW necessary since if a 1 still high after 30us
    }
    return i;
}

void sensor_read(dht_sensor *dht) {
    send_start_signal();
    is_sensor_start_detected(dht);
    if (dht->Check == 1) {
        dht->RH_byte1 = ReadData();
        dht->RH_byte2 = ReadData();
        dht->T_byte1 = ReadData();
        dht->T_byte2 = ReadData();
        dht->Sum = ReadData();
        //Checking check_sum
        if (dht->Sum == ((dht->RH_byte1 + dht->RH_byte2 + dht->T_byte1 + dht->T_byte2) & 0XFF)) {
            dht->Temp = dht->T_byte1;
            dht->RH = dht->RH_byte1;
        }
    }
}