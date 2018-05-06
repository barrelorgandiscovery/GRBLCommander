#include "ChooseFileScreen.h"


#include "mySD.h"
#include "debug.h"

using namespace GRBLCUI; 

namespace App {

    static char buffer[300]; // display name

    ///////////////////////////////////////
    // Main screen

    void SDCardListIterator::init() {
      root = SD.open("/");
    }

    
    void SDCardListIterator::reset() {
      root.rewindDirectory();
    }

    
    const char *SDCardListIterator::nextElement() {
        if (root) {
          entry = root.openNextFile();
          if (!entry) {
            return NULL;
          }
          strcpy(buffer, entry.name());
          return buffer;
        }

        return NULL;
    }


    ChooseFileScreen::ChooseFileScreen(Application *_parent): Screen(_parent) {

    }
    
    void ChooseFileScreen::startup() {

       // init sdcard
       debug("choose file init");
       m_iterator.init();
       m_iterator.reset();
       
       m_menu.setParent(this);
       m_menu.SetIterator(&m_iterator);
       
    }


    void ChooseFileScreen::draw() {
        debug("choose file drawing screen");
        m_menu.draw();
      
    }


    void ChooseFileScreen::getSelectedFile(char *outbuffer) {
      Serial.println(m_menu.GetSelected());
      if (m_menu.GetSelected() != -1) {
         m_menu.GetSelectedElement(outbuffer);
      }
    }

    bool ChooseFileScreen::dispatchMessage(Message *msg) {

      if (msg->msg == KEY_MSG) {
          KeyMessage *keyMessage = (KeyMessage *)msg;
          if (keyMessage->key == 3) {
            // validate key
            // get the selected file

            // and send a message
            NavigationMessage nm(this, NAVIGATION_MESSAGE);
            sendMessage(&nm);
            
            return true;
            
          } else {
            return m_menu.dispatchMessage(msg);
          }
      }
      
      return false;
    }

  

}
