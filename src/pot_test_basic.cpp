#include <Arduino.h>
#include "pinout.h"

void setup(){
    Serial.begin(115200);
    Serial.println("Potentiometer Test");
    pinMode(KNOB_PIN, INPUT);
}

void loop(){
    int val = analogRead(KNOB_PIN);
    Serial.println(val);
    delay(100);
}