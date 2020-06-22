/*****************************************************************/
/****************************** E2I ******************************/
/*****************************************************************/
/******************* Programa de Sensor BMA400 *******************/

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

    DEVICE   | MSP430
 -------------------
   MOSI   |  d11     
   MISO   |  d12
   SCLK   |  d13
   CS     |  d10
   INT1   |  d3
   GND    |  GND
   VIO    |  3.3v
   VS     |  3.3v
 
*/ 

#include <SoftwareSerial.h>
#include <avr/sleep.h>
#include "BMA400.h"
#include "RTClib.h"
#include <SD.h>
/*_____________________________ Fin _____________________________*/

/************************ Pin de Int Sen *************************/
#define interruptPin 3 
//#define WAKEUP_PIN P1_3
/*_____________________________ Fin _____________________________*/

SoftwareSerial mySerial(5,6);

/********************* ACC Sensor Variables **********************/
uint8_t Ascale = AFS_4G, SR = SR_200Hz, power_Mode = normal_Mode, OSR = osr3, acc_filter = acc_filt1;

int Dato;

//uint8_t mssg;
int16_t ax, ay, az;       
const int WAKEUP_PIN = 1;
bool valInterrupt = 0;
BMA400 BMA400;

/*_____________________________ Fin _____________________________*/

/************************ RTC Variables**********************/

RTC_DS1307 rtc;

//char daysOfTheWeek[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
int mes, dia, hora, minuto, segundo;
long anio;
/*_____________________________ Fin _____________________________*/

/************************ SD ***************************/
File myFile;
/*_____________________________ Fin _____________________________*/

