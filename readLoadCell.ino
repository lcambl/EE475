#include "BluetoothSerial.h"
#include "HX711.h"

BluetoothSerial SerialBT;
HX711 scale;
const byte loadcell_dout = 23;
const byte loadcell_sck = 22;

// Variables for the moving average filter
const int numReadings = 1;
long readings[numReadings]; // the readings from the load cell
int samples = 0; // the index of the current reading
long runningTotal = 0; 
long threshold = 40000;

// Calibration variables
long calibrationFactor = 1; // this calibration factor is obtained through calibration
long knownWeight = 0; // replace with the known weight in grams

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  SerialBT.begin();
  scale.begin(loadcell_dout, loadcell_sck);
  scale.set_scale();
  scale.tare();
}

void loop() {
  // put your main code here, to run repeatedly:
  while (! scale.is_ready()) {
    
  } 
  // read from sensor
  long reading = scale.read();
  // print raw reading to BT device's console
  if (reading > threshold) {
    SerialBT.println("Threshold exceeded, sensor value:");
    SerialBT.println(reading); 
  }
}
