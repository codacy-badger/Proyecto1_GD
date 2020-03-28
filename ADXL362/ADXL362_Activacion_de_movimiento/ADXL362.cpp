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

 Modified March 2020
 by Brayan Espinoza Garcia
 */ 

#include <Arduino.h>
#include "ADXL362.h"
#include <SPI.h>

//#define ADXL362_DEBUG

int16_t slaveSelectPin = 10;

ADXL362::ADXL362() {
}


/*
Function begin()
 Initial SPI setup and soft reset of device
*/

void ADXL362::begin(int16_t chipSelectPin) {
  //Begin SPI Comunicaction
	slaveSelectPin = chipSelectPin;
	pinMode(slaveSelectPin, OUTPUT);
	SPI.begin();
	SPI.setDataMode(SPI_MODE0);	//CPHA = CPOL = 0    MODE = 0                
 }

void ADXL362::beginMeasure() {
  setMeasure(MEASUREMENT_MODE); //Set REG_POWER_CTL into measurement mode
	setRange(TWO_GEE);            //Set ADLX Range into Two Gees
  SetODR(ONEHUNDRED_HZ);      //Set ORD to 100Hz (Default)
  //SetODR(TWELVE_HZ);            //Set ODR to 12.5Hz
	delay(10);	
}

void ADXL362::FreeFallInt(int16_t Inacthreshold, int16_t InacTime){
  SetInactivityThreshold(Inacthreshold);
  SetInactivityTime(InacTime);
  SetInactEnable(true);
  SetInact_IntI(true);
  //SetInact_IntII(true);
  setRange(EIGTH_GEE);            //Set ADLX Range into Two Gees
  }

void ADXL362::readXYZTData16(int16_t &XData16, int16_t &YData16, int16_t &ZData16, int16_t &Temperature){
    // Function that reads XYZ axis and temperature with 16bit resolution
    // A burst read of all three axis is required to guarantee all measurements correspond to same sample time
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(READ);  // read instruction
    SPI.transfer(REG_XDATA_L);  // Start at XData Reg
    XData16 = SPI.transfer(0x00);
    XData16 = XData16 + (SPI.transfer(0x00) << 8);
    YData16 = SPI.transfer(0x00);
    YData16 = YData16 + (SPI.transfer(0x00) << 8);
    ZData16 = SPI.transfer(0x00);
    ZData16 = ZData16 + (SPI.transfer(0x00) << 8);
    Temperature = SPI.transfer(0x00);
    Temperature = Temperature + (SPI.transfer(0x00) << 8);
    digitalWrite(slaveSelectPin, HIGH);
}

void ADXL362::readXYZData8(int8_t &XData8, int8_t &YData8, int8_t &ZData8){
    // Function that reads XYZ axis with 8bits resolution
    // A burst read of all three axis is required to guarantee all measurements correspond to same sample time
    digitalWrite(slaveSelectPin, LOW);
    SPI.transfer(READ);  // read instruction
    SPI.transfer(REG_XDATA);  // Start at XData Reg
    XData8 = SPI.transfer(0x00);
    YData8 = SPI.transfer(0x00);
    ZData8 = SPI.transfer(0x00);
    digitalWrite(slaveSelectPin, HIGH);
}

int16_t ADXL362::readXData(){
  //Function that reads 16bit X-Axis
	int16_t XDATA = SPIreadTwoRegisters(REG_XDATA_L);
	return XDATA;
}
int16_t ADXL362::readYData(){
	//Function that reads 16bit Y-Axis
	int16_t YDATA = SPIreadTwoRegisters(REG_YDATA_L);
	return YDATA;
}
int16_t ADXL362::readZData(){
	//Function that reads 16bit Z-Axis
	int16_t ZDATA = SPIreadTwoRegisters(REG_ZDATA_L);
  return ZDATA;
}
int16_t ADXL362::readTemp(){
	//Function that reads 16bit temperature
	int16_t TEMP = SPIreadTwoRegisters(REG_TEMP_L);
	return TEMP;
}

void ADXL362::setupDCActivityInterrupt(int16_t threshold, int16_t timeact){
	SetActivityThreshold(threshold);          // Setup activity threshold
	SetActivityTime(timeact);                 // Setup activity time
  SetActEnable(true);                       // Turn-on activity enable
}

void ADXL362::setupDCInactivityInterrupt(int16_t threshold, int16_t timeinact){
	// Setup motion and time thresholds
  SetInactivityThreshold(threshold);          // Setup inactivity threshold
  SetInactivityTime(timeinact);               // Setup inactivity time
  SetInactEnable(true);                       // turn on inactivity interrupt
	
}

