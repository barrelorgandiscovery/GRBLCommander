

#include "Application.h"



///////////////////////////////////////////////////////////////////////////////////
// Main application

App::Application mainApp;


void StartUI() {
  
   mainApp.startup();
  
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

}


// start the application, it kow all the screens, and initialize them

void App::Application::startup() {
    clearScreen();

    // start all the screens
/*   
    mainScreen.startup();
    recordScreen.startup();
    
    current = &mainScreen;
    current->draw();

    */
}


bool App::Application::dispatchMessage(GRBLCUI::Message *msg) {
    // reroute the messages to the current view
    // current never NULL
    return current->dispatchMessage(msg);
}

void App::Application::clearScreen() {
    getDisplay()->clear();
    getDisplay()->display();
}

void App::Application::changeCurrent(GRBLCUI::BaseWidget *next) {
  current = next;
  clearScreen();
  current->draw();
}

void App::Application::sendMessage(GRBLCUI::Message *msg) {

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

void App::TestIt::reset() {
  current = NULL;
  it = -1;
}

const char *t1[] = { "First Element", "SecondElement" ,"3 eme ", "4 eme" ," 5 eme" ,"6","7","8","9","10"};

const char *App::TestIt::nextElement() {

    if (it >= 9) {
      return NULL;
    }
    return t1[++it];
           
    
}

