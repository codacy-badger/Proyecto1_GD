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
//volatile bool State = false;

//Access to SPI libraries and ADLX362 library
#include <SPI.h>
#include "ADXL362.h"

//Creando una clase ADLX362 con nombre x1
ADXL362 xl;

//Variables del programa
int16_t temp;
int16_t XValue16, YValue16, ZValue16, Temperature16;

//Definiendo pin de interrupcion (Pin 2_5)
#define interruptPin P2_5 

const int WAKEUP_PIN = 2.1;//2.1
bool valInterrupt = 0;

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);
 pinMode( WAKEUP_PIN , OUTPUT); ///XBEE WAKEUP AND SLEEP
 pinMode(interruptPin,INPUT);

  xl.begin(P2_0);                 // Set Cs pin and initialize SPI conection 
  delay(1000);
  xl.SoftReset(); 
  delay(1000);            
  xl.setupDCActivityInterrupt(300, 10);    // 300 code activity threshold.  With default ODR = 100Hz, time threshold of 10 results in 0.1 second time threshold
  xl.setupDCInactivityInterrupt(80, 200);   // 80 code inactivity threshold.  With default ODR = 100Hz, time threshold of 30 results in 2 second time threshold
  xl.SetAwake_IntI(true);     //Active Awake Interruption
  xl.SetLinkLopp(Loop_mode);  //Active Loop Mode
  xl.SetInactReference(true); //Active Inactive Reference Mode
  xl.SetActReference(true);   //Active Active Reference Mode
  xl.SetAutosleep(true);      // turn on Autosleep bit                  
  
  xl.beginMeasure();              // Switch ADXL362 to measure mode  
  delay(100);

  attachInterrupt(interruptPin,interrupt,RISING);
}

void Read(){
  
  xl.readXYZTData16(XValue16, YValue16, ZValue16,Temperature16);
  //Show values
  digitalWrite(WAKEUP_PIN ,LOW);
  Serial.println("Data with 16-bits values:");
  Serial.print(XValue16);
  Serial.print(",");
  Serial.print(YValue16);  
  Serial.print(",");
  Serial.print(ZValue16);  
  Serial.print(",");
  Serial.println(Temperature16); 
  
  sleep(500); // lpm3
  }

void sleepNow(){
  Serial.print("\nADXL went to sleep - Put MSP to sleep now \n");
  suspend();   //lpm4
  }

void interrupt(){
  wakeup();
  }

  
void loop() { 
  valInterrupt = digitalRead(interruptPin);

  if(valInterrupt == 1){
    
    Read();
    
    } else{
    digitalWrite(WAKEUP_PIN ,HIGH);
    sleepNow();
      }
}
