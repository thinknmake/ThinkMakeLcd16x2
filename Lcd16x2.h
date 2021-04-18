#ifndef _LCD16x2_H_
#define _LCD16x2_H_

#include "Arduino.h"

class LCD16x2
{
    public:
        EMLcd(uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7,uint8_t rs,uint8_t en);
	void init();
	void clear(void);
	void clk_pulse(void);
	void nibble(uint8_t nibble);
	void goto_xy(uint8_t x,uint8_t y);
	void send(uint8_t byte,uint8_t rs_pin);
	void print(const char *str);
	void print_xy(uint8_t x,uint8_t y,char *str);
    private:
	uint8_t lcd_data_pins[4]={0,0,0,0};
	uint8_t _rs_pin=0;
	uint8_t _en_pin=0;
};

#endif
