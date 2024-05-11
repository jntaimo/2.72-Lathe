#include <Arduino.h>
#include "pinout.h"
//This code reads a switch and outputs the state to the onboard LED

void setup(){
    pinMode(SWITCH_PIN, INPUT_PULLUP);
      pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
    if (digitalRead(SWITCH_PIN)){
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
    } else {
        digitalWrite(RELAY_PIN, LOW);
        digitalWrite(LED_BUILTIN, LOW);
    }
    delay(10);
}
