
/*
ADXL362_MotionActivatedSleep para el ADXL362 - Micropower 3-axis accelerometer
Conecciones:
 CONECCIONES:

 DEVICE   | MSP430
 -------------------
   MOSI   |  P1.7     
   MISO   |  P1.6
   SCLK   |  P1.5
   CS     |  P2.0
   INT1   |  P1.3
   GND    |  GND
   VIO    |  3.3v
   VS     |  3.3v
 
*/ 

//Incluyendo librerias para comunicación SPI y arduino
#include <SPI.h>
#include "ADXL362.h"

//Definiendo pin de interrupcion (Pin P1_3)
#define interruptPin P1_3          

//Definiendo la clase ADXL362
ADXL362 xl;

//Definiendo variables y banderas del sistema
volatile bool interruptStatus = 0;
int16_t XValue, YValue, ZValue, Temperature;


void setup(){
    Serial.begin(9600);      //Iniciando comunicacion serial
    xl.begin(P2_0);          //Se asigna el pin cs e inicia comunicacion
    delay(1000);
    xl.SoftReset();          //Se resetea el acelerometro
    delay(1000);            
    xl.setupDCActivityInterrupt(300, 10);    // 300 code activity threshold.  With default ODR = 100Hz, time threshold of 10 results in 0.1 second time threshold
    xl.setupDCInactivityInterrupt(80, 200);   // 80 code inactivity threshold.  With default ODR = 100Hz, time threshold of 30 results in 2 second time threshold
    xl.SetAwake_IntI(true);     //Active Awake Interruption
    xl.SetLinkLopp(Loop_mode);  //Active Loop Mode
    xl.SetInactReference(true); //Active Inactive Reference Mode
    xl.SetActReference(true);   //Active Active Reference Mode
    xl.SetAutosleep(true);      // turn on Autosleep bit

    // turn on Measure mode
    //
    xl.beginMeasure();                      // DO LAST! enable measurement mode   
    //xl.checkAllControlRegs();               // check some setup conditions    
    delay(100);
 
    // Setup interrupt function on Arduino
    pinMode(interruptPin, INPUT);    
    attachInterrupt(interruptPin, interruptFunction, RISING);  // A high on output of ADXL interrupt means ADXL is awake, and wake up Arduino 
}



void loop(){
  //
  //  Check ADXL362 interrupt status to determine if it's asleep
  //
  interruptStatus = digitalRead(interruptPin);

// if ADXL362 is asleep, call suspend()  
  if(interruptStatus == 0) { 
    Serial.print("\nADXL went to sleep - Put Arduino to sleep now \n");
    digitalWrite(7, LOW);    // Turn off LED as visual indicator of asleep
    delay(100);
    suspend();   
  }
  
// if ADXL362 is awake, report XYZT data to Serial Monitor
  else{
    delay(10);
    //digitalWrite(7, HIGH);    // Turn on LED as visual indicator of awake
    Serial.println("\nArduino is Awake! \n");
    xl.readXYZTData16(XValue, YValue, ZValue, Temperature);  
    Serial.print("XVALUE=");
    Serial.print(XValue);   
    Serial.print("\tYVALUE=");
    Serial.print(YValue);  
    Serial.print("\tZVALUE=");
    Serial.print(ZValue);  
    Serial.print("\tTEMPERATURE=");
    Serial.println(Temperature);  
 
    delay(100);    
    interruptStatus = 0;
  }
  // give circuit time to settle after wakeup
  delay(20);
}

//

void interruptFunction(){
  /* Function called if Arduino detects interrupt activity
   *when rising edge detected on Arduino interrupt
   */
  interruptStatus=1;
  wakeup();       
}
