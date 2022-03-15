#include "lights.h"


namespace lights
{
  const int NUM_LED = 30;
  CRGB leds[NUM_LED];
  void show_left_pattern()
  {
    leds[0] = CRGB(255, 0, 0);
    FastLED.show();
    leds[1] = CRGB(0, 255, 0);
    FastLED.show();
    leds[2] = CRGB(0, 0, 255);
    FastLED.show();
  }
 
  MagicBoxLeds::MagicBoxLeds(int num_leds, int loop_rate_hz) : num_leds_(num_leds), loop_rate_hz_(loop_rate_hz)
  {
    
  }
  void MagicBoxLeds::getLedsArray(CRGB* led)
  {
    if (millis() - last_led_change_time > (((float)1 / loop_rate_hz_) * 1000))
    {
      last_led_change_time = millis();
      CRGB* old_led = led + current_index_;
      *old_led = CRGB(0, 0, 0);
      current_index_++;
      if (current_index_ > num_leds_)
      {
        current_index_ = 0;
      }
      CRGB* nextLed = led + current_index_;
      *nextLed = CRGB(255, 0, 0);
    }
  }

  MagicBoxLeds magic_leds{NUM_LED, 20};
  void show_loop_pattern()
  {
    magic_leds.getLedsArray(leds);
    FastLED.show();
  }


}
