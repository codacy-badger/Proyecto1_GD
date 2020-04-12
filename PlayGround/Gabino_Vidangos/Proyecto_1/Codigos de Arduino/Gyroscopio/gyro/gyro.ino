//Written by Ahmet Burkay KIRNIK
//Measurement of Angle with MPU-6050(GY-521)

#include<Wire.h>
#include <SimpleKalmanFilter.h>
const int MPU_addr=0x68; 
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;

int minVal=265; int maxVal=402;

double x; double y; double z;
SimpleKalmanFilter pressureKalmanFilter(1, 1, 0.01);
void setup(){ 
  Wire.begin(); 
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x6B); Wire.write(0); 
  Wire.endTransmission(true); 
  Serial.begin(9600); } 

void loop(){ 
  Wire.beginTransmission(MPU_addr); 
  Wire.write(0x3B); 
  Wire.endTransmission(false); 
  Wire.requestFrom(MPU_addr,14,true); 
  AcX=Wire.read()<<8|Wire.read(); 
  AcY=Wire.read()<<8|Wire.read(); 
  AcZ=Wire.read()<<8|Wire.read(); 
  int xAng = map(AcX,minVal,maxVal,-90,90); 
  int yAng = map(AcY,minVal,maxVal,-90,90); 
  int zAng = map(AcZ,minVal,maxVal,-90,90);

  x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI); 
  y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI); 
  z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);
  float est_x = pressureKalmanFilter.updateEstimate(x);
  float est_y = pressureKalmanFilter.updateEstimate(y);
  float est_z = pressureKalmanFilter.updateEstimate(z);

Serial.print(x);
Serial.print(",");
Serial.print(y);
Serial.print(",");
Serial.print(z);
Serial.print(",");
Serial.println(Tmp);
//#Serial.print(",");
//#Serial.print(z);
//#Serial.print(",");
//#Serial.println(est_z);
delay(100);}
//Serial.print("-----------------------------------------");  }
