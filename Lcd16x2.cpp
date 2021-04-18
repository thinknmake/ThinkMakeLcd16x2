/*
This is the LCD16x2 Basic library.
Copyright (c) 2021 Think Make.  All rights reserved.
*/

#include "Arduino.h"
#include "Lcd16x2.h"

void LCD16x2::clk_pulse(void)
{
    digitalWrite(_en_pin, LOW);
    delayMicroseconds(500);    
    digitalWrite(_en_pin, HIGH);
    delayMicroseconds(500);		//enable pulse must be >450ns
    digitalWrite(_en_pin, LOW);
    delayMicroseconds(500);            	//commands need > 37us to settle
}

LCD16x2::EMLcd(uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7,uint8_t rs,uint8_t en)
{
    lcd_data_pins[0]=d4;
    lcd_data_pins[1]=d5;
    lcd_data_pins[2]=d6;
    lcd_data_pins[3]=d7;
    _rs_pin=rs;
    _en_pin=en;    
}

void LCD16x2::init()
{
    uint8_t i;
    for (i=0;i<4;i++)
    {
        pinMode(lcd_data_pins[i],OUTPUT);
    }
  
    pinMode(_rs_pin,OUTPUT);
    pinMode(_en_pin,OUTPUT);
  
    send(0x03,LOW);
    send(0x02,LOW);
    send(0x28,LOW);
    send(0x0C,LOW);
    send(0x01,LOW);
    send(0x06,LOW);
    send(0x80,LOW);
}

void LCD16x2::clear(void)
{
    send(0x01,LOW);
    send(0x80,LOW);
}

void LCD16x2::nibble(uint8_t nibble)
{
    uint8_t i;
    for (i=0;i<4;i++)
    {
        digitalWrite(lcd_data_pins[i], (( nibble >> i) & HIGH));
    }
    clk_pulse();
}

void LCD16x2::send(uint8_t byte,uint8_t rs_pin)
{
    digitalWrite(_rs_pin, rs_pin);
    nibble(byte >> 4);
    nibble(byte & 0x0F);
}

void LCD16x2::print(const char *str)
{
    while(*str!='\0')
    {
	if (*str=='\r' || *str=='\n')
	{
	    str++;
	    continue;
        }
	else
	{
	    send(*str++,HIGH);
	}
    }
}

void LCD16x2::goto_xy(uint8_t x,uint8_t y)
{
    if(y==0){
        send(0x80+x,LOW);
    }
    else if(y==1){
        send(0xC0+x,LOW);
    }
}

void LCD16x2::print_xy(uint8_t x,uint8_t y,char *str)
{
    goto_xy(x,y);
    print(str);
}
