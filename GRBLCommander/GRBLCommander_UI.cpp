
#include "GRBLCommander_UI.h"

////////////////////////////////////////////////////////////////
// display handling 

#include "SSD1306.h"

static SSD1306  display(0x3c, 5, 4);

OLEDDisplay *getDisplay() {
  return &display;
}


////////////////////////////////////////////////////////////////
// static functions

extern void grbluic_init() 
{

  display.init();
  display.displayOn();
  display.normalDisplay();
  display.flipScreenVertically();
  display.clear();
  
}

extern void grbluic_drawtest() {
  // draw things
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_10);
  display.drawString(0, 10, "Arial 10");

  display.display();
}

///////////////////////////////////////////////////////////////
// UI Implementation

namespace GRBLCUI {


      ///////////////////////////////////////////////////////////////
      // messages

      
      Message::Message(uint8_t _msg, void *_sender) : msg(_msg), sender(_sender) {
        
      }
      
      KeyMessage::KeyMessage( void *_sender, uint8_t _key) : Message(KEY_MSG,_sender), key(_key) {
        
      }
      
      ///////////////////////////////////////////////////////////////
      // Base Widget

        BaseWidget::BaseWidget() : BaseWidget(NULL) {
          
        }

      BaseWidget::BaseWidget(BaseUI *_parent) {
         this->parent = _parent;
      }
      

      void BaseWidget::sendMessage(Message *msg) {
         if (parent != NULL) {
           // bubble the message by defaults
           parent->sendMessage(msg);
         }
      }

      void BaseWidget::setParent(BaseUI *_parent) {
         this->parent = _parent;
      }
        

      /////////////////////////////////////////////////////////////////
      // Menu Widget

      Menu::Menu(BaseUI *_parent) : BaseWidget(_parent) {         
        
      }

      Menu::Menu() : Menu(NULL) {       
      }
      
      void Menu::startup() {
        
      }

      void Menu::SetIterator(Iterator *_it) {
         this->it = _it;
      }

      void Menu::SetSelected(uint8_t sel) {
         this->selectedElement = sel;
      }

       void Menu::ResetSelected() {
         this->selectedElement = -1;   
       }
       
        void Menu::MoveDown() {
          this->selectedElement +=1;
          int onscreenline = selectedElement - menuElementStart;
          if (onscreenline >= menusize) {
              menuElementStart += menusize; 
          }
          
        }
        
        void Menu::MoveUp(){
          Serial.println(selectedElement);
          if (selectedElement <= 0)
          {
             return;
          }
          this->selectedElement -= 1;
          int onscreenline = selectedElement - menuElementStart;
          if (onscreenline < 0) {
              menuElementStart -= menusize;
          }
        }

      void Menu::seek(int element, const char **out) {
         if (it == NULL) {
             return;
         }
         if (element < 0) {
             return;
         }
         it->reset();
         uint16_t currentElement = 0;
         *out = it->nextElement();
       
          // skip elements
          while (*out != NULL && currentElement < element ) {
              *out = it->nextElement();
              currentElement++;
          }

      }

      void Menu::draw() {
          if (it != NULL) {

            // seek to the current element
            OLEDDisplay * display = getDisplay();
            display->clear();
            
            const char *e = NULL;
            seek(menuElementStart, &e);
            
            uint8_t i = 0;
            display->setTextAlignment(TEXT_ALIGN_LEFT);
            display->setFont(ArialMT_Plain_10);
            display->setColor(WHITE);

            while (e != NULL) {
               display->drawString(0, i * lineheight, e);
               e = it->nextElement();
               i++;
               if (i >= menusize) {
                  break;
               }
            }
            
            // display selected
            if (selectedElement >= 0) {
                // compute the visible line
                int onscreenline = selectedElement - menuElementStart;
                if (onscreenline >= 0 && onscreenline < menusize) {
                    display->setColor(INVERSE);
                    // highlight the line
                    display->fillRect(0,onscreenline * lineheight, DISPLAY_WIDTH,10);
                    display->setColor(WHITE);
                }
            }

            display->display();
          } // it != NULL
        
      }
      
      bool Menu::dispatchMessage(Message *msg) {
        
      }

}
  
