#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID "82ba65ea-f3ac-4966-ac94-9acc762282a1"
#define CHARACTERISTIC_UUID "6e3ac890-7e4d-4e0c-89be-f2f9af3112d9"

int count = 0;
BLECharacteristic *pCharacteristic;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Connecting to ESP...");

  BLEDevice::init("MyESP32"); // create BLE device
  BLEServer *pServer = BLEDevice::createServer(); // set BLE device as server
  BLEService *pService = pServer->createService(SERVICE_UUID); // create service for BLE server with pre-defined UUID
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID,
  BLECharacteristic::PROPERTY_READ | 
  BLECharacteristic::PROPERTY_WRITE
  ); // set characteristic for service - use predefined characteristic UUID, want characteristic to be read and write
  pCharacteristic->setValue("reading value goes here"); // info to be shared
  pService->start(); // start service

  // start advertising so other devices can scan and find this BLE device (app is client, searching for advertisements)
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();
  Serial.println("Can now read from phone");
}

void loop() {
  // put your main code here, to run repeatedly:
  pCharacteristic->setValue(count);
  count += 1;
  delay(5000);
}
