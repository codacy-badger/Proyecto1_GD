#include "BMA400.h"

/* Specify sensor parameters (sample rate is twice the bandwidth)
 * choices are:
      AFS_2G, AFS_4G, AFS_8G, AFS_16G  
      SR_15_5Hz, SRW_25Hz, SR_50Hz, SR_100Hz, SR_200Hz, SR_400Hz, SR_800Hz 
      sleep_Mode, lowpower_Mode, normal_Mode 
      osr0 (lowest power, lowest oversampling,lowest accuracy), osr1, osr2, osr3 (highest power, highest oversampling, highest accuracy)
      acc_filt1 (variable filter), acc_filt2 (fixed 100 Hz filter), acc_filt_lp (fixed 100 Hz filter, 1 Hz bandwidth)
*/ 
#define interruptPin P2_5 

uint8_t Ascale = AFS_2G, SR = SR_200Hz, power_Mode = normal_Mode, OSR = osr3, acc_filter = acc_filt1;
int16_t ax, ay, az;       // variables to hold latest sensor data values 

BMA400 BMA400;

void setup()
{
  /* Enable USB UART */
  Serial.begin(9600);
  
  /*Begin BMA400*/
  BMA400.begin(P2_0);

      // Read the BMA400 Chip ID register, in order to test of communication
  Serial.println("BMA400 accelerometer...");
  byte c = BMA400.getChipID();  // Read CHIP_ID register for BMA400
  Serial.print("BMA400 "); Serial.print("I AM "); Serial.print(c, HEX);
  Serial.println(" ");
  delay(1000); 
  if(c == 0x90) // check if all I2C sensors with WHO_AM_I have acknowledged
  {
   Serial.println("BMA400 is online..."); Serial.println(" ");
   
   //aRes = BMA400.getAres(Ascale);                                       // get sensor resolutions, only need to do this once
   BMA400.resetBMA400();                                                // software reset before initialization
   //delay(100);      
   //BMA400.selfTestBMA400();                                             // perform sensor self test
   //BMA400.resetBMA400();                                                // software reset before initialization
   //delay(1000);                                                         // give some time to read the screen
   //BMA400.CompensationBMA400(Ascale, SR, normal_Mode, OSR, acc_filter, offset); // quickly estimate offset bias in normal mode
   BMA400.initBMA400(Ascale, SR, normal_Mode, OSR, acc_filter);          // Initialize sensor in desired mode for application 
   BMA400.SetactivitychangeInt(3);
  }
  else 
  {
  if(c != 0x90) Serial.println(" BMA400 not functioning!");
  }
  
}

void loop() { 
 BMA400.readBMA400AccelData(ax,ay,az);
 byte R=BMA400.SPIreadOneRegister(BMA400_INT_STAT_2);  //Show values
 int x_en=500*bitRead(R,0);
 int y_en=500*bitRead(R,1);
 int z_en=500*bitRead(R,2);
  //Serial.println("Data with 16-bits values:");
  Serial.print(ax);Serial.print(",");Serial.print(ay);Serial.print(",");Serial.print(az);   
  Serial.print(",");Serial.print(x_en);Serial.print(",");Serial.print(y_en);Serial.print(",");Serial.println(z_en);   
  }
