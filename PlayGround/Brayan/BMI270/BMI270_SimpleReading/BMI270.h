/* 10/16/2018 Copyright Tlera Corporation
 *
 *  Created by Kris Winer
 *
 *  The BMA400 is an inexpensive (~$2), three-axis, medium-resolution (12-bit), ultra-low power (800 nA low power mode) accelerometer
 *  in a tiny 2 mm x 2 mm LGA12 package with 1024-byte FIFO,
 *  two multifunction interrupts and widely configurable sample rate (15 - 800 Hz), full range (2 - 16 g), low power modes,
 *  and interrupt detection behaviors. This accelerometer is nice choice for motion-based wake/sleep,
 *  tap detection, step counting, and simple orientation estimation.
 *
 *  Library may be used freely and without limit with attribution.
 *
 *  Modfied by: Brayan Espinoza Garcia
 *  March 2020
 */

#ifndef BMI270_h
#define BMI270_h

#include <Energia.h>

/* Register Map BMI270
// https://www.bosch-sensortec.com/media/boschsensortec/downloads/datasheets/bst-bmi270-ds000-2.pdf
*/
#define BMI270_CHIPID          0x00     
#define BMI270_ERR_REG         0x02     
#define BMI270_STATUS          0x03     
#define BMI270_DATA0           0x04     
#define BMI270_DATA1           0x05     
#define BMI270_DATA2           0x06     
#define BMI270_DATA3           0x07     
#define BMI270_DATA4           0x08   
#define BMI270_DATA5           0x09   
#define BMI270_DATA6           0x0A     
#define BMI270_DATA7           0x0B    
#define BMI270_DATA8           0x0C     
#define BMI270_DATA9           0x0D     
#define BMI270_DATA10          0x0E     
#define BMI270_DATA11          0x0F     
#define BMI270_DATA12          0x10     
#define BMI270_DATA13          0x11     
#define BMI270_DATA14          0x12     
#define BMI270_DATA15          0x13     
#define BMI270_DATA16          0x14     
#define BMI270_DATA17          0x15     
#define BMI270_DATA18          0x16     
#define BMI270_DATA19          0x17     
#define BMI270_SENSORTIME_0    0x18     
#define BMI270_SENSORTIME_1    0x19     
#define BMI270_SENSORTIME_2    0x1A     
#define BMI270_EVENT           0x1B     
#define BMI270_INT_STATUS_0    0x1C     
#define BMI270_INT_STATUS_1    0x1D    
#define BMI270_SC_OUT_0        0x1E    
#define BMI270_SC_OUT_1        0x1F     
#define BMI270_WR_GEST_ACT     0x20     
#define BMI270_INTERNAL_SATUS  0x21     
#define BMI270_TEMPERATURE0    0x22     
#define BMI270_TEMPERATURE1    0x23     
#define BMI270_FIFO_LENGTH0    0x24
#define BMI270_FIFO_LENGTH1    0x25     
#define BMI270_FIFO_DATA       0x26     
#define BMI270_FEAT_PAGE       0x2F    
#define BMI270_ACC_CONFIG      0x40
#define BMI270_ACC_RANGE       0x41
#define BMI270_GYR_CONF        0x42
#define BMI270_GYR_RANGE       0x43
#define BMI270_AUX_CONF        0x44
#define BMI270_FIFO_DOWNS      0x45
#define BMI270_FIFO_WTM_0      0x46
#define BMI270_FIFO_WTM_1      0x47
#define BMI270_FIFO_CONFIG_0   0x48
#define BMI270_FIFO_CONFIG_1   0x49
#define BMI270_SATURATION      0x4A
#define BMI270_AUX_DEV_ID      0x4B
#define BMI270_AUX_IF_C0NF     0x4C
#define BMI270_AUX_RD_ADDR     0x4D
#define BMI270_AUX_WR_ADDR     0x4E
#define BMI270_AUX_WR_DATA     0x4F
#define BMI270_ERR_REG_MSK     0x52
#define BMI270_INT1_IO_CTRL    0x53
#define BMI270_INT2_IO_CTRL    0x54
#define BMI270_INT_LATCH       0x55
#define BMI270_INT1_MAP_FEAT   0x56
#define BMI270_INT2_MAP_FEAT   0x57
#define BMI270_INT_MAP_DATA    0x58
#define BMI270_INIT_CTRL       0x59
#define BMI270_INIT_ADDR_0     0x5B
#define BMI270_INIT_ADDR_1     0x5C
#define BMI270_INIT_DATA       0x5E
#define BMI270_INTERNAL_ERROR  0x5F
#define BMI270_AUX_IF_TRIM     0x68
#define BMI270_GYR_CRT_CONF    0x69
#define BMI270_NVM_CONF        0x6A
#define BMI270_IF_CONF         0x6B
#define BMI270_DRV             0x6C
#define BMI270_ACC_SELF_TEST   0x6D
#define BMI270_GYR_SELF_TEST_AXES   0x6E
#define BMI270_NV_CONF              0x70
#define BMI270_OFFSET_0             0x71
#define BMI270_OFFSET_1             0x72
#define BMI270_OFFSET_2             0x73
#define BMI270_OFFSET_3             0x74
#define BMI270_OFFSET_4             0x75
#define BMI270_OFFSET_5             0x76
#define BMI270_OFFSET_6             0x77
#define BMI270_PWR_CONF             0x7C
#define BMI270_PWR_CTRL             0x7D
#define BMI270_CMD                  0x7E