/************************* Main Funccion *************************/
void setup()
{
  //pinMode(interruptPin,INPUT_PULLUP);
  Serial.begin(9600);
  mySerial.begin(9600); 

  BMA400.begin(10);
  Serial.println("BMA400 accelerometer...");
  byte c = BMA400.getChipID();  
  Serial.print("BMA400 "); Serial.print("I AM "); Serial.print(c, HEX);
  Serial.println(" ");
  delay(1000); 

  /************************ SD ***************************/
  Serial.print("Iniciando SD ...");
  if (!SD.begin(4)) {
    Serial.println("No se pudo inicializar");
    return;
  }
  Serial.println("inicializacion exitosa");
  
  if(!SD.exists("datalog.csv"))
  {
      myFile = SD.open("datalog.csv", FILE_WRITE);
      if (myFile) {
        Serial.println("Archivo nuevo, Escribiendo encabezado(fila 1)");
        myFile.println("Año,mes,dia,hora,minuto,segundo,x,y,z");
        myFile.close();
      } else {

        Serial.println("Error creando el archivo datalog.csv");
      }
  }
  /*_____________________________ Fin _____________________________*/

  if(c == 0x90){
   Serial.println("BMA400 is online..."); Serial.println(" ");
   BMA400.resetBMA400();                                                  
   BMA400.initBMA400(Ascale, SR, normal_Mode  , OSR, acc_filter);           
   BMA400.SetWakeupInterruption();     
//////   attachInterrupt(interruptPin,interrupt,RISING);               
  }
  else {
  if(c != 0x90) Serial.println(" BMA400 not functioning!");
  }

  if (! rtc.begin()) {
    Serial.println("Nose pudo encontrar el RTC");
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {
    Serial.println("RTC no esta corriendo, actualizar el tiempo!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}
/*_____________________________ Fin _____________________________*/

  
void Parameters(){
  
    //BMA400.resetBMA400();  
  //if(mssg != 0){
    
   //Serial.flush();
   //Serial.println(mssg);
  if(Dato == 10){ 
    //Serial.println("wooooooooooooo");  
    
    Ascale = AFS_2G;
        } else if(Dato == 11){
        Ascale = AFS_4G;
          } else if (Dato == 12){
            Ascale = AFS_8G; 
            } else if (Dato == 13){
              
              Ascale = AFS_16G;
              //Serial.println("wooooooooooooo");
              //Serial.println(Ascale);
              } 

   if(Dato == 20){
    SR = SR_12_5Hz;
    } else if(Dato == 21){
      SR = SR_25Hz;
      } else if(Dato == 22){
      SR = SR_50Hz;
      } else if(Dato == 23){
      SR = SR_100Hz;
      } else if(Dato == 24){
      SR = SR_200Hz;
      } else if(Dato == 25){
      SR = SR_800Hz;
      }

    if(Dato == 30){
      power_Mode = sleep_Mode;
      } else if(Dato == 31){
        power_Mode = lowpower_Mode;
        } else if(Dato == 32){
        power_Mode = normal_Mode;
        }

    if(Dato == 40){
      OSR = osr0;
      } else if(Dato == 41){
      OSR = osr1;
      } else if(Dato == 42){
      OSR = osr2;
      } else if(Dato == 43){
      OSR = osr3;
      } 

    if(Dato == 50){
      acc_filter = acc_filt1;
      } else if(Dato == 51){
      acc_filter = acc_filt2;
      } else if(Dato == 52){
      acc_filter = acc_filt_lp;
      }

  
      
   //Ascale = Ascale;
    
   //Serial.println("*****************");
   Serial.println(Ascale);
   //Serial.println("*****************");
   delay(2000);
   //byte c = BMA400.getChipID();
   //if(c == 0x90){
   //Serial.println("BMA400 is online..."); //Serial.println(" ");
   //BMA400.resetBMA400();                                                  
          
   //BMA400.SetWakeupInterruption();     
   //attachInterrupt(interruptPin,interrupt,RISING);               
  //}
  //else {
  //if(c != 0x90) Serial.println(" BMA400 not functioning!");
  //}
  
  }

/************************* Main Funccion *************************/
void Read(){
  BMA400.readBMA400AccelData(ax,ay,az);
  digitalWrite(WAKEUP_PIN ,LOW);
  //tiempo();
  Serial.print("a"); Serial.print(ax);Serial.print(",");Serial.print(ay);Serial.print(",");Serial.println(az);   
  SD_card();
  }
/*_____________________________ Fin _____________________________*/

/************************* Main Funccion *************************/

/************************ Main Funccion **************************/

void tiempo(){
    DateTime now = rtc.now();
    anio = now.year();
    mes = now.month();
    dia = now.day();
    hora = now.hour();
    minuto = now.minute();
    segundo = now.second();
    
    Serial.print(anio, DEC);
    Serial.print('/');
    Serial.print(mes, DEC);
    Serial.print('/');
    Serial.print(dia, DEC);
    Serial.print("  ");
    //Serial.print(" (");
    //Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    //Serial.print(") ");
    Serial.print(hora, DEC);
    Serial.print(':');
    Serial.print(minuto, DEC);
    Serial.print(':');
    Serial.print(segundo, DEC);
    Serial.print(" ");
    //delay(500); 
  }
/*_____________________________ Fin _____________________________*/


/************************ SD ***************************/
void SD_card(){
  DateTime now = rtc.now();
  hora = now.hour();
myFile = SD.open("datalog.csv", FILE_WRITE);//abrimos  el archivo
  
  if (myFile) { 
        Serial.println("Escribiendo SD ");
//        int sensor1 = analogRead(0);
//        int sensor2 = analogRead(1);
//        int sensor3 = analogRead(2);
        myFile.print(anio);
        myFile.print(",");
        myFile.print(mes);
        myFile.print(",");
        myFile.print(dia);
        myFile.print(",");
        myFile.print(hora);
        myFile.print(",");
        myFile.print(minuto);
        myFile.print(",");
        myFile.print(segundo);
        myFile.print(",");
        myFile.print(ax);
        myFile.print(",");
        myFile.print(ay);
        myFile.print(",");
        myFile.println(az);
        
        myFile.close(); //cerramos el archivo
        
//        Serial.print("Tiempo(ms)=");
//        Serial.print(millis());
//        Serial.print(",sensor1=");
//        Serial.print(sensor1);
//        Serial.print(",sensor2=");
//        Serial.print(sensor2);
//        Serial.print(",sensor3=");
//        Serial.println(sensor3);       
                    
  
  } else {
    // if the file didn't open, print an error:
    Serial.println("Error al abrir el archivo");
  }
  delay(100);
}
/*_____________________________ Fin _____________________________*/

/************************** Main Loop ****************************/
void loop() { 
  tiempo();
  Read();
  //valInterrupt = digitalRead(interruptPin);

  while(Serial.available()){
    int com = (int)Serial.read();
    
    if (com == 1 or com == '1'){
      Serial.println(com);
      mySerial.println(10);
    }

    if (com == 2 or com == '2'){
      Serial.println(com);
      mySerial.println(13);
    }
  }
  
  while(mySerial.available()){
    int com = (int)Serial.read();
    //Serial.println("Recibido");
    if(com )
    Serial.write(mySerial.read());
    
    
//    myFile = SD.open("datalog.csv", FILE_WRITE);//abrimos  el archivo
//      if (myFile) { 
//        Serial.print("Escribiendo SD: ");
//        myFile.print(mySerial.read());
//        
//        myFile.close(); //cerramos el archivo
//        
////        Serial.print("Tiempo(ms)=");
////        Serial.print(millis());
////        Serial.print(",sensor1=");
////        Serial.print(sensor1);
////        Serial.print(",sensor2=");
////        Serial.print(sensor2);
////        Serial.print(",sensor3=");
////        Serial.println(sensor3);       
//                    
//  
//  } else {
//    // if the file didn't open, print an error:
//    Serial.println("Error al abrir el archivo");
//  }
//  delay(100);
  }
    
}
/*_____________________________ Fin _____________________________*/
