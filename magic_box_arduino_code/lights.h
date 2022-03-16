#ifndef LIGHTS_H
#define LIGHTS_H

#include <Arduino.h>
#include <FastLED.h>

namespace lights
{

  const int NUM_ROWS{5};
  const int NUM_COLS{6};
  const int NUM_LED{NUM_ROWS * NUM_COLS};
  extern CRGB leds[];

  extern int led_matrix[NUM_ROWS][NUM_COLS];

  extern bool a_letter[NUM_ROWS][3];
  
  void show_left_pattern();

  class MagicBoxLeds
  {
    public:
      MagicBoxLeds(int num_leds, int loop_rate_hz);
      void walkLEDArray();
      void MagicBoxLeds::scrollTextLeft(bool letter[5][3], int r, int g, int b);
    private:
      bool isTimeToUpdate();
      unsigned long last_led_change_time{0};
      int num_leds_;
      int loop_rate_hz_;
      int current_index_{0};
    
  };

  void show_loop_pattern(MagicBoxLeds& magic_leds);

  void zero_leds();
  void show_heart();

  void printLEDMatrix();
}

#endif
