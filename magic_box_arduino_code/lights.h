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
  extern bool d_letter[NUM_ROWS][3];
  extern bool h_letter[NUM_ROWS][3];
  extern bool i_letter[NUM_ROWS][3];
  extern bool m_letter[NUM_ROWS][3];
  extern bool n_letter[NUM_ROWS][3];
  extern bool r_letter[NUM_ROWS][3];
  extern bool s_letter[NUM_ROWS][3];
  extern bool u_letter[NUM_ROWS][3];
  extern bool y_letter[NUM_ROWS][3];
  extern bool z_letter[NUM_ROWS][3];

  extern byte GLOBAL_R;
  extern byte GLOBAL_G;
  extern byte GLOBAL_B;
    
  void show_left_pattern();

  class MagicBoxLeds
  {
    public:
      MagicBoxLeds(int num_leds, int loop_rate_hz);
      void walkLEDArray(int r, int g, int b);
      bool MagicBoxLeds::scrollTextLeft(bool letter[5][3], int r, int g, int b);
      bool MagicBoxLeds::scrollLetter(int letter, int r, int g, int b);
      void reset();
      void blinkLight(int pin, byte intensity, bool& on);
    private:
      bool isTimeToUpdate();
      unsigned long last_led_change_time{0};
      int num_leds_;
      int loop_rate_hz_;
      int current_index_{0};
    
  };

  void show_loop_pattern(MagicBoxLeds& magic_leds, int r, int g, int b);

  void zero_leds();
  void show_heart();

  void printLEDMatrix();
}

#endif
