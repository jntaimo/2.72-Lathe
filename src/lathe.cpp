#include <Arduino.h>
#include "pinout.h"
#include <PulsePosition.h>
//This code reads a switch and outputs the state to the onboard LED
PulsePositionOutput spindle;
bool CNC_MODE = false;
float overSampleRead(int8_t pin, int8_t numSamples);

void setup(){
    Serial.begin(115200);
    spindle.begin(SPINDLE_OUT_PIN);
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(KNOB_PIN, INPUT);
    pinMode(SPINDLE_IN_PIN, INPUT);
    pinMode(SPINDLE_OUT_PIN, OUTPUT);
}

void loop(){
    CNC_MODE = digitalRead(SWITCH_PIN);
    //CNC MODE
    if (CNC_MODE){
        digitalWrite(RELAY_PIN, HIGH);
        digitalWrite(LED_BUILTIN, HIGH);
        //Analog read the spindle speed from Arduino
        float cncSpeed = overSampleRead(SPINDLE_IN_PIN, 10);
        //Write the speed to the PPM signal
        spindle.write(1, 1000);

    } else {
        //MANUAL MODE
        digitalWrite(RELAY_PIN, LOW);
        digitalWrite(LED_BUILTIN, LOW);
        //read the knob to control spindle speeed
        float speed = overSampleRead(KNOB_PIN, 10);
        //write the speed PPM signal
        Serial.println(speed);
        //TODO write the speed to the PPM signal
    }
    delay(10);
}

float overSampleRead(int8_t pin, int8_t numSamples){
    float val = 0;
    for(int i = 0; i < numSamples; i++){
        val += analogRead(pin);
    }
    val /= numSamples;

    return val/MAX_ANALOG_READ;
}