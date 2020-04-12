# Plot 6 signals

import serial
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

ser = serial.Serial('COM12', 9600)

leng = 221
fig = plt.figure(figsize=(12, 6))
ax = plt.axes(xlim=(0,leng-1), ylim=(-300,300))

plt.title('Real-time sensor data vs Kalman Filter Applied')
plt.xlabel('Data points')
plt.ylabel('3 axis - Angular')
ax.grid(True)

graphX, = ax.plot([], [], 'b', label = 'X')
graphY, = ax.plot([], [], 'r', label = 'Y')
graphZ, = ax.plot([], [], 'g', label = 'Z')

graphC, = ax.plot([], [], 'b', label = 'X-KF')
graphV, = ax.plot([], [], 'r', label = 'Y-KF')
graphB, = ax.plot([], [], 'g', label = 'Z-KF')

ax.legend(loc='upper right')
ax.legend(loc='upper right')
ax.legend(loc='upper right')

t = list(range(0, leng))
accX = []
accY = []
accZ = []
angX = []
angY = []
angZ = []

for i in range(0, leng):
    accX.append(0)
    accY.append(0)
    accZ.append(0)
    angX.append(0)
    angY.append(0)
    angZ.append(0)

def init():
    graphX.set_data([], [])
    graphY.set_data([], [])
    graphZ.set_data([], [])
    graphC.set_data([], [])
    graphV.set_data([], [])
    graphB.set_data([], [])
    return graphX, graphY, graphZ, graphC, graphV, graphB

def animate(i):
    global t, accX, accY, accZ, angX, angY, angZ

    while (ser.inWaiting() == 0):
        pass

    arduinoString = ser.readline().decode("utf-8")
    dataArray = arduinoString.split(',')
    ###############################################
    accX.append(float(dataArray[0]))    
    accY.append(float(dataArray[1]))    
    accZ.append(float(dataArray[2]))
    angX.append(float(dataArray[3]))    
    angY.append(float(dataArray[4]))    
    angZ.append(float(dataArray[5]))
    ###############################################
    #accX.append(float(dataArray[0])/(32767/2))    
    #accY.append(float(dataArray[1])/(32767/2))    
    #accZ.append(float(dataArray[2])/(32767/2))
    accX.pop(0)
    accY.pop(0)
    accZ.pop(0)
    angX.pop(0)
    angY.pop(0)
    angZ.pop(0)

    graphX.set_data(t, accX)
    graphY.set_data(t, accY)
    graphZ.set_data(t, accZ)
    graphC.set_data(t, angX)
    graphV.set_data(t, angY)
    graphB.set_data(t, angZ)

    return graphX, graphY, graphZ, graphC, graphV, graphB

delay = 20
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               interval=delay, blit=True)

plt.show()

