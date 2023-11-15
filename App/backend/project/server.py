import socket
import bluetooth
from time import sleep
import pandas as pd
import bleak
import asyncio
import struct

address_to_look_for = '24:DC:C3:C0:FE:4A'
service_id_to_look_for = '10336bc0-c8f9-4de7-b637-a68b7ef33fc9'

class Scanner:
    def __init__(self):
        self._scanner = bleak.BleakScanner()
        self._scanner.register_detection_callback(self.detection_callback)
        self.scanning = asyncio.Event()
    def detection_callback(self, device, advertisement_data):
        if device.address == address_to_look_for:
            byte_data = advertisement_data.service_data.get(service_id_to_look_for)
            num_to_test, = struct.unpack_from('<I', byte_data, 0)
            if num_to_test == 62976:
                print('device found')
                self.scanning.clear()

    async def run(self):
        await self._scanner.start()
        self.scanning.set()
        end_time = loop.time() + 20
        while self.scanning.is_set():
            if loop.time() > end_time:
                self.scanning.clear()
                print("timeout")
            await asyncio.sleep(0.1)
        await self._scanner.stop()

if __name__ == '__main__':
    my_scanner = Scanner()
    loop = asyncio.get_event_loop()
    loop.run_until_complete(my_scanner.run())



# def detection_callback(device, advertisement_data):
#     byte_data = advertisement_data
# scan = bleak.BleakScanner()


# scan.start()
# count = 0

# while (count < 10):
#     data = scan.advertisement_data()
#     print(data)
#     count += 1
# scan.stop()


# database = {"Sensor Reading": [], "Time/Date": []}
# devices = bluetooth.discover_devices(lookup_names=True)
# mcuSocket = bluetooth.BluetoothSocket()
# address = ''
# def setUp():
#     global address
#     for device in devices:
#         if device[1] == 'ESP32':
#             address = device[0]
    
#     if address != '':
#         service_matches = bluetooth.find_service( address=address)
#         port = service_matches[0]["port"]
#         name = service_matches[0]["name"]
#         host = service_matches[0]["host"]
#         mcuSocket.connect((host,port))
#         print("connected")
    
# setUp()
# while True:
#     data = mcuSocket.recv(1024)
#     if data:
#         print(data)        
    