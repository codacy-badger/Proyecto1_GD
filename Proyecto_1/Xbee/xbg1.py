#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from digi.xbee.devices import XBeeDevice
from digi.xbee.io import IOLine, IOMode
import serial
import time

# TODO: Replace with the serial port where your local module is connected to.
PORT = "COM21"
# TODO: Replace with the baud rate of your local module.
BAUD_RATE = 9600

#REMOTE_NODE_ID = "RECEIVER"
#REMOTE_NODE_ID = "Receiver XB3_2"
REMOTE_NODE_ID = "XBG3"

DIGITAL_LINE = IOLine.DIO3_AD3
ANALOG_LINE = IOLine.DIO2_AD2

IO_SAMPLING_RATE = 5  # 5 seconds.


def main():
    print(" +----------------------------------------------+")
    print(" |    E2 INNOVATION    GETs SYSTEM DETECTION    |")
    print(" +----------------------------------------------+\n")
    contadortx=0
    device = XBeeDevice(PORT, BAUD_RATE)

    try:
        device.open()
        # Obtain the remote XBee device from the XBee network.
        xbee_network = device.get_network()
        print (xbee_network)
        remote_device = xbee_network.discover_device(REMOTE_NODE_ID)
        print (remote_device)
        if remote_device is None:
            print("Could not find the remote device")
            #exit(1)
        while True:
            tiempo1=time.time()
            direccion = remote_device.get_64bit_addr()
            ADC=remote_device.get_adc_value(IOLine.DIO2_AD2)
            Voltage=remote_device.get_parameter('TP')
            tiempo2=time.time()
            print("++++ New data +++")
            print(tiempo2-tiempo1)
            fecha1=time.strftime("%x")
            hora1=time.strftime("%X")
            print ("Date: ", fecha1)
            print ("Time: ", hora1)
            print("ID:", direccion)
            print ("Valor: ", ADC)
            print ("Voltage" , Voltage)
            print ("")
            #time.sleep(32)
        # Register a listener to handle the samples received by the local device.
            
        input()

    finally:
        if device is not None and device.is_open():
            device.close()
if __name__ == '__main__':
    
    main()
