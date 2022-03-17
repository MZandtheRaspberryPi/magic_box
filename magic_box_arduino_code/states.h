#ifndef STATES_H
#define STATES_H

#include <Arduino.h>

#include "lights.h"
#include "buttons.h"

namespace states
{

  // TODO: make function sig into struct
  typedef enum
  {
    STATE_INITIAL,
    STATE_LEFTDISPLAY,
    STATE_RIGHTDISPLAY,
    STATE_CENTERDISPLAY,
    STATE_LIGHTCONFIG,
    NUM_STATES
  } state_t;

  typedef state_t state_func_t(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin);

  extern state_t current_state;
  
  state_t do_init(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin);

  state_t do_left_display(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin);

  state_t do_right_display(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin);

  state_t do_center_display(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin);

  state_t do_light_config(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin);

  extern state_func_t* const STATE_TABLE[5];

  state_t run_state(state_t cur_state, const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin);

}
#endif
