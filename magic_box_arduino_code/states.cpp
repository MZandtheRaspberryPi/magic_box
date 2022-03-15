#include "states.h"


namespace states
{
  state_t current_state = STATE_INITIAL;

  state_func_t* const STATE_TABLE[NUM_STATES] = {do_init, do_left_display, do_right_display, do_center_display, do_light_config};
  
  state_t do_init(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin)
  {
    Serial.println("In do_init");
     //Declaring LED pin as output
    pinMode(red_led_pin, OUTPUT);
     //Declaring LED pin as output
    pinMode(green_led_pin, OUTPUT);
     //Declaring LED pin as output
    pinMode(blue_led_pin, OUTPUT);
  
    // initialize the pushbutton1 pin as an input:
    pinMode(button_1_pin, INPUT);
  
    // initialize the pushbutton2 pin as an input:
    pinMode(button_2_pin, INPUT);

    return STATE_LEFTDISPLAY;
  }

  state_t do_left_display(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin)
  {
    Serial.println("In do_left_display");
    analogWrite(red_led_pin, 150);
    analogWrite(green_led_pin, 0);
    analogWrite(blue_led_pin, 0);
    while (true)
    {
      lights::show_loop_pattern();
      bool left = buttons::is_button_1_pressed(button_1_pin);
      bool right = buttons::is_button_2_pressed(button_2_pin);
      if (left && right)
      {
        break;
      }
    }
    return STATE_RIGHTDISPLAY;
  }


  state_t do_right_display(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin)
  {
    Serial.println("In do_right_display");
    analogWrite(red_led_pin, 0);
    analogWrite(green_led_pin, 0);
    analogWrite(blue_led_pin, 150);
    while (true)
    {
      lights::show_left_pattern();
      bool left = buttons::is_button_1_pressed(button_1_pin);
      bool right = buttons::is_button_2_pressed(button_2_pin);
      if (left && right)
      {
        break;
      }
    }
    return STATE_CENTERDISPLAY;
  }

  state_t do_center_display(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin)
  {
    Serial.println("In do_center_display");
    analogWrite(red_led_pin, 0);
    analogWrite(green_led_pin, 150);
    analogWrite(blue_led_pin, 0);
    while (true)
    {
      lights::show_left_pattern();
      bool left = buttons::is_button_1_pressed(button_1_pin);
      bool right = buttons::is_button_2_pressed(button_2_pin);
      if (left && right)
      {
        break;
      }
    }
    return STATE_LIGHTCONFIG;
  }

  state_t do_light_config(const int& red_led_pin, const int& green_led_pin,
                          const int& blue_led_pin, const int& button_1_pin,
                          const int& button_2_pin)
  {
    Serial.println("In do_light_config");
    analogWrite(red_led_pin, 130);
    analogWrite(green_led_pin, 130);
    analogWrite(blue_led_pin, 130);
    while (true)
    {
      lights::show_left_pattern();
      bool left = buttons::is_button_1_pressed(button_1_pin);
      bool right = buttons::is_button_2_pressed(button_2_pin);
      if (left && right)
      {
        break;
      }
    }
    return STATE_LEFTDISPLAY;
  }

  state_t run_state(state_t cur_state, const int& red_led_pin, const int& green_led_pin,
                        const int& blue_led_pin, const int& button_1_pin,
                        const int& button_2_pin)
  {

    state_t new_state = STATE_TABLE[ cur_state ]( red_led_pin, green_led_pin,
                                                  blue_led_pin, button_1_pin,
                                                  button_2_pin);
    Serial.println("switching state");
    while ((buttons::is_button_1_pressed(button_1_pin) || buttons::is_button_2_pressed(button_2_pin)))
    {
      Serial.println("delaying state change");
      delay(10);
    }
    return new_state;
  }
}
