/*//volatile bool State = false;

const int buttonPin = PUSH2;
const int ledPin = RED_LED;

 const int WAKEUP_PIN = 2.0;

int buttonState = LOW;


void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);                  // Make red LED an output
 pinMode( WAKEUP_PIN , OUTPUT);
 pinMode(buttonPin, INPUT_PULLUP);              // Make push button input
 //attachInterrupt(PUSH2, interrupt, FALLING);// Attach ISR to PUSH1

}

void Read(){
  //buttonState = HIGH;
  buttonState = digitalRead(buttonPin);
  Serial.println("holi");
  delay(500);
  
  }
void sleepNow(){
  sleep(100);
  attachInterrupt(digitalPinToInterrupt(buttonPin), wakeUp,RISING);
  
  }
void wakeUp(){
  wakeup();
  detachInterrupt(digitalPinToInterrupt(buttonPin));
  buttonState = LOW;
  }
  
void loop() {
  digitalWrite(ledPin, 1);
  attachInterrupt(digitalPinToInterrupt(buttonPin),wakeUp,RISING);
  digitalWrite( ledPin, buttonState);
  if (buttonState == LOW){
    digitalWrite(ledPin, 0);
    digitalWrite(WAKEUP_PIN, 0);
    Read();
    
    }
  else{
    sleepNow();
    digitalWrite(ledPin , 1);
    digitalWrite(WAKEUP_PIN, 1);
    }  
}*/



/////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////



#include "SPI.h"
#include "ADXL362.h"

//Definiendo pin de interrupcion (Pin P1_3)
#define interruptPin P1_3          

//Definiendo la clase ADXL362
ADXL362 xl;

//Definiendo variables y banderas del sistema
volatile bool interruptStatus = 0;
int16_t XValue, YValue, ZValue, Temperature;

//volatile bool State = false;

const int buttonPin = PUSH2;
const int ledPin = RED_LED;

 const int WAKEUP_PIN = 2.0; // despierta al xbee

int buttonState = LOW;


void setup() {
 Serial.begin(9600);
 pinMode(ledPin, OUTPUT);                  // Make red LED an output
 pinMode( WAKEUP_PIN , OUTPUT);
 pinMode(buttonPin, INPUT_PULLUP);              // Make push button input
 //attachInterrupt(PUSH2, interrupt, FALLING);// Attach ISR to PUSH1

 xl.begin(P2_0);          //Se realiza el reseteo suave y se asigna el pin cs
 delay(1000);            

    /*  Ajustando umbrales de Actividad e Inactividad
       Ajustar estos valores afectará la "capacidad de respuesta" y el "retraso" de la función de interrupción
       La configuración actual da como resultado un interruptor de encendido y apagado muy rápido, sensible 
       y con un retraso de 2 segundos para dormir cuando se detiene el movimiento. 
    */
    
    xl.setupDCActivityInterrupt(300, 10);   // 300 code activity threshold.  With default ODR = 100Hz, time threshold of 10 results in 0.1 second time threshold
    xl.setupDCInactivityInterrupt(80, 200);    // 80 code inactivity threshold.  With default ODR = 100Hz, time threshold of 30 results in 2 second time threshold
    Serial.println();

    /* Other possible settings
    //  Motion activated On - stays on for 60 seconds 
    xl.setupDCActivityInterrupt(300, 10);   // 300 code activity threshold.  With default ODR = 100Hz, time threshold of 10 results in 0.1 second time threshold
    xl.setupDCInactivityInterrupt(80, 6000);  // 80 code inactivity threshold.  With default ODR = 100Hz, time threshold of 60000 results in 60 second time threshold
    */
  
  
    //
    // Setup ADXL362 for proper autosleep mode
    //
  
    // Map Awake status to Interrupt 1
    // *** create a function to map interrupts... coming soon
    xl.SPIwriteOneRegister(0x2A, 0x40);   
  
    // Setup Activity/Inactivity register
    xl.SPIwriteOneRegister(0x27, 0x3F); // Referenced Activity, Referenced Inactivity, Loop Mode  
        
    // turn on Autosleep bit
    byte POWER_CTL_reg = xl.SPIreadOneRegister(0x2D);
    POWER_CTL_reg = POWER_CTL_reg | (0x04);       // turn on POWER_CTL[2] - Autosleep bit
    xl.SPIwriteOneRegister(0x2D, POWER_CTL_reg);
 


 
    //
    // turn on Measure mode
    //
    xl.beginMeasure();                      // DO LAST! enable measurement mode   
    xl.checkAllControlRegs();               // check some setup conditions    
    delay(100);
 

 
    //
    // Setup interrupt function on Arduino
    //    IMPORTANT - Do this last in the setup, after you have fully configured ADXL.  
    //    You don't want the Arduino to go to sleep before you're done with setup
    //
    pinMode(interruptPin, INPUT);    
    //attachInterrupt(interruptPin, interruptFunction, RISING);  // A high on output of ADXL interrupt means ADXL is awake, and wake up

    
}

void Read(){
  //buttonState = HIGH;
  //buttonState = digitalRead(buttonPin);
  interruptStatus = digitalRead(interruptPin);
  Serial.println("holi");
  delay(500);
  
  }
void sleepNow(){
  sleep(100);
  attachInterrupt(digitalPinToInterrupt(interruptPin), wakeUp,RISING);
  
  }
void wakeUp(){
  wakeup();
  detachInterrupt(digitalPinToInterrupt(interruptPin));
  interruptStatus = LOW;
  }
  
void loop() {
  digitalWrite(ledPin, 1);
  attachInterrupt(digitalPinToInterrupt(interruptPin),wakeUp,RISING);
  digitalWrite( ledPin, interruptPin);
  if (interruptStatus == LOW){
    Serial.print("\nADXL went to sleep - Put Arduino to sleep now \n");
    digitalWrite(ledPin, 0);
    digitalWrite(WAKEUP_PIN, 0);
    Read();
    
    }
  else{
    sleepNow();
    
    delay(10);
    //digitalWrite(7, HIGH);    // Turn on LED as visual indicator of awake
    Serial.println("\nArduino is Awake! \n");
    xl.readXYZTData(XValue, YValue, ZValue, Temperature);  
    Serial.print("XVALUE=");
    Serial.print(XValue);   
    Serial.print("\tYVALUE=");
    Serial.print(YValue);  
    Serial.print("\tZVALUE=");
    Serial.print(ZValue);  
    Serial.print("\tTEMPERATURE=");
    Serial.println(Temperature);   
    delay(100);  
    
    digitalWrite(ledPin , 1);
    digitalWrite(WAKEUP_PIN, 1);
    }  
}
