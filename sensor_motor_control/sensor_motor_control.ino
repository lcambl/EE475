#include "BluetoothSerial.h"
#include "HX711.h"

BluetoothSerial SerialBT;
HX711 scale;
const byte loadcell_dout = 23;
const byte loadcell_sck = 22;
const byte motorPin = 16;
int ledPin = 2;

// Variables for the moving average filter
int threshold_1 = 40000;
long threshold_2 = 55000;
long threshold_3 = 70000;
long threshold_4 = 85000;
long threshold_5 = 100000;
long threshold_6 = 115000;
long threshold_7 = 130000;
long threshold_8 = 145000;
long threshold_9 = 160000;
long threshold_10 = 175000; 

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
  int motorVal;

  // print raw reading to BT device's console
  if ((reading > threshold_1) && (reading <= threshold_2)) {
    analogWrite(motorPin, 25);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else if ((reading > threshold_2) && (reading <= threshold_3)) {
    analogWrite(motorPin, 50);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else if ((reading > threshold_3) && (reading <= threshold_4)) {
    analogWrite(motorPin, 75);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else if ((reading > threshold_4) && (reading <= threshold_5)) {
    analogWrite(motorPin, 100);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else if ((reading > threshold_5) && (reading <= threshold_6)) {
    analogWrite(motorPin, 125);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else if ((reading > threshold_6) && (reading <= threshold_7)) {
    analogWrite(motorPin, 150);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else if ((reading > threshold_7) && (reading <= threshold_8)) {
    analogWrite(motorPin, 175);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else if ((reading > threshold_8) && (reading <= threshold_9)) {
    analogWrite(motorPin, 200);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else if ((reading > threshold_9) && (reading <= threshold_10)) {
    analogWrite(motorPin, 225);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else if (reading > threshold_10){
    analogWrite(motorPin, 250);
    digitalWrite(ledPin, HIGH);
    SerialBT.println(reading); 
  } else {
    analogWrite(motorPin, 0);
    digitalWrite(ledPin, LOW);
  }
}