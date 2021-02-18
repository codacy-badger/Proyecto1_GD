# -*- coding: utf-8 -*-
"""
Created on Sat Apr 18 11:19:02 2020

@author: axel1
"""

import serial
#from digi.xbee.devices import XBeeDevice
from tkinter import *
#int var0, var1, var2, var3, var4    
#import tkinter as tk

mywindow = Tk()
mywindow.geometry("650x550")
mywindow.title("Configuración")
mywindow.resizable(False,False)
mywindow.config(background = "#213141")
main_title = Label(text="Parámetros | Axel", font =("Cambria",13), bg = "#56CD63", fg = "white", width = "550",height = "2")
main_title.pack()

# Define Label Fields 
ascale_label = Label(text = "Auto Full Scale", bg = "#FFEEDD")
ascale_label.place(x = 22, y = 70)
SR_label = Label(text = "SR Sensor Rate", bg = "#FFEEDD")
SR_label.place(x = 22, y = 130)
powerMode_label = Label(text = "Power Modes", bg = "#FFEEDD")
powerMode_label.place(x = 22, y = 190)
OSR_label = Label(text = "Oversampling", bg = "#FFEEDD")
OSR_label.place(x = 22, y = 250)
accfilter_label = Label(text = "Accel filter" , bg = "#FFEEDD")
accfilter_label.place(x = 22, y = 310)


#var = (var0, var1, var2, var3, var4)

#kibi--------------- interfaz grafica-----------

#for i in var :
#    var[i] = StringVar(mywindow)
    
var0 = StringVar(mywindow)
type(var0)

var1 = StringVar(mywindow)
type(var1)

var2 = StringVar(mywindow)
type(var2)

var3 = StringVar(mywindow)
type(var3)

var4 = StringVar(mywindow)
type(var4)



opciones0 = ['','Scale_2R','Scale_4R','Scale_8R','Scale_16R']
opcion0 = OptionMenu(mywindow,var0,*opciones0)
opcion0.place(x = 22, y = 95)

opciones1 = ['','SR_12_5Hz','SR_25Hz','SR_50Hz','SR_100Hz','SR_200Hz','SR_800Hz']
opcion1 = OptionMenu(mywindow,var1,*opciones1)
opcion1.place(x = 22, y = 155)

opciones2 = ['','sleep_Mode','lowpower_Mode','normal_Mode']
opcion2 = OptionMenu(mywindow,var2,*opciones2)
opcion2.place(x = 22, y = 215)

opciones3 = ['','osr0','osr1','osr2','osr3']
opcion3 = OptionMenu(mywindow,var3,*opciones3)
opcion3.place(x = 22, y = 275)

opciones4 = ['','acc_filt1','acc_filt2','acc_filt_lp']
opcion4 = OptionMenu(mywindow,var4,*opciones4)
opcion4.place(x = 22, y = 335)



  
def read():
    ser = serial.Serial('COM3',9600)
    while True:
        #lined = pd.read_csv('sample_data.csv',header = 0, encoding = 'unicode_escape')
         line = ser.readline()
         lined = line.decode(errors='ignore')
         print(lined)
         #print(lined.find("BMA"))
         
         if (lined.find("BMA") == 0):
         #     #print(lined.find("1320304050"))
             ser.close()
             break;
             
             
    #ser.close()
    """
    ser = serial.Serial('COM3',9600)
    while True:
         line= ser.readline()
         print(line)
         if string.find(line) == "":
             break;
             
    ser.close()
    """
    """
    while True:
    
        try:
            ser = serial.Serial('COM3', 9600)
            xbee_message = ser.readline()
            #x_m_d = xbee_message.decode('utf-8')
            print(xbee_message)
            #time.sleep(1)        
        except KeyboardInterrupt:
            print("bye")
            ser.close()
            break
    """
                        
