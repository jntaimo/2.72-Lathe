#include <Arduino.h>
#include "pinout.h"
#include <Servo.h>

Servo myservo = Servo();


void setup() {
    pinMode(SPINDLE_OUT_PIN, OUTPUT);
}

void loop() {
  for (int pos = 0; pos <= 180; pos++) {  // go from 0-180 degrees
    myservo.write(SPINDLE_OUT_PIN, pos);        // set the servo position (degrees)
    delay(15);
  }
  for (int pos = 180; pos >= 0; pos--) {  // go from 180-0 degrees
    myservo.write(SPINDLE_OUT_PIN, pos);        // set the servo position (degrees)
    delay(15);
  }
}
