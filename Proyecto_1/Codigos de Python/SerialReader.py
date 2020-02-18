import serial
import time

ser = serial.Serial('COM21', 9600)

while (1):
    sensor = ser.readline().decode('utf-8')
    sensor_one = sensor_one.translate({ord(i): None for i in 'a'})
    print("sensor_one:",sensor_one)
    
    
