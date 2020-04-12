# Plot 3 signals

import serial
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

ser = serial.Serial('COM12', 9600)

leng = 201
fig = plt.figure(figsize=(12, 6))
ax = plt.axes(xlim=(0,leng-1), ylim=(-180, 180))

plt.title('Real-time sensor data')
plt.xlabel('Data points')
plt.ylabel('Acceleration [G]')
ax.grid(True)

graphX, = ax.plot([], [], 'b', label = 'X')
graphY, = ax.plot([], [], 'r', label = 'Y')
graphZ, = ax.plot([], [], 'g', label = 'Z')
ax.legend(loc='upper right')
ax.legend(loc='upper right')
ax.legend(loc='upper right')

t = list(range(0, leng))
accX = []
accY = []
accZ = []

for i in range(0, leng):
    accX.append(0)
    accY.append(0)
    accZ.append(0)

def init():
    graphX.set_data([], [])
    graphY.set_data([], [])
    graphZ.set_data([], [])
    return graphX, graphY, graphZ

def animate(i):
    global t, accX, accY, accZ

    while (ser.inWaiting() == 0):
        pass

    arduinoString = ser.readline().decode("utf-8")
    dataArray = arduinoString.split(',')
    ###############################################
    accX.append(float(dataArray[0]))    
    accY.append(float(dataArray[1]))    
    accZ.append(float(dataArray[2]))
    ###############################################
    #accX.append(float(dataArray[0])/(32767/2))    
    #accY.append(float(dataArray[1])/(32767/2))    
    #accZ.append(float(dataArray[2])/(32767/2))
    accX.pop(0)
    accY.pop(0)
    accZ.pop(0)

    graphX.set_data(t, accX)
    graphY.set_data(t, accY)
    graphZ.set_data(t, accZ)

    return graphX, graphY, graphZ

delay = 20
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               interval=delay, blit=True)

plt.show()

