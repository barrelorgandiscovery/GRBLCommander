
#include <Arduino.h>
#include "Application.h"
#include "MainScreen.h"
#include "debug.h"



App::Application mainApp;


void StartUI() {
  
   debug("init the application");
   mainApp.startup();
   debug("done");
  
   // init the keyboard
   
   pinMode(39,INPUT); 
   pinMode(36,INPUT);


  /*
   // test for the menu
   GRBLCUI::Menu m(&mainApp);
   
   // mainApp.current = &m;
   App::TestIt mytestiterator;
   m.SetIterator(&mytestiterator);
   m.SetSelected(0);
   m.draw();

   for(int i = 0; i < 20 ; i++) {
     m.MoveDown();
     m.draw();
     delay(100);
   }
   
   for(int i = 0; i < 20 ; i++) {
     m.MoveUp();
     m.draw();
     delay(100);
   }
*/
}

extern void LoopUI() {

    bool k1state = false;
    bool k2state = false;
  //  bool k3state = false;

    while(true) {
        
        // check keyboard
        int p = analogRead(39);
        if (p < 500 ) {
            if (k1state == false) {
              debug("key 1 pressed");
              k1state = true;
              GRBLCUI::KeyMessage key(&mainApp, 1);
              mainApp.dispatchMessage(&key);
            } 
        } else {
          k1state = false;
        }
        
        p = analogRead(36);
        if (p < 500) {
            if (k2state == false) {
              debug("key 2 pressed");
              k2state = true;
              GRBLCUI::KeyMessage key(&mainApp, 2);
              mainApp.dispatchMessage(&key);
            }
        } else {
          k2state = false;
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
        
       delay(0.01);
    }

  
}



///////////////////////////////////////////////////////////////////////////////////
// Main application

namespace App {


// screens

MainScreen mainScreen(&mainApp);



// start the application, it kow all the screens, and initialize them

void Application::startup() {
    clearScreen();

    // start all the screens
 
    mainScreen.startup();
    // recordScreen.startup();
    
    current = &mainScreen;
    current->draw();

    
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
