#include "states.h"
#include "pin_mapping.cpp"


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

    
    FastLED.addLeds<WS2812, LED_PIN, GRB>(lights::leds, lights::NUM_LED);

    int init_index{0};
    for (int i = 0; i < lights::NUM_ROWS; i++)
    {
      if (i % 2 == 1)
      {
        for (int j = lights::NUM_COLS - 1; j >= 0; j--)
        {
          lights::led_matrix[i][j] = init_index;
          init_index++;
        }
      }
      else
      {
        for (int j = 0; j < lights::NUM_COLS; j++)
        {
          lights::led_matrix[i][j] = init_index;
          init_index++;
        }
      }
    }

    Serial.println("led matrix initialized to:");
    lights::printLEDMatrix();

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
    lights::MagicBoxLeds magic_leds{lights::NUM_LED, 20};
    while (true)
    {
      lights::show_loop_pattern(magic_leds);
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
    analogWrite(red_led_pin, 0);
    analogWrite(green_led_pin, 0);
    analogWrite(blue_led_pin, 150);
    lights::zero_leds();
    lights::MagicBoxLeds magic_leds{lights::NUM_LED, 5};
    while (true)
    {
      magic_leds.scrollTextLeft(lights::a_letter, 255, 0, 0);
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
    lights::zero_leds();
    lights::show_heart();
    while (true)
    {
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
    lights::zero_leds();
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
