#ifndef GRBLCOMMANDER_MAINSCREEN_h
#define GRBLCOMMANDER_MAINSCREEN_h

#include "GRBLCommander_UI.h"
#include "Application.h"

using namespace GRBLCUI;

namespace App {
  
    /////////////////////////////////////////////////
    // main screen


      // test class iterator
      class MainListIterator : public Iterator {
          public:
            virtual void reset();
            virtual const char *nextElement();
          private:
            int it = 0;
            const char *current = NULL;
      };
     

    
     class MainScreen : public Screen {
     public:
        MainScreen(Application *_parent);
     
        // startup phase
        virtual void startup();
        // draw the main menu
        virtual void draw();
        
        // dispatch the message and return if the message is consumed
        // this use a delegating model
        virtual bool dispatchMessage(Message *msg);
        
     private:
        Menu m_menu;
        MainListIterator m_iterator;     
    };



}


#endif
