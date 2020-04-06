#include "BMA400.h"

/* Specify sensor parameters (sample rate is twice the bandwidth)
 * choices are:
      AFS_2G, AFS_4G, AFS_8G, AFS_16G  
      SR_15_5Hz, SRW_25Hz, SR_50Hz, SR_100Hz, SR_200Hz, SR_400Hz, SR_800Hz 
      sleep_Mode, lowpower_Mode, normal_Mode 
      osr0 (lowest power, lowest oversampling,lowest accuracy), osr1, osr2, osr3 (highest power, highest oversampling, highest accuracy)
      acc_filt1 (variable filter), acc_filt2 (fixed 100 Hz filter), acc_filt_lp (fixed 100 Hz filter, 1 Hz bandwidth)
*/ 
uint8_t Ascale = AFS_2G, SR = SR_100Hz, power_Mode =normal_Mode, OSR = osr0, acc_filter = acc_filt1;

float aRes;             // scale resolutions per LSB for the sensor
int16_t accelCount[3];  // Stores the 16-bit signed accelerometer sensor output
int16_t tempCount;      // temperature raw count output
float   temperature;    // Stores the real internal chip temperature in degrees Celsius
float ax, ay, az;       // variables to hold latest sensor data values 
float offset[3];        // accel bias offsets

BMA400 BMA400;

void setup()
{
  Serial.begin(9600);     //Enable USB UART 
  BMA400.begin(P2_0);     //Begin BMA400 SPI comunicaction and select cs pin
  byte c = BMA400.getChipID();  // Read CHIP_ID register for BMA400 to test comunication
  delay(1000); 
  if(c == 0x90) // check if SPI comunication is working with WHO_AM_I register
  {
    aRes = BMA400.getAres(Ascale);                                       // get sensor resolutions, only need to do this once
    BMA400.resetBMA400();                                                // software reset before initialization
    delay(100);      
    BMA400.selfTestBMA400();                                             // perform sensor self test
    BMA400.resetBMA400();                                                // software reset before initialization
    delay(1000);                                                         // give some time to read the screen
    BMA400.CompensationBMA400(Ascale, SR, normal_Mode, OSR, acc_filter, offset); // quickly estimate offset bias in normal mode
    BMA400.initBMA400(Ascale, SR, power_Mode, OSR, acc_filter);          // Initialize sensor in desired mode for application                     
  }
  else 
  {
    if(c != 0x90) Serial.println("BMA400 is not working...");
  }
}

void loop()
{
  BMA400.readBMA400AccelData(accelCount[0],accelCount[1],accelCount[2]);
  tempCount=BMA400.readBMA400TempData();
  temperature=tempCount/2+23;
  Serial.print(accelCount[0]);Serial.print(","); Serial.print(accelCount[1]);Serial.print(","); Serial.println(accelCount[2]);
  //Serial.print("Temperatura: "); Serial.println(temperature);
 }  