void ADXL362::checkAllControlRegs(){
	//byte filterCntlReg = SPIreadOneRegister(0x2C);
	//byte ODR = filterCntlReg & 0x07;  Serial.print("ODR = ");  Serial.println(ODR, HEX);
	//byte ACT_INACT_CTL_Reg = SPIreadOneRegister(0x27);      Serial.print("ACT_INACT_CTL_Reg = "); Serial.println(ACT_INACT_CTL_Reg, HEX);
	digitalWrite(slaveSelectPin, LOW);
	SPI.transfer(0x0B);  // read instruction
	SPI.transfer(0x20);  // Start burst read at Reg 20
#ifdef ADXL362_DEBUG
	Serial.println("Start Burst Read of all Control Regs - Library version 6-5-2014:");
	Serial.print("Reg 20 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 21 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 22 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 23 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 24 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 25 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 26 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 27 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 28 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 29 = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 2A = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 2B = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 2C = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 2D = "); 	Serial.println(SPI.transfer(0x00), HEX);
	Serial.print("Reg 2E = "); 	Serial.println(SPI.transfer(0x00), HEX);
#endif
	digitalWrite(slaveSelectPin, HIGH);
}


// SOFT RESET REGISTER
void ADXL362::SoftReset(){
  // Function that makes a soft Resete
  SPIwriteOneRegister(REG_SOFT_RESET, Soft_Reset);  // Write to SOFT RESET, "R"
  delay(10);
}

//ACTIVITY THRESHOLD REGISTERS
void ADXL362::SetActivityThreshold(int16_t act_threshold){
  SPIwriteTwoRegisters(REG_THRESH_ACT_L, act_threshold);
  }
//ACTICITY TIME REGISRERS
void ADXL362::SetActivityTime(int16_t act_time){
  SPIwriteTwoRegisters(REG_TIME_ACT_L, act_time);
  }
//INACTIVITY THRESHOLD REGISTERS
void ADXL362::SetInactivityThreshold(int16_t act_threshold){
  SPIwriteTwoRegisters(REG_THRESH_INACT_L, act_threshold);
  }
//INACTICITY TIME REGISRERS
void ADXL362::SetInactivityTime(int16_t act_time){
  SPIwriteTwoRegisters(REG_TIME_INACT_L, act_time);
  }
//ACTIVITY INACTIVITY CONTROL
  void ADXL362::SetLinkLopp(byte mode){
    SPIwriteBits(REG_ACT_INACT_CTL, LINKLOOP_bit, LINKLOOP_lenght, mode);
  }
  void ADXL362::SetInactReference(bool Enable){
    SPIwriteBit(REG_ACT_INACT_CTL, INACT_REF, Enable);
  } 
  void ADXL362::SetInactEnable(bool Enable){
    SPIwriteBit(REG_ACT_INACT_CTL, INACT_EN, Enable);
  }
  void ADXL362::SetActReference(bool Enable){
    SPIwriteBit(REG_ACT_INACT_CTL, ACT_REF, Enable);
  }
  void ADXL362::SetActEnable(bool Enable){
    SPIwriteBit(REG_ACT_INACT_CTL, ACT_EN, Enable);
  }

//FIFO CONTROL
//FIFO Samples


//INTMAP1
 void ADXL362::SetIntLow_IntI(bool Enable){
    SPIwriteBit(REG_INTMAP1, INT_LOW_bit, Enable);
  } 
 void ADXL362::SetAwake_IntI(bool Enable){
    SPIwriteBit(REG_INTMAP1, AWAKE_bit, Enable);
  } 
 void ADXL362::SetInact_IntI(bool Enable){
    SPIwriteBit(REG_INTMAP1, INACT_REF, Enable);
  } 
 void ADXL362::SetAct_IntI(bool Enable){
    SPIwriteBit(REG_INTMAP1, ACT_bit, Enable);
  } 
 void ADXL362::SetFifoOverrun_IntI(bool Enable){
    SPIwriteBit(REG_INTMAP1, FIFO_OVERRUN_bit, Enable);
  } 
 void ADXL362::SetFifoWatermark_IntI(bool Enable){
    SPIwriteBit(REG_INTMAP1, FIFO_WATERMARK_bit, Enable);
  } 
 void ADXL362::SetFifoReady_IntI(bool Enable){
    SPIwriteBit(REG_INTMAP1, FIFO_READY_bit, Enable);
  } 
 void ADXL362::SetDataready_IntI(bool Enable){
    SPIwriteBit(REG_INTMAP1, DATA_READY_bit, Enable);
  } 
  
//INTMAP2
 void ADXL362::SetIntLow_IntII(bool Enable){
    SPIwriteBit(REG_INTMAP2, INT_LOW_bit, Enable);
  } 
 void ADXL362::SetAwake_IntII(bool Enable){
    SPIwriteBit(REG_INTMAP2, AWAKE_bit, Enable);
  } 
 void ADXL362::SetInact_IntII(bool Enable){
    SPIwriteBit(REG_INTMAP2, INACT_REF, Enable);
  } 
 void ADXL362::SetAct_IntII(bool Enable){
    SPIwriteBit(REG_INTMAP2, ACT_bit, Enable);
  } 
 void ADXL362::SetFifoOverrun_IntII(bool Enable){
    SPIwriteBit(REG_INTMAP2, FIFO_OVERRUN_bit, Enable);
  } 
 void ADXL362::SetFifoWatermark_IntII(bool Enable){
    SPIwriteBit(REG_INTMAP2, FIFO_WATERMARK_bit, Enable);
  } 
 void ADXL362::SetFifoReady_IntII(bool Enable){
    SPIwriteBit(REG_INTMAP2, FIFO_READY_bit, Enable);
  } 
 void ADXL362::SetDataready_IntII(bool Enable){
    SPIwriteBit(REG_INTMAP2, DATA_READY_bit, Enable);
  } 
  