def Leer_Parametro():
    
    ser = serial.Serial('COM3', 9600)    
    entrada5 = 8
    b = ser.write(str(entrada5).encode())
    
    line = ser.readline()
    lined = line.decode(errors = 'ignore')
    print(lined)
    x = lined.find("Parametros")
    if (x == 0):
        #print("wii")
        letra = lined[12:22]
        if(int(letra[0:2]) == 10):
            print("Ascale = AFS_2G")
        elif(int(letra[0:2]) == 11):
            print("Ascale = AFS_4G")
        elif(int(letra[0:2]) == 12):
            print("Ascale = AFS_8G")
        elif(int(letra[0:2]) == 13):
            print("Ascale = AFS_16G")
        
        #print(letra[2:4])
        if(int(letra[2:4]) == 20):            
            print("SR = SR_12_5HZ")
        elif(int(letra[2:4]) == 21):
            print("SR = SR_25HZ")
        elif(int(letra[2:4]) == 22):
            print("SR = SR_50HZ")
        elif(int(letra[2:4]) == 23):
            print("SR = SR_100HZ")
        elif(int(letra[2:4]) == 24):
            print("SR = SR_200HZ")
        elif(int(letra[2:4]) == 25):
            print("SR = SR_800HZ")
        
        #print(letra[4:6])
        if(int(letra[4:6]) == 30):
            print("Power_Mode = sleep_Mode")
        elif(int(letra[4:6]) == 31):
            print("Power_Mode = low power_Mode")
        elif(int(letra[4:6]) == 32):
            print("Power_Mode = normal_Mode")
            
        if(int(letra[6:8]) == 40):
            print("OSR = osr0")
        elif(int(letra[6:8]) == 41):
            print("OSR = osr1")
        elif(int(letra[6:8]) == 42):
            print("OSR = osr2")
        elif(int(letra[6:8]) == 43):
            print("OSR = osr3")
            
        if(int(letra[8:10]) == 50):
            print("acc_filter = acc_filt1")
        elif(int(letra[8:10]) == 51):
            print("acc_filter = acc_filt2")
        elif(int(letra[8:10]) == 52):
            print("acc_filter = acc_fil_lp")
        #print(letra)
        ser.close()
        #break  
    
    # if(lined.find("Para") == 0):
    #     print(lined.find("Para"))
    #     ser.close()
        
def ok():
    
    
    ser = serial.Serial('COM3', 9600)
    #ser.open()
    
    if (var0.get() == 'Scale_2R') :
        entrada0 = 10
    elif (var0.get() == 'Scale_4R') :
        entrada0 = 11
    elif (var0.get() == 'Scale_8R') :
        entrada0 = 12
    elif (var0.get() == 'Scale_16R') :
        entrada0 = 13
        
    ########## en vez de hacer esto mandar una notificaion si es cuadro esta vacio
    else :
        entrada0 = 11
        
    if (var1.get() == 'SR_12_5Hz') :
        entrada1 = 20
    elif (var1.get() == 'SR_25Hz') :
        entrada1 = 21
    elif (var1.get() == 'SR_50Hz') :
        entrada1 = 22
    elif (var1.get() == 'SR_100Hz') :
        entrada1 = 23
    elif (var1.get() == 'SR_200Hz') :
        entrada1 = 24
    elif (var1.get() == 'SR_800Hz') :
        entrada1 = 25
    else :
         entrada1 = 24
        
    if (var2.get() == 'sleep_Mode') :
        entrada2 = 30
    elif (var2.get() == 'lowpower_Mode') :
        entrada2 = 31
    elif (var2.get() == 'normal_Mode') :
        entrada2 = 32
    else :
         entrada2 = 32
        
    if (var3.get() == 'osr0') :
        entrada3 = 40
    elif (var3.get() == 'osr1') :
        entrada3 = 41
    elif (var3.get() == 'osr2') :
        entrada3 = 42   
    elif (var3.get() == 'osr3') :
        entrada3 = 43 
    else :
         entrada3 = 43
        
    if (var4.get() == 'acc_filt1') :
        entrada4 = 50
    elif (var4.get() == 'acc_filt2') :
        entrada4 = 51
    elif (var4.get() == 'acc_filt_lp') :
        entrada4 = 52       
    else :
        entrada4 = 50
  
    
    entrada = (entrada0, entrada1 , entrada2 , entrada3 , entrada4)
    
    #mywindow.quit()
    
    for x in entrada :
        a = ser.write(str(x).encode())
        #a = ser.send_data_broadcast("Hello")
    
    ser.close()
    
    
    print("value is", var0.get())
    #print()
    
    
    
    
    
button = Button(mywindow, text = "OK", command = ok)
button.place(x = 22, y = 375)

button2 = Button(mywindow, text = "READ", command = read)
button2.place(x = 80 , y = 375)

button3 = Button(mywindow, text = "Leer Parametros", command = Leer_Parametro)
button3.place(x = 138, y = 375)

print(opcion0)



mywindow.mainloop()