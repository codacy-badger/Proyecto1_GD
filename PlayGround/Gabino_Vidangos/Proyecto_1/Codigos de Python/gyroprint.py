# Plot 6 signals

import serial
import numpy as np

ser = serial.Serial('COM12', 9600)
angX = []
angY = []
angZ = []
while (ser.inWaiting() == 0):
    pass
    arduinoString = ser.readline().decode("utf-8")
    dataArray = arduinoString.split(',')
    ###############################################
    angX = dataArray[0]
    angY = dataArray[1]  
    angZ = dataArray[2]
    ###############################################
    angZ = int(float(angZ))
    angY = int(float(angY)) 
    angX = int(float(angX))
    print(angX,angY,angZ)
    
