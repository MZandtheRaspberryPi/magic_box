#ifndef LIGHTS_H
#define LIGHTS_H

#include <Arduino.h>
#include <FastLED.h>

namespace lights
{
  extern const int NUM_LED;
  extern CRGB leds[];
  void show_left_pattern();

  class MagicBoxLeds
  {
    public:
      MagicBoxLeds(int num_leds, int loop_rate_hz);
      void getLedsArray(CRGB* leds);
    private:
      unsigned long last_led_change_time{0};
      int num_leds_;
      int loop_rate_hz_;
      int current_index_{0};
    
  };

  void show_loop_pattern();
}

#endif
