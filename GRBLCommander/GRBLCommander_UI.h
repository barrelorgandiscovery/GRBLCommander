#ifndef GRBLCOMMANDER_UI_h
#define GRBLCOMMANDER_UI_h

#include <Arduino.h>
#include "OLEDDisplay.h"

// static initialization of the screen
void grbluic_init();

// test function
void grbluic_drawtest();

// global access to screen functions
OLEDDisplay *getDisplay();

// standard UI components
namespace GRBLCUI {

    // base message
    class Message {
       public:
          Message(uint8_t _msg, void *_sender);
          uint8_t msg;
          void *sender;
    };
    
    #define KEY_MSG 1
     class KeyMessage : public Message {
          public:
            KeyMessage(void *_sender, uint8_t _key);
            uint8_t key;
      };

    ///////////////////////////////////////////////////////////////////////////

    /**
     * Class that manage the communication, and events associated to the elements
     */
    class BaseUI {
        public:
          // dispatch the message and return if the message is consumed
          virtual bool dispatchMessage(Message *msg) = 0;
  
          // send a new message to upstream
          virtual void sendMessage(Message *msg) = 0;
    };
  
  
    // every widget has a startup and draw methods
    class BaseWidget : public BaseUI {
       public:
        BaseWidget(BaseUI *_parent);
        // startup phase
        virtual void startup() = 0;
        // draw the button
        virtual void draw() = 0;
        // dispatch the message and return if the message is consumed
        // this use a delegating model
        virtual bool dispatchMessage(Message *msg) = 0;

        // widgets may send messages upstream
        virtual void sendMessage(Message *msg);
      
      protected:
        // every widgets has a parent, for dispatching events
        BaseUI *parent;
    };

    class Iterator {
        public:
        virtual void reset() = 0;
        virtual const char *nextElement() = 0;
    };

    // menu is a widget
    //  furnish an enumerator interface to display the elements
    class Menu : BaseWidget {

        public:
          Menu(BaseUI *_parent);

          void SetIterator(Iterator *_it);
          void SetSelected(uint8_t sel);
          uint8_t GetSelected();
          void ResetSelected();
          void MoveDown();
          void MoveUp();
          virtual void startup();
          virtual void draw();
          virtual bool dispatchMessage(Message *msg);

        private:
          const uint8_t menusize = 6;
          const uint8_t lineheight = 10;
          Iterator *it = NULL;
          uint8_t menuElementStart = 0;
          uint8_t selectedElement = -1; // no selected elements

          void seek(int element, const char **out);
        
    };

  
}


#endif
