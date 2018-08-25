/* 
 *  this program use arduino pro mini pin 0 and pin 1 for LED
 *  remove LED or anything on pin 0 and pin 1
 *  before serial communication.
 * 
 *  on the other hand, remove serial ports before using arduino
 *  pro mini pin 0 and pin 1.
 *  
 *  程式代號: Receiver.h
 *  程式名稱: Obstacle Avoiding Car receiver
 *  程式功能: Receiving xbox controller's wifi message to control the car
 *  2018.08.26
 */
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <RF24.h>
#include "pitches.h"
#include "songs.h"

#ifdef __AVR__

  #include <avr/power.h>

#endif

#define EnableLR  9       // Enable Pin for motor 1 (control Left&Right)
#define EnableFB  10      // Enable Pin for motor 2 (control Front&Back)
#define tL        2       // Control pin 1 for motor 1 (Turn Left)
#define tR        7       // Control pin 2 for motor 1 (Turn Right)
#define tF        A3      // Control pin 1 for motor 2 (Turn Front)
#define tB        A0      // Control pin 2 for motor 2 (Turn Back)
#define sensor1   A4      // HC-SR04 front model
#define sensor2   A5      // HC-SR04 back model
#define Dout      1       // LED data pin
#define signalL   0       // signal light
/*signal status
 * blink : when receive message from Nrf24
 * blink twice: when start
 * always on : enable HC-SR04
 * always off : auto mode
 */

/* declaring car light pins */
#define frontL    6
#define frontR    5
#define backL     8
#define backR     4

/* declaring tonePin */
#define tonePin   3

char song[450];

/* declaring NeoPixels */
Adafruit_NeoPixel cjmcu = Adafruit_NeoPixel(32, Dout, NEO_GRB + NEO_KHZ800);

/* declaring WiFi Receiver */
RF24 rf24(A2, A1);        // CE pin, CSN pin
const uint64_t addr;
const byte pipe = 1;      // 0~5
long msg = 0;             // wifi msg

/* store buttons and car's status */
uint8_t Mode = 1;         // Mode 1 2 3
uint8_t xButton = 0;      // store the button value
uint8_t carMode = 0;      // 0: auto mode, 1: manual mode, 2: turnfront, 3: turnback
bool isPress = false;     // control button on and off

/* recording the time when function start */
unsigned long nowtime = 0;

/* for randomly select functions */
typedef void (*functionCallback)(int);
functionCallback functions[];

void setLEDpin();
void setNeoPixel();
void setNrf24();
void setRGB(uint8_t r, uint8_t g, uint8_t b);
void setTone();
void setPinsVal(uint8_t pin1, uint8_t pin2, uint8_t value);
void setHalfBright(uint8_t pin1, uint8_t pin2);
void resetLED();
void resetPixel();
void resetSong();
void resetAll();
void frontLight();
void backLight();
void lrLight(uint8_t light1, uint8_t light2);
void redMode();
void yellowMode();
void greenMode();
void blueMode();
void changeDirection(uint8_t t1, uint8_t t2);
void stopMotor();
void runMotor(uint8_t LR, uint8_t FB); // Drive Motor in PWM
void brakes(uint8_t m);
void enableHCSR04();
bool distance(uint8_t m);
void whileReceiveMSG();
void Horn(char *p);
void colorWipe(uint8_t wait);      // Fill the dots one after the other with a color
void colorWipeCycle(uint8_t wait); // LEDs are turned color1 in sequence, then turned color2 in sequence
void rainbow(uint8_t wait);        // Cycles all LEDs at once through a rainbow
void rainbowCycle(uint8_t wait);   // Slightly different, this makes the rainbow equally distributed throughout
void theaterChase(uint8_t wait);   // Theatre-style crawling lights
void theaterChaseRainbow(uint8_t wait); // Theatre-style crawling lights with rainbow effect
void random_color();               // Lights all LEDs in one random color up
void multi_dynamic();              // Lights every LED in a random color
uint32_t Wheel(byte WheelPos);     // The colors are a transition r - g - b - back to r
void colorCycle();
void manualMode();
void autoMode();
void setup();
void loop();