/*********************************************************
This is a library for the MPR121 12-channel Capacitive touch sensor

Designed specifically to work with the MPR121 Breakout in the Adafruit shop 
  ----> https://www.adafruit.com/products/

These sensors use I2C communicate, at least 2 pins are required 
to interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution
**********************************************************/

#include <Wire.h>
#include "Adafruit_MPR121.h"

#ifndef _BV
#define _BV(bit) (1 << (bit)) 
#endif

Adafruit_MPR121 cap = Adafruit_MPR121();

int Led[] = {3, 4, 5, 6, 7};
int numTouched = 0;

void setup() {
  for (int count = 0; count < 5; count++) {
    pinMode(Led[count], OUTPUT);
  }

  Serial.begin(9600);

  while (!Serial) {
    delay(10);
  }

  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
}

void loop() {
  uint16_t currtouched = cap.touched();
  numTouched = 0;

  for (int i = 0; i < 5; i++) {
    if (currtouched & _BV(i)) {
      numTouched++;
    }
  }

  if (numTouched > 1) {
    for (int i = 0; i < 5; i++) {
      digitalWrite(Led[i], HIGH);
    }
  } else {
    for (int i = 0; i < 5; i++) {
      digitalWrite(Led[i], LOW);
    }
  }

  delay(100); // Delay to avoid rapid LED state changes

  numTouched = 0;
}


