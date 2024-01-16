///* 
// * Trigger LIGHT for 10 second AMPLIFY period in FRC Crescendo game 
// * and Display elapsed time 
// * jerryleblanc56 2024
// * LED backpack HT16K33 
// * https://learn.adafruit.com/adafruit-led-backpack/0-dot-56-seven-segment-backpack-arduino-setup 
// * A5 Connect CLK to the I2C clock - on Arduino UNO thats Analog #5 
// * A4 Connect DAT to the I2C data - on Arduino UNO thats Analog #4 
// */
// */
// 
///*************************************************** 
//  This is a library for our I2C LED Backpacks
//
//  Designed specifically to work with the Adafruit LED 7-Segment backpacks 
//  ----> http://www.adafruit.com/products/881
//  ----> http://www.adafruit.com/products/880
//  ----> http://www.adafruit.com/products/879
//  ----> http://www.adafruit.com/products/878
//
//  These displays use I2C to communicate, 2 pins are required to 
//  interface. There are multiple selectable I2C addresses. For backpacks
//  with 2 Address Select pins: 0x70, 0x71, 0x72 or 0x73. For backpacks
//  with 3 Address Select pins: 0x70 thru 0x77
//
//  Adafruit invests time and resources providing this open source code, 
//  please support Adafruit and open-source hardware by purchasing 
//  products from Adafruit!
//
//  Written by Limor Fried/Ladyada for Adafruit Industries.  
//  BSD license, all text above must be included in any redistribution
// ****************************************************/

#define SWITCH_PIN 2
#define LED_PIN 6
#define VIRTUAL_SECOND 998
#define AMP_DURATION 10000 
long int amp_start_time=0;
long int amp_stop_time=0;

// Enable one of these two #includes and comment out the other.
// Conditional #include doesn't work due to Arduino IDE shenanigans.
#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
//#include <TinyWireM.h> // Enable this line if using Adafruit Trinket, Gemma, etc.
#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"
Adafruit_7segment matrix = Adafruit_7segment();

#include "Adafruit_VCNL4010.h"
Adafruit_VCNL4010 vcnl;
//#define PROX_POWER A2   // Pin to supply power to proximity sensor VCNL4010 
void setupProximitySensor() {
//  digitalWrite(PROX_POWER, HIGH);
  Serial.println("VCNL4010 test");
  if (! vcnl.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.println("Found VCNL4010");
}

void setup() {
//#ifndef __AVR_ATtiny85__
  Serial.begin(9600);
  Serial.println("Control Amplify Light on Crescendo Game");
//#endif
  matrix.begin(0x70);
  display(0);
  // pin mode
  digitalWrite(LED_PIN, LOW);
//  setupProximitySensor();
}

void display(uint16_t n) {
//    Serial.println(n);
    matrix.println(n);
    matrix.writeDisplay();
}

void loop() {
  if( digitalRead(SWITCH_PIN) == HIGH ) {
    amp_start_time = millis();
    digitalWrite(LED_PIN, HIGH);
    Serial.println("START AMPLIFY");
    uint16_t counter = 10;
    while( millis() < amp_start_time + AMP_DURATION ) {
      Serial.println(millis());
      display(counter--);
      delay(VIRTUAL_SECOND);
    }
    digitalWrite(LED_PIN, LOW);
    amp_stop_time = millis();
    Serial.print("STOP AMP after (msec) ");
    Serial.println(amp_stop_time - amp_start_time);
    display(counter);
  }
  delay(10);
}
