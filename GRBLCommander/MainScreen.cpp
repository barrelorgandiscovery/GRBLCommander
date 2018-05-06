
#include "MainScreen.h"
#include "debug.h"

using namespace GRBLCUI; 

namespace App {


///////////////////////////////////////
// Main screen


    
    void MainListIterator::reset() {
      current = NULL;
      it = -1;
    }

    const char *mainMenuElements[] = { "Homing", "Send a file", "About"};
    
    const char *MainListIterator::nextElement() {
        if (it >= 1) {
          return NULL;
        }
        return mainMenuElements[++it];
    }


    MainScreen::MainScreen(Application *_parent): Screen(_parent) {

    }
    
    void MainScreen::startup() {
       
       m_menu.setParent(this);
       m_menu.SetIterator(&m_iterator);
       m_menu.SetSelected(0);
      
    }


    void MainScreen::draw() {
        debug("drawing screen");
        m_menu.draw();
      
    }

    bool MainScreen::dispatchMessage(Message *msg) {
      if (msg == NULL)
      {
        return false;
      }
    
      if (msg->msg == KEY_MSG) {

        KeyMessage *k = (KeyMessage *)msg;
        switch(k->key) {
           case 1:
             Serial.println("move down");
             m_menu.MoveDown();
             break;
           case 2:
             Serial.println("move up");
             m_menu.MoveUp();
             break;
           
        };

        draw();
        return true;
        
      }
      
      return false;
    }

  

}

