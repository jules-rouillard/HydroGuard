/*
 * File:   lcd.c
 * Author: Jules
 *
 * Created on 02 June 2025, 17:33
 */


#include "mcc_generated_files/system/system.h"
#define RS RC5
#define EN RC4
#define D4 RC3
#define D5 RC6
#define D6 RC7
#define D7 RB7

void ldc_set_data(char data){
    //Using and operation we verify each 4 bit of data one by one and change the state of the pin accordingly
    if (data & 0b0001)
        D4 = 1;
    else
        D4 = 0;	
    if(data & 0b0010)
		D5 = 1;
	else
		D5 = 0;
	if(data & 0b0100)
		D6 = 1;
	else
		D6 = 0;
	if(data & 0b1000)
		D7 = 1;
	else
		D7 = 0;
}

void lcd_cmd(char data){
    RS = 0; //RS 0 for cmd mode
    ldc_set_data(data);
    EN = 1;
    __delay_us(500);
    EN = 0;
}

void lcd_clear(){
    lcd_cmd(0b0000);//Clear display
    lcd_cmd(0b0001);
    //Return home Execution time 1.52ms
    lcd_cmd(0b0000);
    lcd_cmd(0b0010);
    __delay_ms(2);
}



void lcd_init(){
    ldc_set_data(0b0000);    
    __delay_ms(20);
    lcd_cmd(0b0011); //initialization by instructions figure 24
    __delay_ms(5);
    lcd_cmd(0b0011); //initialization by instructions
    __delay_ms(11);
    lcd_cmd(0b0011); //initialization by instructions
    
    lcd_cmd(0b0010); // Function set 4 bit mode
    lcd_cmd(0b0010); // Function set 4 bit mode
    lcd_cmd(0b0010); // Function set 4 bit mode
    lcd_cmd(0b0011); // Function set 2 line font 5x11   
    
    lcd_cmd(0b1000); //Select Row 1
    lcd_cmd(0b0000); //Clear Row 1 Display
    lcd_cmd(0b1100); //Select Row 2
    lcd_cmd(0b0000); //Clear Row 2 Display
    lcd_cmd(0b0000); // Entry mode set
    lcd_cmd(0b0110); //Entry mode
}

void lcd_print_char(char data){
    //Send the data over two transmission
    //data = 0bxxxx yyyy  data & 0b0000 1111 = 0b0000 yyyy  data & 0b1111 0000 = 0bxxxx 0000
    //0b1111 0000 >> 4 = 0b0000 1111 
    RS = 1 ;
    ldc_set_data((data & 0b11110000)>>4);
    EN = 1;
    __delay_us(500);
    EN = 0 ;
    // No need to shift has set_data function only look at the 4 lower bit
    ldc_set_data(data & 0b00001111);
    EN = 1;
    __delay_us(500);
    EN = 0 ;
}

void lcd_set_cursor(char a, char b)
{
	char temp,z,y;
	if(a== 1)
	{
	  temp = 0x80 + b - 1; //80H is used to move the cursor
		z = temp>>4; //Lower 8-bits
		y = temp & 0x0F; //Upper 8-bits
		lcd_cmd(z); //Set Row
		lcd_cmd(y); //Set Column
	}
	else if(a== 2)
	{
		temp = 0xC0 + b - 1;
		z = temp>>4; //Lower 8-bits
		y = temp & 0x0F; //Upper 8-bits
		lcd_cmd(z); //Set Row
		lcd_cmd(y); //Set Column
	}
}

void lcd_print_string(char *a){
    int i;
    for(i=0;a[i]!='\0';i++)
        lcd_print_char(a[i]);
}