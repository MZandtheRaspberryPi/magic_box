#include "pin_mapping.cpp"
#include "states.h"
#include "lights.h"

#define LED_PIN     A2

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(lights::leds, lights::NUM_LED);
  states::current_state = states::do_init(RED_LED, GREEN_LED, BLUE_LED, BUTTON1, BUTTON2);
}

void loop() {
  states::current_state = states::run_state(states::current_state, RED_LED, GREEN_LED,
                                            BLUE_LED, BUTTON1, BUTTON2);
}
