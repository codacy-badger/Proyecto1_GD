#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Apr 28 09:43:01 2018

@author: eddy
"""

# Copyright 2017, Digi International Inc.
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

from digi.xbee.devices import XBeeDevice
from digi.xbee.io import IOLine, IOMode
import serial
import pymysql
import time

# TODO: Replace with the serial port where your local module is connected to.
PORT = "/dev/ttyUSB1"
# TODO: Replace with the baud rate of your local module.
BAUD_RATE = 9600

REMOTE_NODE_ID = "RECEIVER"

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
        remote_device = xbee_network.discover_device(REMOTE_NODE_ID)
        if remote_device is None:
            print("Could not find the remote device")
            exit(1)

        # Set the local device as destination address of the remote.
        remote_device.set_dest_address(device.get_64bit_addr())

        #remote_device.set_io_configuration(DIGITAL_LINE, IOMode.DIGITAL_IN)
        remote_device.set_io_configuration(ANALOG_LINE, IOMode.ADC)

        # Enable periodic sampling every IO_SAMPLING_RATE seconds in the remote device.
        remote_device.set_io_sampling_rate(IO_SAMPLING_RATE)

        # Enable DIO change detection in the remote device.
        remote_device.set_dio_change_detection({DIGITAL_LINE})

        # Register a listener to handle the samples received by the local device.
        def io_samples_callback(sample, remote, tiempo):
            #print("New sample received from %s - %s" % (remote.get_64bit_addr(), sample))
            direccion = remote.get_64bit_addr()
            temp = str(sample)
            if len(temp)==22:
                temperatura = int(temp[19])
            elif len(temp)==23:
                temperatura = int(temp[19:21])
            elif len(temp)==24:
                temperatura = int(temp[19:22])
            elif len(temp)==25:
                temperatura = int(temp[19:23])

            #data = temp.split(",")
            print("++++ New data +++")
            fecha1=time.strftime("%x")
            hora1=time.strftime("%X")

            print ("Date: ", fecha1)
            print ("Time: ", hora1)
            print("ID:", direccion)

            #print(len(temp))
            voltage = round(3.6*temperatura/1023, 2)
            temperatura=round(-50 + temperatura*120/1023,2)
            if temperatura > 0:
                GET= True
            else:
                GET = False
            print("Voltage:",voltage)
            print (" ")
            #sendgpsdata(temperatura)
        device.add_io_sample_received_callback(io_samples_callback)

        input()

    finally:
        if device is not None and device.is_open():
            device.close()

if __name__ == '__main__':
    main()
