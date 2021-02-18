
#include <SoftwareSerial.h>
#include "BMA400.h"

SoftwareSerial mySerial(P2_4, P2_3); // RX, TX
uint8_t BMA400_Ascale = BMA400_AFS_2G, BMA400_SR = BMA400_SR_200Hz, BMA400_power_Mode = BMA400_normal_Mode, BMA400_OSR = BMA400_osr3, BMA400_acc_filter = BMA400_acc_filt1;
//int16_t BMA400_Data[3];       // variables to hold BMA400 sensor data values 
//const size_t dataLength = 6;
//byte BMA400_RawData[dataLength];
int16_t ax, ay, az;       
BMA400 BMA400;            //Define BMI270 object

void setup()
{
  mySerial.begin(9600);
  //mySerial.write(data, dataLength);

  Serial.begin(9600);
  //Serial.write(data, dataLength);

  BMA400.begin(P2_0);
   byte c = BMA400.getChipID();  // Read CHIP_ID register for BMA400
   Serial.print("BMA400 "); Serial.print("I AM "); Serial.println(c, HEX);
   delay(1000); 
  if(c == 0x90) // check if all I2C sensors with WHO_AM_I have acknowledged
  {
  // Serial.println("BMA400 is online...");
   //BMA400.resetBMA400();                                                // software reset before initialization 
   BMA400.initBMA400(BMA400_Ascale,BMA400_SR,BMA400_normal_Mode,BMA400_OSR,BMA400_acc_filter);          // Initialize sensor in desired mode for application       
  }
   else 
  {
  if(c != 0x90) Serial.println(" BMA400 not functioning!");
  }
}

void loop() 
{
   //BMA400.SPIreadRegisters(BMA400_ACCD_X_LSB,BMA400_RawData,6);
   //BMA400.readBMA400AccelData(BMA400_Data);  //Datos almacenados en 12 bits
   BMA400.readBMA400AccelData(ax,ay,az);  //Datos almacenados en 12 bits
  Serial.print(ax,DEC);   mySerial.print(ax,DEC);
  Serial.print(",");      mySerial.print(",");
  Serial.print(ay,DEC);   mySerial.print(ay,DEC);
  Serial.print(",");      mySerial.print(",");
  Serial.println(az,DEC); mySerial.println(az,DEC);
 // delay(100);
 

    //  Serial.print((char)BMA400_RawData[i]);
  //  if (i==5){
  //    Serial.println(" ");
  //    }
  //    else {
  //      Serial.print(",");
  //      }

  //BMA400.readBMA400AccelData(BMA400_Data);  //Datos almacenados en 12 bits
  //Serial.print(BMA400_Data[0],DEC);
  //mySerial.print(BMA400_Data[0],DEC);
  //Serial.print(",");
  //mySerial.print(",");
  //Serial.print(BMA400_Data[1],DEC);
  //mySerial.print(BMA400_Data[1],DEC);
  //Serial.print(",");
  //mySerial.print(",");
  //Serial.println(BMA400_Data[2],DEC);
  //mySerial.println(BMA400_Data[2],DEC);

  //otrometodo
  //Serial.println(BMA400_RawData[i]);
  //}
  //mySerial.print((byte*)BMA400_RawData, dataLength * sizeof(BMA400_RawData[0]));
  //delay(50);
  //Serial.write(data, dataLength);
}
