
#include <Wire.h>  
#include "SSD1306.h"

SSD1306  display(0x3c, 5, 4);
// OLEDDisplayUi ui     ( &display );


void setup() {

  Serial.begin(115200);
  Serial.println();
  Serial.println();

  display.init();
  display.displayOn();
  display.normalDisplay();
  display.flipScreenVertically();
  display.clear();
  
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 10, "Arial 10");

  display.display();
  
}


void loop(){

  Serial.println(touchRead(T2));
  delay(1000);

  
}

