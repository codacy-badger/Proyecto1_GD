import pygame
from pygame.locals import*

from OpenGL.GL import *
from OpenGL.GLU import *

import serial
import numpy as np

ser = serial.Serial('COM12', 9600)

##_____________________________________________##

verticies = (           #X,Y,Z
    (1,-1,-1),
    (1,1,-1),
    (-1,1,-1),
    (-1,-1,-1),
    (1,-1,1),
    (1,1,1),
    (-1,-1,1),
    (-1,1,1),
    )
edges = (
    (0,1),
    (0,3),
    (0,4),
    (2,1),
    (2,3),
    (2,7),
    (6,3),
    (6,4),
    (6,7),
    (5,1),
    (5,4),
    (5,7)
    )
def cube():
    glBegin(GL_LINES)
    for edge in edges:
        for vertex in edge:
            glVertex3fv(verticies[vertex])
    glEnd()
    
def main():
    pygame.init()
    display=(800,600)
    pygame.display.set_mode(display,DOUBLEBUF|OPENGL)

    gluPerspective(45, (display[0]/display[1]),0.1,50.0)
    glTranslatef(0.0,0.0,-8)
    #glRotatef(37,37,37,25)

    while True:
        arduinoString = ser.readline().decode("utf-8")
        dataArray = arduinoString.split(',')
        angX = int(float(dataArray[0]))
        angY = int(float(dataArray[1]))
        angZ = int(float(dataArray[2]))
                      
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
        glRotatef(angX,1.0, 0.0, 0.0)
        glRotatef(angY,0.0, 1.0, 0.0)
        glRotatef(angZ,0.0, 0.0, 1.0)       
#        glRotatef(1,1,0,0)
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT)
        cube()
        pygame.display.flip()
        pygame.time.wait(10)
main()


    
    
