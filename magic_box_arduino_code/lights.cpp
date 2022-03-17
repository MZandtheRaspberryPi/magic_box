#include "lights.h"


namespace lights
{
  CRGB leds[NUM_LED];
  int led_matrix[NUM_ROWS][NUM_COLS];
  bool a_letter[5][3] =
  {
      {false, true, false},
      {true, false, true},
      {true, true, true},
      {true, false, true},
      {true, false, true}
  };

  bool d_letter[NUM_ROWS][3] =
  {
      {true, true, false},
      {true, false, true},
      {true, false, true},
      {true, false, true},
      {true, true, false}
  };
  bool h_letter[NUM_ROWS][3] =
  {
      {true, false, true},
      {true, false, true},
      {true, true, true},
      {true, false, true},
      {true, false, true}
  };

  bool i_letter[NUM_ROWS][3] =
  {
      {true, true, true},
      {false, true, false},
      {false, true, false},
      {false, true, false},
      {true, true, true}
  };
  bool m_letter[NUM_ROWS][3] =
  {
      {true, false, true},
      {true, true, true},
      {true, true, true},
      {true, false, true},
      {true, false, true}
  };
  bool n_letter[NUM_ROWS][3] =
  {
      {true, false, true},
      {true, true, true},
      {true, true, true},
      {true, false, true},
      {true, false, true}
  };
  bool r_letter[NUM_ROWS][3] =
  {
      {true, true, true},
      {true, false, true},
      {true, true, true},
      {true, true, false},
      {true, false, true}
  };
  bool s_letter[NUM_ROWS][3] =
  {
      {true, true, true},
      {true, false, false},
      {true, true, true},
      {false, false, true},
      {true, true, true}
  };
  bool u_letter[NUM_ROWS][3] =
  {
      {true, false, true},
      {true, false, true},
      {true, false, true},
      {true, false, true},
      {true, true, true}
  };

  bool y_letter[NUM_ROWS][3] =
  {
      {true, false, true},
      {true, true, true},
      {false, true, false},
      {false, true, false},
      {false, true, false}
  };

  bool z_letter[NUM_ROWS][3] =
  {
      {true, true, true},
      {false, false, true},
      {false, true, false},
      {true, false, false},
      {true, true, true}
  };



  
  void show_left_pattern()
  {
    leds[0] = CRGB(255, 0, 0);
    FastLED.show();
    leds[1] = CRGB(0, 255, 0);
    FastLED.show();
    leds[2] = CRGB(0, 0, 255);
    FastLED.show();
  }

  void zero_leds()
  {
    Serial.println("clearing lights");
    int index{0};
    for (int i = 0; i < lights::NUM_ROWS; i++)
    {
      for (int j = 0; j < lights::NUM_COLS; j++)
      {
        index = led_matrix[i][j];
        leds[index] = CRGB(0, 0, 0);
      }
    }
    FastLED.show();
  }

  void show_heart()
  {
    int index{0};
    // first row of 30 pixel heart
    index = led_matrix[0][1];
    leds[index] = CRGB(255, 0, 0);
    index = led_matrix[0][4];
    leds[index] = CRGB(255, 0, 0);

    // next 2 rows are all lit up
    for (int i = 1; i < 3; i++)
    {
      for (int j = 0; j < lights::NUM_COLS; j++)
      {
        index = led_matrix[i][j];
        leds[index] = CRGB(255, 0, 0);
      }
    }

    for (int j = 1; j < 5; j++)
    {
      index = led_matrix[3][j];
      leds[index] = CRGB(255, 0, 0);
    }

    index = led_matrix[4][2];
    leds[index] = CRGB(255, 0, 0);
    index = led_matrix[4][3];
    leds[index] = CRGB(255, 0, 0);
    FastLED.show();
  }
 
  MagicBoxLeds::MagicBoxLeds(int num_leds, int loop_rate_hz) : num_leds_(num_leds), loop_rate_hz_(loop_rate_hz)
  {
    
  }

  void MagicBoxLeds::reset()
  {
      last_led_change_time = 0;
      current_index_ = 0;
  }

  bool MagicBoxLeds::scrollLetter(int letter, int r, int g, int b)
  {
    switch(letter)
    {
    case 97: {  
               return scrollTextLeft(a_letter, r, g, b);
               break;
            }
    case 100: {  
           return scrollTextLeft(d_letter, r, g, b);
           break;
        } 
    case 104: {  
           return scrollTextLeft(h_letter, r, g, b);
           break;
        } 
    case 105: {  
           return scrollTextLeft(i_letter, r, g, b);
           break;
        } 
    case 109: {  
           return scrollTextLeft(m_letter, r, g, b);
           break;
        } 
    case 110: {  
           return scrollTextLeft(n_letter, r, g, b);
           break;
        } 
    case 114: {  
           return scrollTextLeft(r_letter, r, g, b);
           break;
        } 
    case 115: {  
           return scrollTextLeft(s_letter, r, g, b);
           break;
        } 
    case 117: {  
           return scrollTextLeft(u_letter, r, g, b);
           break;
        } 
    case 121: {  
           return scrollTextLeft(y_letter, r, g, b);
           break;
        } 
    case 122: {  
           return scrollTextLeft(z_letter, r, g, b);
           break;
        } 
    default: {
             return false;
             break;
            }
    }
  }
  bool MagicBoxLeds::scrollTextLeft(bool letter[5][3], int r, int g, int b)
  {
    if (isTimeToUpdate())
    {
      zero_leds();
      // we want to scroll all the way off the screen, so permit starting on 6 - 8, -2, as we will add 2 to it and get to 0
      if (current_index_ > 8)
      {
        return true;
      }
      else
      {
        current_index_ += 1;
      }
      int led_index;
      // iterating over 3 letter cols
      int starting_col = NUM_COLS - current_index_;
      for (int j = 0; j < 3; j++)
      {
        if (starting_col + j > NUM_COLS - 1 || starting_col + j < 0)
        {
          continue;
        }
        for (int i = 0; i < NUM_ROWS; i++)
        {
          if (letter[i][j])
          {
            led_index = lights::led_matrix[i][starting_col + j];
            leds[led_index] = CRGB(r, g, b);
          } 
        }
      }
      
    }
    FastLED.show();
    return false;
  }

  bool MagicBoxLeds::isTimeToUpdate()
  {
    if (millis() - last_led_change_time > (((float)1 / loop_rate_hz_) * 1000))
    {
      last_led_change_time = millis();
      return true;
    }
    else
    {
      return false;
    }
    
  }
  void MagicBoxLeds::walkLEDArray()
  {
    if (isTimeToUpdate())
    {
      leds[current_index_] = CRGB(0, 0, 0);
      current_index_++;
      if (current_index_ == num_leds_)
      {
        current_index_ = 0;
      }
      leds[current_index_] = CRGB(255, 0, 0);
    }
    FastLED.show();
  }


  void show_loop_pattern(MagicBoxLeds& magic_leds)
  {
    magic_leds.walkLEDArray();
  }


  void printLEDMatrix()
  {
    for (int i = 0; i < lights::NUM_ROWS; i++)
    {
      for (int j = 0; j < lights::NUM_COLS; j++)
      {
        Serial.println( lights::led_matrix[i][j]);
      }
    }
  }

}
