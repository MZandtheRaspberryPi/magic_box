#include "pin_mapping.cpp"
#include "states.h"


void setup() {
  Serial.begin(9600);
  states::current_state = states::do_init(RED_LED, GREEN_LED, BLUE_LED, BUTTON1, BUTTON2);
}

void loop() {
  states::current_state = states::run_state(states::current_state, RED_LED, GREEN_LED,
                                            BLUE_LED, BUTTON1, BUTTON2);
}
