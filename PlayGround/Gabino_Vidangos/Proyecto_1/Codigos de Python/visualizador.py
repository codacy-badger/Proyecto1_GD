import pygame
import cv2
import serial
import time
ser = serial.Serial('COM20', 9600)

pygame.init()
screen = pygame.display.set_mode((600,400))

pygame.display.set_caption("GET Monitoring")
icon = pygame.image.load("e2i.png")
pygame.display.set_icon(icon)

##############################################
running = True
#Player
playerImg = pygame.image.load("smallget.png")
##############################################
def get():
    sensor = ser.readline().decode('utf-8')
    cordx = 10
    cordy = float(sensor)
    screen.blit(playerImg, (cordx,cordy))
    print(cordy)
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            runing = False
    screen.fill((0,0,0))
    get()
    pygame.display.update()
