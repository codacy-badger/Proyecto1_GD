import serial
import time
import numpy as np
import string
import re

ser = serial.Serial('COM12',9600)

ax = 0
ay = 0
az = 0
t = 0
while True:
    string = ser.readline().decode('utf-8')   
    line = string.split(',')  
    ax = float(line[0])    
    ay = float(line[1])    
    az = float(line[2])
    t = float(line[3])
    print(ax,ay,az,t)
    
    
