/*
 Arduino Library for Analog Devices ADXL362 - Micropower 3-axis accelerometer
 go to http://www.analog.com/ADXL362 for datasheet
 
 
 License: CC BY-SA 3.0: Creative Commons Share-alike 3.0. Feel free 
 to use and abuse this code however you'd like. If you find it useful
 please attribute, and SHARE-ALIKE!
 
 Created June 2012
 by Anne Mahaffey - hosted on http://annem.github.com/ADXL362
 
 Modified May 2013
 by Jonathan Ruiz de Garibay

 Modified Mach 2020
 by Brayan Espinoza Garcia
 */ 

#include <Arduino.h>

#ifndef ADXL362_h
#define ADXL362_h

//Define registers
#define REG_DEVID_AD    0x00  //Contains the number 0xAD
#define REG_DEVID_MST   0x01  //Contains the number 0x1D
#define REG_PARTID      0X02  //Contains the number 0xF2
#define REG_REVID       0X03  //Contains the product revision 
#define REG_XDATA       0X08  //8 most-significant bits of X-axis
#define REG_YDATA       0X09  //8 most-significant bits of Y-axis
#define REG_ZDATA       0X0A  //8 most-significant bits of Z-axis
#define REG_STATUS      0X0B  //Describe ADXL362 conditions
#define REG_FIFO_Entries_L 0X0C //Describe the number of data samples present in FIFO buffer (0-512)
#define REG_XDATA_L     0X0E  //Sign-extended x-axis
#define REG_YDATA_L     0X10  //Sign-extended y-axis
#define REG_ZDATA_L     0X12  //Sign-extended z-axis
#define REG_TEMP_L      0X14  //Sign-extended temp
#define REG_SOFT_RESET  0X1F  //Reset the ADLX362
#define REG_THRESH_ACT_L 0X20 //Threshold for activity
#define REG_TIME_ACT_L   0X22 //Activity time register
#define REG_THRESH_INACT_L 0X23 //Threshold for inactivity
#define REG_TIME_INACT_L 0X25 //Inctivity time register
#define REG_ACT_INACT_CTL 0X27 //Activity/ Inactivity control register
#define REG_FIFO_CONTROL 0X28  //FIFO CONTROL REGISTER
#define REG_FIFO_SAMPLES 0X29  //Number of samples to store
#define REG_INTMAP1 0X2A       //INT1/INT2 FUNCTION MAP REGISTER
#define REG_INTMAP2 0X2B       //INT1/INT2 FUNCTION MAP REGISTER
#define REG_FILTER_CTL 0X2C    //Filter control register
#define REG_POWER_CTL  0X2D    //POWER CONTROL REGISTER
#define REG_SELF_TEST  0X2E    //SELF TEST TEGISTER

//Status Register bits
#define ERR_USER_REG_bit 7 //(1=Error, 0=Ok)
#define AWAKE_bit 6        //(AWAKE=1, INACTIVE=0)
#define INACT_bit 5        //(1= INACTIVITY OR FREE FALL CONDITION)
#define ACT_bit 4          //(1= ACTIVITY DETECTED AN OVER-THRESHOLD CONDITIO)
#define FIFO_OVERRUN 3     //(1= OVERRUN OR OVERFLOWED)
#define FIFO_WATERMARK 2   //(1= FIFO CONTAINS THE NUMBER SETING IN FIFO_SAMPLES)
#define FIFO_READY 1       //(1= AT LEAST ONE SAMPLE AVAIABLE)
#define DATA_READY 0       //(1= NEW VALID SAMPLES  IS AVAIBLE TO BE READ)

#define Soft_Reset 0x52   

//Activity/ Inactivity Control Register
#define LINKLOOP_bit 5     //(Default mode: Activity and Inactivity are enable automatic acknoledge)
#define LINKLOOP_lenght 2
  #define Linked_mode 2 //(Linkedmode:Activity and Inactivity are sequentially no automatic acknoledge)
  #define Loop_mode   3 //(loopmode:Activity and Inactivity are sequentially automatic acknoledge)
#define INACT_REF 3     // (1=Referenced mode, 0=Absolute mode)
#define INACT_EN  2     // (1=Activate Under-Threshold)
#define ACT_REF 1       // (1=Referenced mode, 0=Absolute mode)
#define ACT_EN  0       // (1=Activate Over-threshold)

//FIFO_CONTROL
#define AH_bit 3          //(MSB of FIFO_SAMPLES)
#define FIFO_TEMP_bit 2   //(1=Temperature sore with X,Y,Z acceleration)
#define FIFO_MODE_bit 1   
#define FIFO_MODE_lenght 2
  #define FIFO_DISABLED     0
  #define OLDEST_SAVE_MODE  1
  #define STREAM_MODE       2
  #define Triggered_MODE    3

//INT_MAP1/ INT_MAP2
#define INT_LOW_bit 7     //(1==Active Low)
#define AWAKE_bit 6
#define INACT_bit 5
#define ACT_bit 4
#define FIFO_OVERRUN_bit 3
#define FIFO_WATERMARK_bit 2
#define FIFO_READY_bit 1
#define DATA_READY_bit 0

//Filter Control Register
#define RANGE_bit 7     //Measure Range Selection
#define RANGE_length 2  
  #define TWO_GEE 0x00
  #define FOUR_GEE 0x01
  #define EIGTH_GEE 0x03 
