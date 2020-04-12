# Plot 6 signals

import serial
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import animation

ser = serial.Serial('COM12', 9600)

leng = 201
fig = plt.figure(figsize=(12, 6))
ax = plt.axes(xlim=(0,leng-1), ylim=(-50, 50))

plt.title('Real-time sensor data vs Kalman Filter Applied')
plt.xlabel('Data points')
plt.ylabel('3 axis - Angular')
ax.grid(True)

graphX, = ax.plot([], [], 'b', label = 'X')
graphY, = ax.plot([], [], 'r', label = 'X-KF')

ax.legend(loc='upper right')
ax.legend(loc='upper right')


t = list(range(0, leng))
accX = []
accY = []

for i in range(0, leng):
    accX.append(0)
    accY.append(0)

def init():
    graphX.set_data([], [])
    graphY.set_data([], [])
    return graphX, graphY

def animate(i):
    global t, accX, accY
    while (ser.inWaiting() == 0):
        pass
    arduinoString = ser.readline().decode("utf-8")
    dataArray = arduinoString.split(',')
    ###############################################
    accX.append(float(dataArray[0]))    
    accY.append(float(dataArray[1]))    
    ###############################################
    accX.pop(0)
    accY.pop(0)
    graphX.set_data(t, accX)
    graphY.set_data(t, accY)
   
    return graphX, graphY

delay = 20
anim = animation.FuncAnimation(fig, animate, init_func=init,
                               interval=delay, blit=True)

plt.show()
