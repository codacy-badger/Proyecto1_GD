#include "BMI270.h"

/* Specify sensor parameters (sample rate is twice the bandwidth)
 * choices are:
      AFS_2G, AFS_4G, AFS_8G, AFS_16G  
      SR_15_5Hz, SRW_25Hz, SR_50Hz, SR_100Hz, SR_200Hz, SR_400Hz, SR_800Hz 
      sleep_Mode, lowpower_Mode, normal_Mode 
      osr0 (lowest power, lowest oversampling,lowest accuracy), osr1, osr2, osr3 (highest power, highest oversampling, highest accuracy)
      acc_filt1 (variable filter), acc_filt2 (fixed 100 Hz filter), acc_filt_lp (fixed 100 Hz filter, 1 Hz bandwidth)
*/ 
#define interruptPin P2_5 
//Accel configuration
uint8_t BMI270_Ascale = BMI270_AFS_16G, BMI270_ODR = BMI270_ODR_200Hz, BMI270_OSR = BMI270_norm_avg4, BMI270_acc_filter = BMI270_acc_filt_hp;
//Gyro configuration
uint8_t BMI270_gyr_bwp = BMI270_norm , BMI270_gyr_noise_perf = BMI270_gyr_noise_hp, BMI270_gyr_filter_perf = BMI270_gyr_filter_hp, BMI270_ois_range=BMI270_range_2000;

//Program variables
int16_t BMI270_Data[6];   // variables to hold BMI270 sensor data values
BMI270 BMI270;            //Define BMI270 object

void setup()
{
  /* Enable USB UART */
  Serial.begin(9600);  
  /*Begin BMI270*/
  BMI270.begin(P2_1);
  BMI270.initBMI270(BMI270_Ascale,BMI270_ODR,BMI270_OSR,BMI270_acc_filter,BMI270_gyr_bwp,BMI270_gyr_noise_perf,BMI270_gyr_filter_perf,BMI270_ois_range);

  delay(3000);
  //BMI270.resetBMI270();
  // Read the BMI270 Chip ID register, in order to test of communication
  Serial.println("BMI270 IMU...");
  byte c = BMI270.getChipID();  // Read CHIP_ID register for BMA400
  Serial.print("BMI270 "); Serial.print("I AM "); Serial.print(c, HEX);
  Serial.println(" ");
  delay(1000); 
  if(c == 0x24) // check if all I2C sensors with WHO_AM_I have acknowledged
  {
   Serial.println("BMI270 is online...");       
//      BMI270.initBMI270(BMI270_Ascale,BMI270_ODR,BMI270_OSR,BMI270_acc_filter,BMI270_gyr_bwp,BMI270_gyr_noise_perf,BMI270_gyr_filter_perf,BMI270_ois_range);
  }
  else 
  {
  if(c != 0x24) Serial.println(" BMI270 not functioning!");
  }
}

void loop() { 
  byte a = BMI270.getStatus();
     //if (a==1){
  BMI270.readBMI270Data(BMI270_Data);
  Serial.print(BMI270_Data[0]);Serial.print(",");Serial.print(BMI270_Data[1]);Serial.print(",");Serial.print(BMI270_Data[2]);
  Serial.print(",");
  Serial.print(BMI270_Data[3]);Serial.print(",");Serial.print(BMI270_Data[4]);Serial.print(",");Serial.println(BMI270_Data[5]);
  //   }
  //else{
     Serial.println(a);
  //  }
 }
