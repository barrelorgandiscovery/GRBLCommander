
//
// Patrice Freydiere - Barrel Organ Discovery - GRBL Commander program
//

#include <Wire.h>  // needed for oled display
#include "GRBLCommander_UI.h"
#include "Application.h"
#include "GRBLCommander_UI.h" // for iterator

void setup() {

   grbluic_init();
   grbluic_drawtest();
   StartUI();

}


void loop() {
  // put your main code here, to run repeatedly:

  // loop for serial events
  // adjust the state of the GRBL command and grab the events for the UI
  

}


