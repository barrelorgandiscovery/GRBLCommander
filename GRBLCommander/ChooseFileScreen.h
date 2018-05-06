
#ifndef GRBLCOMMANDER_CHOOSEFILESCREEN
#define GRBLCOMMANDER_CHOOSEFILESCREEN

#include "mySD.h"
#include "GRBLCommander_UI.h"
#include "Application.h"


using namespace GRBLCUI;

namespace App {
  
    /////////////////////////////////////////////////
    // main screen

      // test class iterator
      class SDCardListIterator : public Iterator {
          public:
            virtual void init();
            virtual void reset();
            virtual const char *nextElement();
          private:
            File root;
            File entry;
      };
    
     class ChooseFileScreen : public Screen {
     public:
        ChooseFileScreen(Application *_parent);
     
        // startup phase
        virtual void startup();
        // draw the main menu
        virtual void draw();

        virtual void getSelectedFile(char *outbuffer);
        
        // dispatch the message and return if the message is consumed
        // this use a delegating model
        virtual bool dispatchMessage(Message *msg);
        
     private:
        Menu m_menu;
        SDCardListIterator m_iterator;     
    };


}




#endif
