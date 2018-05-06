#include "SendFileScreen.h"
#include "debug.h"

using namespace GRBLCUI;

namespace App {

    char filepath[500] = "\0";


    SendFileScreen::SendFileScreen(Application *_parent): Screen(_parent) {

    }

    void SendFileScreen::SetFile(const char *thefilepath) {
       strcpy(&filepath[0], thefilepath);
       
    }
    
    void SendFileScreen::startup() {

       // init sdcard
       debug("choose file init");
       
       
    }

    void SendFileScreen::draw() {
        debug("choose file drawing screen");
        // m_menu.draw();
        getDisplay()->drawString(0,10, "File to send:");
        getDisplay()->drawString(0,20, filepath);
        getDisplay()->display();
    }

    bool SendFileScreen::dispatchMessage(Message *msg) {

      
      return true;// m_menu.dispatchMessage(msg);
    }



}
