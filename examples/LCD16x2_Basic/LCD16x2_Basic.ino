#include <Lcd16x2.h>
LCD16x2 lcd(5,4,3,2,7,6);
char line1[16];

uint16_t c=0;

void setup() {
  lcd.init();
  lcd.clear();
  lcd.print_xy(0,0,"Think Make");
  lcd.print_xy(0,1,"LCD16x2 Demo");
  delay(1000);
  lcd.clear();
}

void loop() {

  sprintf(line1,"Counter : %d",c++);
  lcd.print_xy(0,0,"Variables");
  lcd.print_xy(0,1,line1);
  delay(1000);
  lcd.clear();
}
