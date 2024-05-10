#include <Arduino.h>
#include "pinout.h"

float overSamplePot(int8_t numSamples);

void setup(){
    Serial.begin(115200);
    Serial.println("Potentiometer Test Advanced");
    pinMode(KNOB_PIN, INPUT);

}

void loop(){
    Serial.println(overSamplePot(10));
    delay(100);
}

float overSamplePot(int8_t numSamples){
    float val = 0;
    for(int i = 0; i < numSamples; i++){
        val += analogRead(KNOB_PIN);
    }
    val /= numSamples;

    return val/MAX_ANALOG_READ;
}