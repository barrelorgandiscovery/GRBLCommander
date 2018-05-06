
#include "mySD.h"

#include "GRBLCommander_UI.h"
#include "Application.h"
#include "MainScreen.h"
#include "ChooseFileScreen.h"
#include "SendFileScreen.h"
#include "debug.h"



App::Application mainApp;


void StartUI() {
 
  
   // init the keyboard
   
   pinMode(39,INPUT); 
   pinMode(36,INPUT);

   delay(1000);
  
   // init the SDCard
   if (!SD.begin(16 /*cs*/, 12 /*mosi */, 13/*miso*/, 14 /*sck */)) {
      debug(">>> ERROR while initializing the SD Card");
      
      getDisplay()->drawString(0, 20, "SD Card Init Failed");
      getDisplay()->display();

  
      delay(1000);
        // init the SDCard
       if (!SD.begin(16 /*cs*/, 12 /*mosi */, 13/*miso*/, 14 /*sck */)) {
          getDisplay()->drawString(0, 30, "Attempt #2 Failed");
          getDisplay()->display();
          delay(1000);
          debug(">>> ERROR while initializing the SD Card Attempt 2");
       }
   }
   debug("End of SD card initialized");
 
   debug("init the application");
   mainApp.startup();
   debug("done");
  


}

#define VALIDATE_BUTTON_DELAY 200
#define ANALOG_BUTTON_TIGGER 500

extern void LoopUI() {

    // trigger for button up
    bool k1state = false;
    bool k2state = false;
    
  //  bool k3state = false;

    int k1trigger = -1;
    int k2trigger = -1;
    

    while(true) {
        
        // check keyboard
        int p = analogRead(39);
        if (p < ANALOG_BUTTON_TIGGER ) {
           k1state = true;
        } else {
           if (k1state == true) {
              // activate the trigger
              k1trigger = VALIDATE_BUTTON_DELAY;
            } 
          k1state = false;
        }
        
        p = analogRead(36);
         if (p < ANALOG_BUTTON_TIGGER ) {
           k2state = true;
        } else {
           if (k2state == true) {
              //activate the trigger
              k2trigger = VALIDATE_BUTTON_DELAY;
            } 
          k2state = false;
          
        }

        // trigger the state, for both buttons
        if (k1trigger > 0 && k2trigger > 0) {
              GRBLCUI::KeyMessage key(&mainApp, 3);
              debug("key 3 pressed");
              mainApp.dispatchMessage(&key);
              k1trigger = -1; // disable the triggers
              k2trigger = -1;
               
        }


        // trigger the state
        if (k1trigger == 0) {
              GRBLCUI::KeyMessage key(&mainApp, 1);
               debug("key 1 pressed");
              mainApp.dispatchMessage(&key);
              k1trigger = -1;
              
        }

        // trigger the state
        if (k2trigger == 0) {
              GRBLCUI::KeyMessage key(&mainApp, 2);
               debug("key 2 pressed");
              mainApp.dispatchMessage(&key);
              k2trigger = -1;
              
        }

        if (k1trigger > 0) {
          k1trigger --;
        }

        if (k2trigger > 0) {
          k2trigger --;
        }

/*
        p = digitalRead(16);
        if (p == 1) {
            if (k3state == false) {
               debug("key 3 pressed");
               k3state = true;
                GRBLCUI::KeyMessage key(&mainApp, 3);
              mainApp.dispatchMessage(&key);
              
            }
        } else {
          k3state = false;
        }*/
        
       delay(1); // in milliseconds
    }

  
}

namespace App {
  
///////////////////////////////////////////////////////////////////////////////////
// Navigation Message

      NavigationMessage::NavigationMessage(void *_sender, uint8_t _screen) : Message(NAVIGATION_MESSAGE,_sender) {
         this->screen = _screen;  
      }


///////////////////////////////////////////////////////////////////////////////////
// Main application



// screens

MainScreen mainScreen(&mainApp);
ChooseFileScreen chooseFileScreen(&mainApp);
SendFileScreen sendFileScreen(&mainApp);


// start the application, it kow all the screens, and initialize them

void Application::startup() {
    clearScreen();

    // start all the screens
 
    mainScreen.startup();
    chooseFileScreen.startup();
   
    changeCurrent(&chooseFileScreen);
    
}


bool Application::dispatchMessage(GRBLCUI::Message *msg) {
    // reroute the messages to the current view
    // current never NULL
    return current->dispatchMessage(msg);
}

void Application::clearScreen() {
    getDisplay()->clear();
    getDisplay()->display();
}

void Application::changeCurrent(GRBLCUI::BaseWidget *next) {
  current = next;
  clearScreen();
  current->draw();
}

void Application::sendMessage(GRBLCUI::Message *msg) {

    // handle sub elements messages, upstreams to parents

    if (msg->msg == NAVIGATION_MESSAGE)
    {
       NavigationMessage *navMsg = (NavigationMessage *)msg;
       if (navMsg->screen == SEND_FILE_SCREEN) {
          debug("change to screen sendfile");
          char buffer[500] = "\0";
          chooseFileScreen.getSelectedFile(&buffer[0]);
          debug("selected file :");
          debug(buffer);
          sendFileScreen.SetFile(buffer);
          changeCurrent(&sendFileScreen);
       }
    }
  
    /*
    if (msg->msg == APP_MESSAGE_GO_HOME) {
      ss_change_command(SS_COMMAND_END);   
      changeCurrent(&mainScreen);
    } else if (msg->msg == APP_MESSAGE_RECORD) {
      ss_change_command(SS_COMMAND_START);
      midiWidget.resetPosition();
      changeCurrent(&recordScreen);
    }*/
}

//////////////////////////////////////////////////////
// Test iterator

void TestIt::reset() {
  current = NULL;
  it = -1;
}

const char *t1[] = { "First Element", "SecondElement" ,"3 eme ", "4 eme" ," 5 eme" ,"6","7","8","9","10"};

const char *TestIt::nextElement() {

    if (it >= 9) {
      return NULL;
    }
    return t1[++it];
    
}


    ///////////////////////////////////////////
    // abstract class for screens

    Screen::Screen(Application *_parent): BaseWidget(_parent) {

    }
    
    Screen::Screen(): BaseWidget(NULL) {
    }

    void Screen::startup() {

      
    }

    void Screen::draw() {

      
    }
    
    void Screen::sendMessage(Message *msg) {
       if (msg != NULL && this->parent != NULL) {
           this->parent->sendMessage(msg);
       }
    }

}

