#ifndef PINOUT_H
#define PINOUT_H
//SEGWAY BOARD PINOUTS
////////////////////////////////////////////////////////////
//tft pins
#define TFT_DC 34
#define TFT_RST 0
#define TFT_CS 3

//motor pins
#define DIR1 39
#define DIR2 40
#define PWM1 41
#define PWM2 42

//encoder pins
#define LEFT_ENCODER_A_PIN 21
#define LEFT_ENCODER_B_PIN 38
#define RIGHT_ENCODER_A_PIN 16
#define RIGHT_ENCODER_B_PIN 15

//POT pins
#define POT_1_PIN 1 //A0
#define POT_2_PIN 2 //A1
#define POT_3_PIN 4 //A3
#define POT_4_PIN 5 //A4

//IMU pins
#define IMU_CS 12
#define IMU_INT 13
#define IMU_RST 14
// MISO 37  
// MOSI 35
// SCK 36

//misc pins
#define LED_PIN 7
#define BAT_PIN 6
////////////////////////////////////////////////////////////

//relay pins
#define RELAY_PIN DIR1
#define SWITCH_PIN DIR2
#define CNC_LED PWM2
#define ENC_A_PIN LEFT_ENCODER_A_PIN
#define ENC_B_PIN LEFT_ENCODER_B_PIN
#define SPINDLE_IN_PIN POT_1_PIN
#define SPINDLE_OUT_PIN PWM1


#endif