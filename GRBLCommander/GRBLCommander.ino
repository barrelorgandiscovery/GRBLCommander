
//
// Patrice Freydiere - Barrel Organ Discovery - GRBL Commander program
//

#include <Wire.h>  // needed for oled display
#include <SPI.h> // needed for sdcard

#include "GRBLCommander_UI.h"
#include "Application.h"
#include "debug.h"

void setup() {
   Serial.begin(115000);
 
   grbluic_init();
   
   // grbluic_drawtest();
   
   StartUI();
   LoopUI();
}


void loop() {

  // peek input, 
  // dispatch to the application
  

 
}


