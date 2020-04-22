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
int En=0;
int FF_en=0;
int En_z=0;
int i=0;
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
   BMA400.SetWakeupInterruption(0x08);     
   BMA400.SetactivitychangeInt(3);
   
         
  }
  else {
  if(c != 0x90) Serial.println(" BMA400 not functioning!");
  }
}
/*_____________________________ Fin _____________________________*/

/************************* Main Funccion *************************/
void Read(){
  BMA400.readBMA400AccelData(ax,ay,az);
  byte R=BMA400.SPIreadOneRegister(BMA400_INT_STAT_2);  //Show values
  bool x_en=bitRead(R,0);
  //bool y_en=bitRead(R,1);
  bool z_en=bitRead(R,2);
  if (x_en==1 & z_en==0){En=500;}
  else{En=0;}
  //Fall detection
  if (abs(ax)<100&abs(ay)<100&abs(az)<100){
    i=i+1;
    if (i>5){
    FF_en=500;
    }
   }
  else{i=0;}
  digitalWrite(WAKEUP_PIN ,LOW);
  Serial.print(ax);Serial.print(",");Serial.print(ay);Serial.print(",");Serial.print(az);Serial.print(",");Serial.print(En);
  Serial.print(",");Serial.println(FF_en);
  //Serial.print(x_en);Serial.print(",");Serial.print(y_en);Serial.print(",");Serial.println(z_en);  
  }
void loop() { 
    Read();
}
/*_____________________________ Fin _____________________________*/
