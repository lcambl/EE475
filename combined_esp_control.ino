/*************************************************************************
 * DRV2605 LRA ERM Haptic Driver Wireling
 * This program is an expanded example that is part of the Adafruit_DRV2605 
 * library. The DRV_2605 will send 116 different waveform effects to a 
 * vibrating or buzzing motor. If you are interested in the individual 
 * effects, the list of effects can be found on page 57 of the datasheet: 
 * http://www.ti.com/lit/ds/symlink/drv2605.pdf
 * 
 * Modified by: Laveréna Wienclaw for TinyCircuits 
 *************************************************************************/
 
#include <Wire.h>             // For using I2C communication
#include "Adafruit_DRV2605.h" // For interfacing with the DRV2605 chip
#include <Wireling.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "HX711.h"

// Vibration motor setup
Adafruit_DRV2605 drv;   // The variable used to interface with the DRV2605 chip
uint8_t effect = 1;     // The global variable used to keep track of effects

// HX711 scale setup
HX711 scale;
const byte loadcell_dout = 23;
const byte loadcell_sck = 18;
long avgReading = 0;
long avgDiff = 0;
bool ready = false;
int samples = 0;
const int samplesToInitialize = 100;
long lastReading = 0;

// BLE setup
BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};


void setup() {
  Serial.begin(115200);

  // Vibration Motor Setup
  Wireling.begin();
  drv.begin();
  drv.selectLibrary(1); // LRA library
  drv.setMode(DRV2605_MODE_INTTRIG); // internal I2C trigger, send go command 
  drv.useLRA();

  // BLE initialization
  BLEDevice::init("Smart Collar");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ
                    );
  
  pCharacteristic->addDescriptor(new BLE2902());
  pService->start();
  BLEDevice::startAdvertising();

  // HX711 scale initialization
  scale.begin(loadcell_dout, loadcell_sck);
  scale.set_scale();
  scale.tare();
}

// long filteredReading = 0;

void loop() {
  // BLE connection handling
  if (deviceConnected && !oldDeviceConnected) {
    oldDeviceConnected = deviceConnected;
  }

  if (!deviceConnected && oldDeviceConnected) {
    pServer->startAdvertising();
    oldDeviceConnected = deviceConnected;
  }

  if (!ready) {
    initializeSensor();
  } else {
    long filteredReading = scale.read() - avgReading - avgDiff;
    Serial.println(filteredReading);
    drv.setWaveform(0, effect);  // Set effect
    drv.setWaveform(1, 0);       // End waveform

    // Play the effect
    if (filteredReading >= 200000) {
      drv.go();
      
    }
    if (deviceConnected) {
      pCharacteristic->setValue((uint8_t*)&filteredReading, sizeof(filteredReading));
      pCharacteristic->notify();
    }
  }
  delay(10);
  Serial.print("Effect #"); 
  Serial.println(effect);
  // Set the effect to play


  // Pause for differentiation between effects
  //delay(1000);
  effect++;
  if (effect > 117) effect = 1;
}

// Function to initialize the sensor
void initializeSensor() {
    long reading = scale.read();
    avgReading += reading;
    Serial.println(samples);
    samples++;
    if (lastReading != 0) {
        avgDiff += (reading - lastReading);
    }
    lastReading = reading;

    // Calculate and send initialization progress
    float progress = (float)samples / (float)samplesToInitialize * 100.0;
    if (deviceConnected) {
        char initMsg[50];
        sprintf(initMsg, "Initializing: %.2f%%", progress);
        pCharacteristic->setValue((uint8_t*)initMsg, strlen(initMsg));
        pCharacteristic->notify();
    }

    // Check if initialization is complete
    if (samples >= samplesToInitialize) {
        avgReading /= samples;
        avgDiff /= (samples - 1);
        ready = true;
    }
}
