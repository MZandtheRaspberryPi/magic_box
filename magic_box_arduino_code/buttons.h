#ifndef BUTTONS_H
#define BUTTONS_H

#include <Arduino.h>

namespace buttons
{

  extern int BUTTON_1_STATE;             // the current reading from the input pin
  extern int LAST_BUTTON_1_STATE;   // the previous reading from the input pin
  extern int BUTTON_2_STATE;             // the current reading from the input pin
  extern int LAST_BUTTON_2_STATE;   // the previous reading from the input pin

  extern unsigned long LAST_DEBOUNCE_TIME_BUTTON_1;  // the last time the output pin was toggled
  extern unsigned long LAST_DEBOUNCE_TIME_BUTTON_2;  // the last time the output pin was toggled
  extern unsigned long DEBOUNCE_DELAY;    // the debounce time; increase if the output flickers 

  bool is_button_pressed(const int& button_pin, int& last_button_state,  unsigned long& last_debounce_time, const int& debounce_delay, int& button_state);
  bool is_button_1_pressed(const int& button_1_pin);
  bool is_button_2_pressed(const int& button_2_pin);

}

#endif
