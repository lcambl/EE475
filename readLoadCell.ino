#include "BluetoothSerial.h"
#include "HX711.h"

BluetoothSerial SerialBT;
HX711 scale;
const byte loadcell_dout = 23;
const byte loadcell_sck = 22;
// Variables for the moving average filter
const int numReadings = 5;
long readings[numReadings]; // the readings from the load cell
int readIndex = 0; // the index of the current reading
long total = 0; // the running total
long average = 0; // the average

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
  // Initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  if (scale.is_ready()) {
    SerialBT.println("scale was ready");
    long reading = scale.read();
    SerialBT.println(reading);
    // Subtract the last reading:
    total = total - readings[readIndex];
    // Read from the sensor:
    readings[readIndex] = reading;
    // Add the reading to the total:
    total = total + readings[readIndex];
    // Advance to the next position in the array:
    readIndex = readIndex + 1;

    // If we're at the end of the array...
    if (readIndex >= numReadings) {
      // ...wrap around to the beginning:
      readIndex = 0;
    }

    // Calculate the average:
    average = total / numReadings;
    // Scale the average reading to the known weight to get the calibration factor
    if (scale.get_units(10) != 0) {
      calibrationFactor = knownWeight / scale.get_units(10);
      scale.set_scale(calibrationFactor); // Adjust to this calibration factor
    }  

    // // Print out the raw, average, and the weight readings:
    // Serial.print("Raw reading: ");
    // Serial.print(reading);
    // Serial.print(" Average reading: ");
    // Serial.print(average);
    // Serial.print(" Weight: ");
    // Serial.print(scale.get_units(), 2); // two decimal places
    // Serial.println(" g");

  } else {
    SerialBT.println("HX711 not found.");
  }

  delay(1000);
  // if (Serial.available()) {
  //   SerialBT.write(Serial.read());

  // }
  // if (SerialBT.available()) {
  //   Serial.write(SerialBT.read());
  // }
  // delay(20);
}
