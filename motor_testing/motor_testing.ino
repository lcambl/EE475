#include <Wire.h>             // For using I2C communication
#include "Adafruit_DRV2605.h" // For interfacing with the DRV2605 chip
#include <Wireling.h>

// Vibration motor setup
Adafruit_DRV2605 drv;   // The variable used to interface with the DRV2605 chip
uint8_t effect = 1;     // The global variable used to keep track of effects

const int SIZE = 6;

int arr[SIZE] = { 47, 48, 49, 50, 51 }; 
int itr = 0;
int i = 0;

void setup() {
  Serial.begin(115200);

  // Vibration Motor Setup
  Wireling.begin();
  drv.begin();
  drv.selectLibrary(1); // LRA library
  drv.setMode(DRV2605_MODE_INTTRIG); // internal I2C trigger, send go command 
  drv.useLRA();
}

void loop() {
  // cycle through all effects, 1-46 for clicks
  // effect = arr[i];
  // Serial.print("changing effect to:");
  // Serial.println(effect);
  // drv.setWaveform(0, effect);  // Set effect
  // drv.setWaveform(1, 0);       // End waveform
  // //drv.go();
  // //delay(10);

  // while (itr <= 10000) {
  //   drv.go();
  //   //delay(5);
  //   itr++;
  // }

  // delay(2000);
  
  // itr = 0;
  // i++;

  // if (i > SIZE-1) {
  //   i = 0;
  // }

  // // for testing ranges:
  // effect = 64;
  // Serial.println("Test effect 64");
  // drv.setWaveform(0, effect);
  // drv.setWaveform(1, effect);
  // drv.setWaveform(2, effect);
  // drv.setWaveform(3, effect);
  // drv.setWaveform(4, effect);
  // drv.setWaveform(5, 0);
  // drv.go();
  // delay(5000);

  // effect = 65;
  // Serial.println("Test effect 65");
  // drv.setWaveform(0, effect);
  // drv.setWaveform(1, effect);
  // drv.setWaveform(2, effect);
  // drv.setWaveform(3, effect);
  // drv.setWaveform(4, effect);
  // drv.setWaveform(5, 0);
  // drv.go();
  // delay(5000);

  // effect = 66;
  // Serial.println("Test effect 66");
  // drv.setWaveform(0, effect);
  // drv.setWaveform(1, effect);
  // drv.setWaveform(2, effect);
  // drv.setWaveform(3, effect);
  // drv.setWaveform(4, effect);
  // drv.setWaveform(5, 0);
  // drv.go();
  // delay(5000);

  // effect = 67;
  // Serial.println("Test effect 67");
  // drv.setWaveform(0, effect);
  // drv.setWaveform(1, effect);
  // drv.setWaveform(2, effect);
  // drv.setWaveform(3, effect);
  // drv.setWaveform(4, effect);
  // drv.setWaveform(5, 0);
  // drv.go();
  // delay(5000);

  // effect = 68;
  // Serial.println("Test effect 68");
  // drv.setWaveform(0, effect);
  // drv.setWaveform(1, effect);
  // drv.setWaveform(2, effect);
  // drv.setWaveform(3, effect);
  // drv.setWaveform(4, effect);
  // drv.setWaveform(5, 0);
  // drv.go();
  // delay(5000);

  // effect = 69;
  // Serial.println("Test effect 69");
  // drv.setWaveform(0, effect);
  // drv.setWaveform(1, effect);
  // drv.setWaveform(2, effect);
  // drv.setWaveform(3, effect);
  // drv.setWaveform(4, effect);
  // drv.setWaveform(5, 0);
  // drv.go();
  // delay(5000);

  // for (int i = 119; i < 124; i++) {
  //   Serial.print("Test effect ");
  //   Serial.println(i);
  //   drv.setWaveform(0, i);
  //   drv.setWaveform(1, i);
  //   drv.setWaveform(2, i);
  //   drv.setWaveform(3, i);
  //   drv.setWaveform(4, i);
  //   drv.setWaveform(5, 0);
  //   drv.go();
  //   delay(5000);
  // }

  // drv.setWaveform(0, 119);
  // drv.setWaveform(1, 119);
  // drv.setWaveform(2, 119);
  // drv.setWaveform(3, 119);
  // drv.setWaveform(4, 119);
  // drv.setWaveform(5, 0);
  // drv.go();
  // delay(5000);

  // drv.setWaveform(0, 64);
  // drv.setWaveform(1, 64);
  // drv.setWaveform(2, 64);
  // drv.setWaveform(3, 64);
  // drv.setWaveform(4, 64);
  // drv.setWaveform(5, 0);
  // drv.go();
  // delay(5000);

  // HIGH THRESHOLD
  Serial.println("Max buzz - very very bad dog");
  drv.setWaveform(0, 47);
  drv.setWaveform(1, 47);
  drv.setWaveform(2, 47);
  drv.setWaveform(3, 47);
  drv.setWaveform(4, 47);
  drv.setWaveform(5, 47);
  drv.setWaveform(6, 47);
  drv.setWaveform(7, 47);
  drv.setWaveform(8, 47);
  drv.setWaveform(9, 47);
  drv.setWaveform(10, 0);
  drv.go();
  delay(5000);

  // MID THRESHOLD
  Serial.println("Medium buzz - bad dog");
  drv.setWaveform(0, 119);
  drv.setWaveform(1, 119);
  drv.setWaveform(2, 119);
  drv.setWaveform(3, 119);
  drv.setWaveform(4, 119);
  drv.setWaveform(5, 0);
  drv.go();
  delay(5000);

  // LOW THRESHOLD
  Serial.println("Min buzz - misbehaved dog");
  drv.setWaveform(0, 123);
  drv.setWaveform(1, 123);
  drv.setWaveform(2, 123);
  drv.setWaveform(3, 123);
  drv.setWaveform(4, 123);
  drv.setWaveform(5, 0);
  drv.go();
  delay(5000);
}