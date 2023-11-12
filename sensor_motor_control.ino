#include "BluetoothSerial.h"
#include "HX711.h"

BluetoothSerial SerialBT;
HX711 scale;
const byte loadcell_dout = 23;
const byte loadcell_sck = 22;
const byte motorPin = 16;
int ledPin = 2;

// Variables for the moving average filter
long low_threshold = 40000;
long med_threshold = 100000;
long high_threshold = 160000; 

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
  pinMode(motorPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (! scale.is_ready()) {
    
  } 
  // read from sensor
  long reading = scale.read();
  // print raw reading to BT device's console
  if ((reading > low_threshold) && (reading < med_threshold)) {
    analogWrite(motorPin, 155);
    digitalWrite(ledPin, HIGH);
    SerialBT.println("Low Threshold exceeded, sensor value:");
    SerialBT.println(reading); 
  } else if ((reading > med_threshold) && (reading < high_threshold)) {
    analogWrite(motorPin, 200);
    digitalWrite(ledPin, HIGH);
    SerialBT.println("Medium Threshold exceeded, sensor value:");
    SerialBT.println(reading); 
  } else if (reading > high_threshold) {
    analogWrite(motorPin, 255);
    digitalWrite(ledPin, HIGH);
    SerialBT.println("High Threshold exceeded, sensor value:");
    SerialBT.println(reading); 
  } else {
    analogWrite(motorPin, 0);
    digitalWrite(ledPin, LOW);
  }
}
