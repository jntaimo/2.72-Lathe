#ifndef LATHE_H
#define LATHE_H
#include <Arduino.h>
#define ENC_CPR 250
#define MAX_ANALOG_READ 1023
#define MIN_PPM_ANGLE 0
#define MAX_PPM_ANGLE 180
#define DISPLAY_DELAY_MILLIS 100
#define MAX_ENC_ANGLE 8*2*PI
float overSamplePot(int8_t pin, int8_t numSamples);

#endif