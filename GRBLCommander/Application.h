
#ifndef GRBLCOMMANDER_APPLICATION_h
#define GRBLCOMMANDER_APPLICATION_h

#include "GRBLCommander_UI.h"

using namespace GRBLCUI;

namespace App {
  
  // top level application
  class Application : public BaseUI {
    public:
       GRBLCUI::BaseWidget *current;

       // start the application
       virtual void startup();
       
       virtual bool dispatchMessage(Message *msg);
       virtual void sendMessage(Message *msg);
       
    private:
       void clearScreen();
       void changeCurrent(GRBLCUI::BaseWidget *next);
    
  };



   class Screen : public BaseWidget {
        public:
        Screen(Application *_parent);
        Screen();
    
        virtual void startup();
        // draw the button
        virtual void draw();
        virtual void sendMessage(Message *msg);
    
    };

  // test class iterator
  class TestIt : public GRBLCUI::Iterator {
      public:
        virtual void reset();
        virtual const char *nextElement();
      private:
        int it = 0;
        const char *current = NULL;
  };
 
}

///////////////////////////////////////////////////////
// global instances
  
extern App::Application mainApp;

extern void StartUI();

extern void LoopUI();



#endif
