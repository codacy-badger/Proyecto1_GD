/*****************************************************************/
/****************************** E2I ******************************/
/*****************************************************************/
/******************* Programa de Sensor BMA400 *******************/
#include "BMA400.h"
/*_____________________________ Fin _____________________________*/

/************************ Pin de Int Sen *************************/
#define interruptPin P2_5 
/*_____________________________ Fin _____________________________*/

/********************* ACC Sensor Variables **********************/
uint8_t Ascale = AFS_2G, SR = SR_200Hz, power_Mode = normal_Mode, OSR = osr3, acc_filter = acc_filt1;
int16_t ax, ay, az;       
const int WAKEUP_PIN = P1_3;
bool valInterrupt = 0;
BMA400 BMA400;
/*_____________________________ Fin _____________________________*/

/************************* Main Funccion *************************/
void setup()
{
  Serial.begin(9600);
  BMA400.begin(P2_0);
  Serial.println("BMA400 accelerometer...");
  byte c = BMA400.getChipID();  
  Serial.print("BMA400 "); Serial.print("I AM "); Serial.print(c, HEX);
  Serial.println(" ");
  delay(1000); 

  if(c == 0x90){
   Serial.println("BMA400 is online..."); Serial.println(" ");
   BMA400.resetBMA400();                                                  
   BMA400.initBMA400(Ascale, SR, normal_Mode, OSR, acc_filter);           
   BMA400.SetWakeupInterruption(0x80);     
   attachInterrupt(interruptPin,interrupt,RISING);               
  }
  else {
  if(c != 0x90) Serial.println(" BMA400 not functioning!");
  }
}
/*_____________________________ Fin _____________________________*/

/************************* Main Funccion *************************/
void Read(){
  BMA400.readBMA400AccelData(ax,ay,az);
  digitalWrite(WAKEUP_PIN ,LOW);
  Serial.print(ax);Serial.print(",");Serial.print(ay);Serial.print(",");Serial.println(az);   
  }
/*_____________________________ Fin _____________________________*/

/************************* Main Funccion *************************/
void sleepNow(){
  Serial.print("\nBMA400 went to sleep - Put MSP to sleep now \n");
  suspend();
  }
/*_____________________________ Fin _____________________________*/

/************************ Main Funccion **************************/
void interrupt(){
  wakeup();
  }
/*_____________________________ Fin _____________________________*/

/************************** Main Loop ****************************/
void loop() { 
  valInterrupt = digitalRead(interruptPin);
  if(valInterrupt == 1){
    Read();
    } 
  else{
    digitalWrite(WAKEUP_PIN, HIGH);
    sleepNow();
      }
}
/*_____________________________ Fin _____________________________*/
