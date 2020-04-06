/*
ADXL362_MotionActivatedSleep para el ADXL362 - Micropower 3-axis accelerometer
Conecciones:
 CONECCIONES:

 DEVICE   | MSP430
 -------------------
   MOSI   |  P1.7     
   MISO   |  P1.6
   SCLK   |  P1.5
   CS     |  P2.0
   INT1   |  P1.3
   GND    |  GND
   VIO    |  3.3v
   VS     |  3.3v
 
*/ 

//Access to SPI libraries and ADLX362 library
#include <SPI.h>
#include "ADXL362.h"

//Creando una clase ADLX362 con nombre x1
ADXL362 xl;

//Variables del programa
int16_t temp;
int16_t XValue16, YValue16, ZValue16, Temperature16;
int8_t XValue8, YValue8, ZValue8;


void setup(){
  
  Serial.begin(9600);
  xl.begin(P2_0);                 // Set Cs pin and initialize SPI conection 
  delay(1000);
  xl.SoftReset();                   
  xl.beginMeasure();              // Switch ADXL362 to measure mode  
  Serial.println("Start Demo: Simple Read");
}

void loop(){
  //16-bitd reading
  xl.readXYZTData16(XValue16, YValue16, ZValue16,Temperature16);  
  //8-bits reading
  xl.readXYZData8(XValue8, YValue8, ZValue8);  
 
  //Show values
  Serial.println("Data with 16-bits values:");
  Serial.print(XValue16);
  Serial.print(",");
  Serial.print(YValue16);  
  Serial.print(",");
  Serial.print(ZValue16);  
  Serial.print(",");
  Serial.println(Temperature16);

  Serial.println("Data with 8-bits values:");   
  Serial.print(XValue8);  
  Serial.print(",");
  Serial.print(YValue8);  
  Serial.print(",");
  Serial.print(ZValue8);  
  Serial.print('\n');   

  delay(500);                // Arbitrary delay to make serial monitor easier to observe
}
