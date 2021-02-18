#!/usr/bin/env python3
import serial
import time

ser = serial.Serial('COM9', 9600, timeout=0)
print(" +----------------------------------------------+")
print(" |       E2 INNOVATION GETs SYSTEM DETECTION    |")
print(" +----------------------------------------------+\n")
time.sleep(1)

while True: 
    serial = ser.readline()
    data = serial.decode('utf-8')

    if 'a' in data:
        ser.write(b"a")
        g1 = data.translate({ord(i): None for i in 'a'}) # 1°
        print('s1:',g1)

    if 'b' in data:
        ser.write(b"b")
        g2 = data.translate({ord(i): None for i in 'b'}) # 2°
        print('s2:',g2)

    if 'c' in data:
        ser.write(b"c")
        g3 = data.translate({ord(i): None for i in 'c'}) # 3°
        print('s3:',g3)

    if 'd' in data:
        ser.write(b"d")
        g4 = data.translate({ord(i): None for i in 'd'}) # 4°
        print('s4:',g4)

    if 'e' in data:
        ser.write(b"e")
        g5 =data.translate({ord(i): None for i in 'e'}) # 5°
        print('s5:',g5)

    if 'f' in data:
        ser.write(b"f")
        g6 = data.translate({ord(i): None for i in 'f'}) # 6°
        print('s6:',g6)

    if 'g' in data:
        ser.write(b"g")
        g7 = data.translate({ord(i): None for i in 'g'}) # 7°
        print('s7:',g7)

    if 'h' in data:
        ser.write(b"h")
        g8 = data.translate({ord(i): None for i in 'h'}) # 8°
        print('s8:',g8)

    if 'i' in data:
        ser.write(b"i")
        g9 = data.translate({ord(i): None for i in 'i'}) # 9°
        print('s9:',g9)