// FILTER CONTROL REGISTER
void ADXL362::setRange(byte range) {
  //Set FILTER CONTROL REGISTER 
  SPIwriteBits(REG_FILTER_CTL,RANGE_bit,RANGE_length,range);
  }
void ADXL362::SetHalfBW(bool Enable){
    SPIwriteBit(REG_FILTER_CTL, HALF_BW_bit, Enable);
  }
void ADXL362::SetExt_Sample(bool Enable){
    SPIwriteBit(REG_FILTER_CTL, EXT_SAMPLE_bit, Enable);
  }
void ADXL362::SetODR(byte frecuency) {
  //Set FILTER CONTROL REGISTER 
  SPIwriteBits(REG_FILTER_CTL,ODR_bit,ODR_length,frecuency);
  }  
  
//POWER CONTROL REGISTER
 void ADXL362::setMeasure(byte MEASURE) {
  //Set FILTER CONTROL REGISTER  
  SPIwriteBits(REG_POWER_CTL, MEASUSE_bit, MEASUSE_length, MEASURE);
  }
 void ADXL362::SetAutosleep(bool Enable){
    SPIwriteBit(REG_POWER_CTL, AUTOSLEEP_bit, Enable);
  } 
 void ADXL362::SetWakeup(bool Enable){
    SPIwriteBit(REG_POWER_CTL, WAKEUP_bit, Enable);
  } 
 void ADXL362::SetLowNoise(byte Noise) {
  //Set FILTER CONTROL REGISTER 
  SPIwriteBits(REG_FILTER_CTL,LOW_NOISE_bit,LOW_NOISE_length,Noise);
  }
  void ADXL362::SetExt_clk(bool Enable){
    SPIwriteBit(REG_POWER_CTL, EXT_CLK_bit, Enable);
  } 

//SELF TEST
  void ADXL362::SetST(bool Enable){
    SPIwriteBit(REG_SELF_TEST, ST_bit, Enable);
  } 
/*
 *+++++++++BASIC SPI ROUTINES TO SIMPLY CODE+++++++++++
 */

// read and write one register
byte ADXL362::SPIreadOneRegister(byte regAddress){
	byte regValue = 0;
  digitalWrite(slaveSelectPin, LOW);
	SPI.transfer(READ);  // read instruction
	SPI.transfer(regAddress);
	regValue = SPI.transfer(0x00);
	digitalWrite(slaveSelectPin, HIGH);
	return regValue;
}

void ADXL362::SPIwriteOneRegister(byte regAddress, byte regValue){
 	digitalWrite(slaveSelectPin, LOW);
	SPI.transfer(WRITE);  // write instruction
	SPI.transfer(regAddress);
	SPI.transfer(regValue);
	digitalWrite(slaveSelectPin, HIGH);
}

int16_t ADXL362::SPIreadTwoRegisters(byte regAddress){
	int16_t twoRegValue = 0;
  
	digitalWrite(slaveSelectPin, LOW);
	SPI.transfer(READ);  // read instruction
	SPI.transfer(regAddress);  
	twoRegValue = SPI.transfer(0x00);
	twoRegValue = twoRegValue + (SPI.transfer(0x00) << 8);
	digitalWrite(slaveSelectPin, HIGH);

	return twoRegValue;
}  

void ADXL362::SPIwriteTwoRegisters(byte regAddress, int16_t twoRegValue){
	byte twoRegValueH = twoRegValue >> 8;
	byte twoRegValueL = twoRegValue;
  
	digitalWrite(slaveSelectPin, LOW);
	SPI.transfer(WRITE);  // write instruction
	SPI.transfer(regAddress);  
	SPI.transfer(twoRegValueL);
	SPI.transfer(twoRegValueH);
	digitalWrite(slaveSelectPin, HIGH);
}


void ADXL362::SPIwriteBits(byte regAddress, byte bitStart, byte length1, byte data){
    //      010 value to write
    // 76543210 bit numbers
    //    xxx   args: bitStart=4, length=3
    // 00011100 mask byte
    // 10101111 original value (sample)
    // 10100011 original & ~mask
    // 10101011 masked | value
    byte b;
    b=SPIreadOneRegister(regAddress);
    byte mask = ((1 << length1) - 1) << (bitStart - length1 + 1);
    data <<= (bitStart - length1 + 1); // shift data into correct position
    data &= mask; // zero all non-important bits in data
    b &= ~(mask); // zero all important bits in existing byte
    b |= data; // combine data with existing byte
    SPIwriteOneRegister(regAddress, b);   
 }

void ADXL362::SPIwriteBit(byte regAddress, byte bitNum, byte data){
  byte b;
  b=SPIreadOneRegister(regAddress);
  b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
  SPIwriteOneRegister(regAddress, b);   
  }
