#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Apr 26 11:52:58 2018

@author: eddy
"""

import serial
from xbee import XBee

serial_port = serial.Serial('/dev/ttyUSB1', 9600)
xbee = XBee(serial_port)
device = XBeeDevice(PORT, BAUD_RATE)
while True:
    print ('llll')
    """
    line = serial_port.readline()
    print (line)
    """
    try:
        mensaje= xbee.wait_read_frame()
        print(mensaje)
        #break
    except KeyboardInterrupt:
        break
    
serial_port.close()
    