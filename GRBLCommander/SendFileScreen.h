
#ifndef GRBLCOMMANDER_SENDFILESCREEN
#define GRBLCOMMANDER_SENDFILESCREEN

#include "GRBLCommander_UI.h"
#include "Application.h"


using namespace GRBLCUI;

namespace App {
  
    /////////////////////////////////////////////////
    // main screen
    
     class SendFileScreen : public Screen {
     public:
        SendFileScreen(Application *_parent);
     
        // startup phase
        virtual void startup();
        // draw the main menu
        virtual void draw();
        
        // dispatch the message and return if the message is consumed
        // this use a delegating model
        virtual bool dispatchMessage(Message *msg);

        void SetFile(const char *filename);
        
     private:
      
        Menu m_menu;
    };


}




#endif
