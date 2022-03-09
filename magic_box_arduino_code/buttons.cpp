#include "buttons.h"

namespace buttons
{

  
  int BUTTON_1_STATE;             // the current reading from the input pin
  int LAST_BUTTON_1_STATE = LOW;   // the previous reading from the input pin
  int BUTTON_2_STATE;             // the current reading from the input pin
  int LAST_BUTTON_2_STATE = LOW;   // the previous reading from the input pin

  unsigned long LAST_DEBOUNCE_TIME_BUTTON_1 = 0;  // the last time the output pin was toggled
  unsigned long LAST_DEBOUNCE_TIME_BUTTON_2 = 0;  // the last time the output pin was toggled
  unsigned long DEBOUNCE_DELAY = 50;    // the debounce time; increase if the output flickers
  
  bool is_button_pressed(const int& button_pin, int& last_button_state,  unsigned long& last_debounce_time, const int& debounce_delay, int& button_state)
  {
    int reading = digitalRead(button_pin);
    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:
    // If the switch changed, due to noise or pressing:
    if (reading != last_button_state) 
    {
      // reset the debouncing timer
      last_debounce_time = millis();
    }

    // https://www.norwegiancreations.com/2018/10/arduino-tutorial-avoiding-the-overflow-issue-when-using-millis-and-micros/
    if ((unsigned long)(millis() - last_debounce_time) > debounce_delay) 
    {
      // whatever the reading is at, it's been there for longer than the debounce
      // delay, so take it as the actual current state:

      // if the button state has changed:
      if (reading != button_state) 
      {
        Serial.println("changing button state");
        Serial.println(reading);
        Serial.println(button_state);
        button_state = reading;
        Serial.println(button_state);
  
      }
    }
    
    last_button_state = reading; 

    return button_state == HIGH;
   
  }
  bool is_button_1_pressed(const int& button_1_pin)
  {
    return is_button_pressed(button_1_pin, LAST_BUTTON_1_STATE,
                             LAST_DEBOUNCE_TIME_BUTTON_1,
                             DEBOUNCE_DELAY, BUTTON_1_STATE);
  }
  bool is_button_2_pressed(const int& button_2_pin)
  {
    return is_button_pressed(button_2_pin, LAST_BUTTON_2_STATE,
                             LAST_DEBOUNCE_TIME_BUTTON_2,
                             DEBOUNCE_DELAY, BUTTON_2_STATE);
  }
  
}
