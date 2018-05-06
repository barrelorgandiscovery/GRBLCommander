

//
// Patrice Freydiere - Barrel Organ Discovery - GRBL Commander program
//

// #include <Arduino.h>
#include <SPI.h> // needed for sdcard
#include <Wire.h>  // needed for oled display

#include "GRBLCommander_UI.h"
#include "Application.h"
#include "debug.h"

void setup() {
  Serial.begin(115000);
  Serial.println("Initialising the card");
 
   grbluic_init();
   
   grbluic_drawwelcome();
   
   StartUI();
   LoopUI();
}


void loop() {

  // peek input, 
  // dispatch to the application
  

 
}



