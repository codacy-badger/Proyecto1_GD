import serial
import numpy as np
import time

ser = serial.Serial('COM29', 9600, timeout=0)
time.sleep(2)
while True:
    sensor = ser.readline().decode('utf-8')
    time.sleep(0.1)
    #print(sensor)
    if sensor == 'a':
        ser.write(b"i")
        # print(sensor)
        if not sensor == 'a':
            ser.write(b"s")
            #ser.write(b"s")
            #print(sensor)
            print(sensor)
