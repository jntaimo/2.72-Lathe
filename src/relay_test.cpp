#include <Arduino.h>
#include "pinout.h"
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
    digitalWrite(RELAY_PIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
    delay(2000);                      // wait for a second
    digitalWrite(RELAY_PIN, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
    delay(1000);                      // wait for a second
}