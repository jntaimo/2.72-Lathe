#include <Arduino.h>
#include "pinout.h"
//This code reads a switch and outputs the state to the onboard LED

void setup(){
    Serial.begin(115200);
    Serial.println("Switch Test");
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
    int val = digitalRead(SWITCH_PIN);
    Serial.println(val);
    digitalWrite(LED_BUILTIN, val);
    delay(100);
}