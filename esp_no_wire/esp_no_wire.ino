#include <Wire.h>
#include "Adafruit_DRV2605.h"
#include <Wireling.h>
#include "BluetoothSerial.h"
#include "HX711.h"

Adafruit_DRV2605 drv;
BluetoothSerial SerialBT;

// Initialize HX711 Scale
HX711 scale;
const byte loadcell_dout = 23;
const byte loadcell_sck = 18;
long avgReading = 0;
long avgDiff = 0;
bool ready = false;
int samples = 0;
const int samplesToInitialize = 100;
long lastReading = 0;

void setup() {
    // Bluetooth classic setup
    SerialBT.begin("Smart Collar");
    Serial.begin(115200);

    // Vibration Motor Setup
    Wireling.begin();
    drv.begin();
    drv.selectLibrary(1);
    drv.setMode(DRV2605_MODE_INTTRIG);
    drv.useLRA();

    // Setup HX711 Scale
    scale.begin(loadcell_dout, loadcell_sck);
    scale.set_scale();
    scale.tare();
}   

void loop() {
    if (!ready) {
        initializeSensor();
    } else {
        long filteredReading = scale.read() - avgReading - avgDiff;
        SerialBT.println(filteredReading);
        //Serial.println(filteredReading);
    }
    delay(10);
}

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

    // Check if initialization is complete
    if (samples >= samplesToInitialize) {
        avgReading /= samples;
        avgDiff /= (samples - 1);
        ready = true;
    }
}
