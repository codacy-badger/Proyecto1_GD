# Plot 4 signals

import serial
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

ser = serial.Serial('COM12', 9600)
angX = []
angY = []
angZ = []
tempP = []

while (ser.inWaiting() == 0):
    pass
    arduinoString = ser.readline()#.decode("utf-8")
    dataArray = arduinoString.split(',')
    ###############################################
    angX.append(float(dataArray[0]))    
    angY.append(float(dataArray[1]))    
    angZ.append(float(dataArray[2]))
    tempT.append(float(dataArray[3]))
    ###############################################
    print(angX,angY,angZ)

delay = 20

