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
uint8_t Ascale = AFS_2G, ODR = ODR_200Hz, OSR = norm_avg4, acc_filter = acc_filt_hp;
//Gyro configuration
uint8_t gyr_bwp = norm , gyr_noise_perf = gyr_noise_hp, gyr_filter_perf = gyr_filter_hp, ois_range=range_2000;
//Program variables
int16_t ax, ay, az;       // variables to hold latest sensor data values 
BMI270 BMI270;            //Define BMI270 object

void setup()
{
  /* Enable USB UART */
  Serial.begin(9600);  
  /*Begin BMI270*/
  BMI270.begin(P2_0);
  delay(1000);
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
   BMI270.initBMI270(Ascale,ODR,OSR,acc_filter,gyr_bwp,gyr_noise_perf,gyr_filter_perf,ois_range);
  }
  else 
  {
  if(c != 0x24) Serial.println(" BMI270 not functioning!");
  }
}

void loop() { 
// byte a = BMI270.getStatus();
//Serial.println(a);
 BMI270.readBMI270Data(ax,ay,az);
 Serial.print(ax);Serial.print(",");Serial.print(ay);Serial.print(",");Serial.println(az);
 }
