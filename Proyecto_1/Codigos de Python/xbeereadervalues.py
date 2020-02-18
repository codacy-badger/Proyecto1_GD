#!/usr/bin/env python3
# -*- coding: utf-8 -*-
from digi.xbee.devices import XBeeDevice
from digi.xbee.io import IOLine, IOMode
from xbee.helpers.dispatch import Dispatch



import serial
import time
# TODO: Replace with the serial port where your local module is connected to.
PORT = "COM21"
# TODO: Replace with the baud rate of your local module.
BAUD_RATE = 9600
#REMOTE_NODE_ID = "XBG2"

def main():
    print(" +----------------------------------------------+")
    print(" |    E2 INNOVATION    GETs SYSTEM DETECTION    |")
    print(" +----------------------------------------------+\n")
    contadortx=0
    device = XBeeDevice(PORT, BAUD_RATE)
    try:
        device.open(force_settings=True)
        # Obtain the remote XBee device from the XBee network.
        xbee_network = device.get_network()
        xbee_network.start_discovery_process() 
        while xbee_network.is_discovery_running():
             time.sleep(0.5)
        devices = xbee_network.get_devices()
        print (xbee_network)
        remote_list = xbee_network.discover_devices(["XBG2", "XBG3"])
        print (remote_list)
        if remote_list is None:
            print("Could not find the remote device")
        while True:
            direccion = remote_list.get_64bit_addr()
        print(direccion)
                                 
    finally:
        if device is not None and device.is_open():
            device.close()
if __name__ == '__main__':
    main()