#include "HX711.h"

HX711 scale;
const byte loadcell_dout = 23;
const byte loadcell_sck = 22;

// Variables for the moving average filter
const int numReadings = 1;
long readings[numReadings]; // the readings from the load cell
int samples toInitialize = 100; // the number of samples to initialize the load cell
long runningTotal = 0; 
long avgReading = 0; // the average reading
long lastReading = 0; // the latest reading
long avgDiff = 0; // the difference between the current reading and the average reading
bool initialized = false; // whether or not the load cell has been initialized

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
  int motorVal;

  // print raw reading to BT device's console
  if (!initialized) {
    avgReading += reading;
    samples++;
    // if we have a lastReading from the previous loop, calculate the difference between the current reading and the average reading
    if (lastReading != 0) {
      avgDiff = (reading - avgReading);
    }
    // if we have enough samples, calculate the average reading and the average difference
    if (samples == toInitialize) {
      avgReading /= samples;
      avgDiff /= (samples - 1);
      initialized = true;
    }

    // save the reading for the next loop
    lastReading = reading;
  } else {
    // Print the current reading using the filter of the average reading and the average difference
    SerialBT.println(reading - avgReading - avgDiff);
  }
}
