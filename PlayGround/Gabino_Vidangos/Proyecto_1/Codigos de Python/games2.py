import serial
import time

ser = serial.Serial('COM12', 9600)

while (1):
    sensores = ser.readline().decode('utf-8')
    
    if 'a' in sensores:
        s1 = sensores.translate({ord(i): None for i in 'a'}) # 1°
        print('s1:',s1)

    if 'b' in sensores:
        s2 = sensores.translate({ord(i): None for i in 'b'}) # 2°
        print('s2:',s2)

    
