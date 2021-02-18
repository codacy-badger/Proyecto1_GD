#include "BMI270.h"
#include "BMA400.h"

//++++++++++++++++++++BMA400 CONFIGURATION++++++++++++++++++++++++++
uint8_t BMA400_Ascale = BMA400_AFS_2G, BMA400_SR = BMA400_SR_200Hz, BMA400_power_Mode = BMA400_normal_Mode, BMA400_OSR = BMA400_osr3, BMA400_acc_filter = BMA400_acc_filt1;

//++++++++++++++++++++BMI270 CONFIGURATION++++++++++++++++++++++++++
//Accel configuration
uint8_t BMI270_Ascale = BMI270_AFS_16G, BMI270_ODR = BMI270_ODR_200Hz, BMI270_OSR = BMI270_norm_avg4, BMI270_acc_filter = BMI270_acc_filt_hp;
//Gyro configuration
uint8_t BMI270_gyr_bwp = BMI270_norm , BMI270_gyr_noise_perf = BMI270_gyr_noise_hp, BMI270_gyr_filter_perf = BMI270_gyr_filter_hp, BMI270_ois_range=BMI270_range_2000;

//++++++++++++++++++++++++++DATA VARIABLES++++++++++++++++++++
int16_t BMA400_Data[3];       // variables to hold BMA400 sensor data values 
int16_t BMI270_Data[6];       // variables to hold BMI270 sensor data values 

//++++++++++++++++++++++++++DEFINE OBJECTS+++++++++++++++++++++++
BMI270 BMI270;            //Define BMI270 object
BMA400 BMA400;            //Define BMI270 object

void setup()
{
  /* Enable USB UART */
  Serial.begin(9600);  
  /*Begin BMI270 and BMA400*/
  BMA400.begin(P2_0);
  BMI270.begin(P2_1);
  delay(1000);
  
  // Read the BMI270 Chip ID register, in order to test of communication
  byte c = BMI270.getChipID();  // Read CHIP_ID register for BMA400
  delay(1000); 
  if(c == 0x24) // check if all I2C sensors with WHO_AM_I have acknowledged
  {
   Serial.println("BMI270 is online...");       
   BMI270.initBMI270(BMI270_Ascale,BMI270_ODR,BMI270_OSR,BMI270_acc_filter,BMI270_gyr_bwp,BMI270_gyr_noise_perf,BMI270_gyr_filter_perf,BMI270_ois_range);
  }
   c = BMA400.getChipID();  // Read CHIP_ID register for BMA400
   delay(1000); 
  if(c == 0x90) // check if all I2C sensors with WHO_AM_I have acknowledged
  {
   Serial.println("BMA400 is online..."); 
   BMA400.initBMA400(BMA400_Ascale,BMA400_SR,BMA400_normal_Mode,BMA400_OSR,BMA400_acc_filter);          // Initialize sensor in desired mode for application       
  }
}

void loop() { 
  byte a = BMI270.getStatus();
  //if(a==1){
  BMI270.readBMI270Data(BMI270_Data);       //Datos almacenados en 16 bits
  BMA400.readBMA400AccelData(BMA400_Data);  //Datos almacenados en 12 bits
  Serial.print(BMA400_Data[0]);Serial.print(",");Serial.print(BMA400_Data[1]);Serial.print(",");Serial.print(BMA400_Data[2]);
  Serial.print(",");
  Serial.print(BMI270_Data[0]);Serial.print(",");Serial.print(BMI270_Data[1]);Serial.print(",");Serial.println(BMI270_Data[2]);
  //}
  //else{
  // Serial.println(a);
  //  }
 }