//I2c adress
  #define BMA400_ADDRESS  0x24  // for I2C conections
//ACCEL CONIGURATION
  //Accel Auto Full Scale (acc_range)
    #define AFS_2G           0x00
    #define AFS_4G           0x01
    #define AFS_8G           0x02
    #define AFS_16G          0x03
  //Bandwidth parameter (acc_bwp)
  /*Bandwith parameter determines filter configuration
  (acc_filt_perf=1) y promediando par el caso de submuestreo
  (acc_filt_perf=0) 
  */
    #define osr4_avg1        0x00  
    #define osr2_avg2        0x01
    #define norm_avg4        0x02
    #define cic_avg8         0x03
    #define res_avg16        0x04
    #define res_avg32        0x05
    #define res_avg64        0x06
    #define res_avg128       0x07
  //Define (acc_filter_perf)
    #define acc_filt_ulp     0x00 // power optimized
    #define acc_filt_hp      0x01 // power optimized

//GYRO CONFIGURATION
  //Gyroscope bandwidth (gyr_bwp)
    #define osr4             0x00  
    #define osr2             0x01  
    #define norm             0x02  
    #define res              0x03
  //Gyroscope_noise_perf (gyr_noise_perf)
    #define gyr_noise_ulp    0x00  
    #define gyr_noise_hp     0x01  
  //Gyroscope_filter_perf (gyr_filter_perf)
    #define gyr_filter_ulp    0x00  
    #define gyr_filter_hp     0x01  
  //ois_range
    #define range_252         0x00
    #define range_2000        0x01
    
//ACCEL AND GYRO CONFIGURATION 
//(gyr_range) and (acc_range)
  #define ODR_0p78Hz        0x01
  #define ODR_1p5Hz         0x02  
  #define ODR_3p1Hz         0x03  
  #define ODR_6p25Hz        0x04
  #define ODR_12p5Hz        0x05
  #define ODR_25Hz          0x06
  #define ODR_50Hz          0x07
  #define ODR_100Hz         0x08
  #define ODR_200Hz         0x09  
  #define ODR_400Hz         0x0A
  #define ODR_800Hz         0x0B  
  #define ODR_1KHz          0x0C  
  #define ODR_3K2Hz         0x0D  
  #define ODR_6K4Hz         0x0E  
  #define ODR_12K8Hz        0x0F  



class BMI270
{
  public:
  BMI270();

  void begin (int16_t chipSelectPin = 10);
  //float getAres(uint8_t Ascale);
  uint8_t getChipID();
  uint8_t getStatus();
  void resetBMI270();
  void initBMI270(uint8_t Ascale, uint8_t ODR, uint8_t Accel_OSR, uint8_t acc_filter, uint8_t gyr_bwp, uint8_t gyr_noise_perf, uint8_t gyr_filter_perf, uint8_t ois_range);
  void readBMI270Data(int16_t &XData16, int16_t &YData16, int16_t &ZData16);
 // void CompensationBMA400(uint8_t Ascale, uint8_t SR, uint8_t power_Mode, uint8_t OSR, uint8_t acc_filter, float * offset);
 // void selfTestBMA400();
 // void SetWakeupInterruption();
 // int16_t readBMA400TempData();
 // void activateNoMotionInterrupt();
 // void deactivateNoMotionInterrupt();
 // 

 // //Autolowpowerfunctions
 // void SetAutolowpowertimeout(uint16_t time_code);
 // void SetactivitychangeInt(byte Threshold);
 // //Basic SPI functions
  byte SPIreadOneRegister(byte regAddress);
  void SPIreadRegisters(uint8_t regAddress, uint8_t *data , uint16_t len);
  void SPIwriteOneRegister(byte regAddress, byte regValue);
  void SPIwriteRegisters(byte regAddress, const uint8_t *data, uint16_t len); 
  void SPIwriteBits(byte regAddress, byte bitStart, byte length1, byte data);
  void SPIwriteBit(byte regAddress, byte bitNum, byte data);
 




  private:
  uint8_t _intPin1;
  uint8_t _intPin2;
  float _aRes;
};

#endif
