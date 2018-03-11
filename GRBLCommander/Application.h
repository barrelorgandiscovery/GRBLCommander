
#ifndef GRBLCOMMANDER_APPLICATION_h
#define GRBLCOMMANDER_APPLICATION_h

#include "GRBLCommander_UI.h"

namespace App {
  
  // top level application
  class Application : public GRBLCUI::BaseUI {
    public:
       GRBLCUI::BaseWidget *current;

       // start the application
       virtual void startup();
       
       virtual bool dispatchMessage(GRBLCUI::Message *msg);
       virtual void sendMessage(GRBLCUI::Message *msg);
       
    private:
       void clearScreen();
       void changeCurrent(GRBLCUI::BaseWidget *next);
    
  };

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


#endif
