#include "lathe.h"
#include "pinout.h"
#include "display.h"
#include "EncoderVelocity.h"
#include "UMS3.h"
#include <Servo.h>
#include "util.h"

bool CNC_ON = false;
bool CNC_WAS_ON = true;

float inputDuty = 0;
float outputDuty = 0;

//display
Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);
//encoder for reading spindle speed
EncoderVelocity encoder(ENC_A_PIN, ENC_B_PIN, ENC_CPR);

//microcontroller object
UMS3 ums3;

Servo spindle = Servo();

void setup(){
    //set up microcontroller LED
    ums3.begin();
    ums3.setPixelBrightness(255/3);

    Serial.begin(115200);
    displaySetup();
    //setup output pints
    pinMode(RELAY_PIN, OUTPUT);
    pinMode(CNC_LED, OUTPUT);
    pinMode(SPINDLE_OUT_PIN, OUTPUT);
    //setup input pins
    pinMode(SWITCH_PIN, INPUT_PULLUP);
    pinMode(SPINDLE_IN_PIN, INPUT);

    //display configuration
    tft.setTextWrap(false);
    tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
}

void loop(){
    CNC_ON = digitalRead(SWITCH_PIN);
    EVERY_N_MILLIS(10){
        if (CNC_ON){
            //if this is the first time the CNC is turned on.
            if (!CNC_WAS_ON){
                CNC_WAS_ON = true;
                //clear the display if you turn the CNC on
                tft.fillScreen(ST77XX_WHITE);
                tft.setCursor(0,0);
                tft.setTextColor(ST77XX_ORANGE);
                tft.setTextSize(8);
                tft.println("CNC");
                tft.setTextSize(3);
                tft.setTextColor(ST77XX_BLACK, ST77XX_WHITE);
            }
            //Connect the stepper drivers to the motors
            digitalWrite(RELAY_PIN, HIGH);
            //Turn on the CNC LED
            digitalWrite(CNC_LED, HIGH);
            ums3.setPixelColor(0,0,255);
            //read the analog spindle speed
            inputDuty = overSamplePot(SPINDLE_IN_PIN, 10);
            //Scale the input duty cycle to the output duty cycle
            outputDuty = constrain(inputDuty * 1.0, 0,1);;
            //write the spindle speed to the spindle output
            int ouputPPM = mapDouble(outputDuty, 0, 1, MIN_PPM_ANGLE, MAX_PPM_ANGLE);
            spindle.write(SPINDLE_OUT_PIN, ouputPPM);

    
        } else {
            if (CNC_WAS_ON){
                //If the CNC was on, reset the encoder position
                //makes sue the spindle speed is 0 when the CNC is turned off
                encoder.resetPosition();
                CNC_WAS_ON = false;
                tft.fillScreen(ST77XX_BLACK);
                tft.setCursor(0,0);
                tft.setTextColor(ST77XX_GREEN);
                tft.setTextSize(5);
                tft.println("MANUAL");
                tft.setTextSize(3);
                tft.setTextColor(ST77XX_WHITE, ST77XX_BLACK);
            }       

            //Disconnect the stepper drivers from the motors
            digitalWrite(RELAY_PIN, LOW);
            //Change the CNC LED to off
            ums3.setPixelColor(255,0,0); //red
            digitalWrite(CNC_LED, LOW);
            //read the encoder to determine spindle speed
            //get angle in radians
            float encAngle = encoder.getPosition();
            encAngle = constrain(encAngle, 0, MAX_ENC_ANGLE);
            outputDuty = mapDouble(encAngle, 0, MAX_ENC_ANGLE, 0.0, 1.0);
        }        
    }
    EVERY_N_MILLIS(DISPLAY_DELAY_MILLIS){
        //print the spindle speed and CNC mode to the display
        tft.setCursor(0,200);
        tft.setTextSize(3);
        tft.printf("Spindle: %.2f      \n", outputDuty);
        Serial.println(encoder.getPosition());
    }


}

float overSamplePot(int8_t pin, int8_t numSamples){
    float val = 0;
    for(int i = 0; i < numSamples; i++){
        val += analogRead(pin);
    }
    val /= numSamples;

    return val/MAX_ANALOG_READ;
}