#define HALF_BW_bit 4   //(Bandwidth of anti-aliasing filter set to: 1=1/4 ODR,0= 1/2 ODR)
#define EXT_SAMPLE_bit 3 //(1=INT2 ->External Conversion Control)
#define ODR_bit 2
#define ODR_length 3  
  #define TWELVE_HZ 0
  #define TWENTYFIVE_HZ 1
  #define FIFTY_HZ  2
  #define ONEHUNDRED_HZ 3 //Default
  #define TWOHUNDRED_HZ 4
  #define FOURHUNDRER_HZ 5

//POWER CONTROL REGISTER
#define EXT_CLK_bit 6     //(1=RUN EXTERNAL CLOCK)
#define LOW_NOISE_bit 5   //(Selects power vs. noise tradeoff)
#define LOW_NOISE_length 2 
  #define NORMAL 0
  #define LOW_NOISE_MODE 1
  #define ULTRA_LOW_NOISE_MODE 2
#define WAKEUP_bit 3    //(1=Operates in Wakeup mode)
#define AUTOSLEEP_bit 2 //(1=Autosleep enable)
#define MEASUSE_bit 1
#define MEASUSE_length 2 //(Select measurement Mode or Standby)
  #define STANDBY 0
  #define MEASUREMENT_MODE 2

//SELF TEST REGISTER
#define ST_bit 0 //(1=A selft test force is applied)

//SPI COMANDS
#define WRITE 0X0A
#define READ  0X0B
#define READ_FIFO 0X0D

class ADXL362
{
public:

	ADXL362();
	
	//
	// Basic Device control and readback functions
	                                                                                                                           //
	void begin(int16_t chipSelectPin = 10); 	
 	void beginMeasure(); 
  
  void FreeFallInt(int16_t Inacthreshold, int16_t InacTime);

	int16_t readXData();
	int16_t readYData();
	int16_t readZData();
	void readXYZTData16(int16_t &XData16, int16_t &YData16, int16_t &ZData16, int16_t &Temperature);
	void readXYZData8(int8_t &XData8, int8_t &YData8, int8_t &ZData8);
	int16_t readTemp();
	
	
	
	//
	// Activity/Inactivity interrupt functions
	//
	void setupDCActivityInterrupt(int16_t threshold, int16_t time);	
	void setupDCInactivityInterrupt(int16_t threshold, int16_t time);
  //void setupACActivityInterrupt(int16_t threshold, byte time);
	//void setupACInactivityInterrupt(int16_t threshold, int16_t time);
	
	//Configuration functions

 //SOFT_RESET REGISTER
	void SoftReset();

  //ACTIVITY THRESHOLD REGISTERS
  void SetActivityThreshold(int16_t act_threshold);
  //ACTICITY TIME REGISRERS
  void SetActivityTime(int16_t act_time);
  //INACTIVITY THRESHOLD REGISTERS
  void SetInactivityThreshold(int16_t act_threshold);
  //INACTICITY TIME REGISRERS
  void SetInactivityTime(int16_t act_time);
  
  //ACTIVITY INACTIVITY CONTROL
  void SetLinkLopp(byte mode); 
  void SetInactReference(bool Enable);
  void SetInactEnable(bool Enable);
  void SetActReference(bool Enable);
  void SetActEnable(bool Enable);
    
 //FILTER CONTROL REGISTER
  void setRange(byte range);
  void SetHalfBW(bool Enable);
  void SetExt_Sample(bool Enable);
  void SetODR(byte frecuency);

  //FIFO CONTROL REGISTER
    void SetFIFO_Temp(bool Enable);
    void SetFIFOMode(byte MODE);
  //FIFO Samples
 //INTMAP1
 void SetIntLow_IntI(bool Enable); 
 void SetAwake_IntI(bool Enable);
 void SetInact_IntI(bool Enable); 
 void SetAct_IntI(bool Enable);
 void SetFifoOverrun_IntI(bool Enable);
 void SetFifoWatermark_IntI(bool Enable);
 void SetFifoReady_IntI(bool Enable);
 void SetDataready_IntI(bool Enable);
  
//INTMAP2
 void SetIntLow_IntII(bool Enable); 
 void SetAwake_IntII(bool Enable);
 void SetInact_IntII(bool Enable); 
 void SetAct_IntII(bool Enable);
 void SetFifoOverrun_IntII(bool Enable);
 void SetFifoWatermark_IntII(bool Enable);
 void SetFifoReady_IntII(bool Enable);
 void SetDataready_IntII(bool Enable);

  //POWER CONTROL REGISTER
  void setMeasure(byte MEASURE);
  void SetAutosleep(bool Enable); 
  void SetWakeup(bool Enable); 
  void SetLowNoise(byte Noise); 
  void SetExt_clk(bool Enable);

  //SELF TEST
  void SetST(bool Enable);

	// need to add the following functions
	// void activityInterruptControl
	//		-Activity, Inactivity, Both
	//		- Referenced, Absolute
	//		- Free Fall
	
	//Debug functions
	void checkAllControlRegs();
	

	
	//  Low-level SPI control, to simplify overall coding
	byte SPIreadOneRegister(byte regAddress);
	void SPIwriteOneRegister(byte regAddress, byte regValue);
	int16_t  SPIreadTwoRegisters(byte regAddress);
	void SPIwriteTwoRegisters(byte regAddress, int16_t twoRegValue);
  void SPIwriteBits(byte regAddress, byte bitStart, byte length1, byte data);
  void SPIwriteBit(byte regAddress, byte bitNum, byte data);


private:
	
};

#endif
