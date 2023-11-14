import socket
import bluetooth
from time import sleep
import pandas as pd

database = {"Sensor Reading": [], "Time/Date": []}
devices = bluetooth.discover_devices(lookup_names=True)
mcuSocket = bluetooth.BluetoothSocket()
address = ''

def setUp():
    global address
    for device in devices:
        if device[1] == 'ESP32':
            address = device[0]
    
    if address != '':
        service_matches = bluetooth.find_service( address=address)
        port = service_matches[0]["port"]
        name = service_matches[0]["name"]
        host = service_matches[0]["host"]
        mcuSocket.connect((host,port))
        print("connected")
    
setUp()
while True:
    data = mcuSocket.recv(1024)
    if data:
        print(data)  