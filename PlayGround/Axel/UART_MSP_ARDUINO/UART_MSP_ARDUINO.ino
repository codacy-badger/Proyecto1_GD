///*****************************************************************/
///****************************** E2I ******************************/
///*****************************************************************/
///******************* Programa de Sensor BMA400 *******************/
//
///*
//ADXL362_MotionActivatedSleep para el ADXL362 - Micropower 3-axis accelerometer
//Conecciones:
// CONECCIONES:
//
// DEVICE   | MSP430
// -------------------
//   MOSI   |  P1.7     
//   MISO   |  P1.6
//   SCLK   |  P1.5
//   CS     |  P2.0
//   INT1   |  P1.3
//   GND    |  GND
//   VIO    |  3.3v
//   VS     |  3.3v
// 
//*/ 
//
//#include <SoftwareSerial.h>
//#include "BMA400.h"



///*_____________________________ Fin _____________________________*/
//
///************************ Pin de Int Sen *************************/
//#define interruptPin P2_5 
////#define WAKEUP_PIN P1_3
///*_____________________________ Fin _____________________________*/
//
//SoftwareSerial mySerial(P2_4, P2_3); // RX, TX
//
///********************* ACC Sensor Variables **********************/
//uint8_t Ascale = AFS_4G, SR = SR_200Hz, power_Mode = normal_Mode, OSR = osr3, acc_filter = acc_filt1;
//
//long mssg;
//long mssg2;
//String Dato[10];
//String valorCadena = "";
//
////uint8_t mssg;
//int16_t ax, ay, az;       
//const int WAKEUP_PIN = P2_1;
//bool valInterrupt = 0;
//BMA400 BMA400;
///*_____________________________ Fin _____________________________*/
//
///************************* Main Funccion *************************/
//void setup()
//{
//  Serial.begin(9600);
//  BMA400.begin(P2_0);
//  Serial.println("BMA400 accelerometer...");
//  byte c = BMA400.getChipID();  
//  Serial.print("BMA400 "); Serial.print("I AM "); Serial.print(c, HEX);
//  Serial.println(" ");
//  delay(1000); 
//  /*__________________________________________________________*/
//  mySerial.begin(9600);
//  delay(200);
//  /*__________________________________________________________*/
//
//  if(c == 0x90){
//   Serial.println("BMA400 is online..."); Serial.println(" ");
//   BMA400.resetBMA400();                                                  
//   BMA400.initBMA400(Ascale, SR, normal_Mode  , OSR, acc_filter);           
//   BMA400.SetWakeupInterruption();     
//   //attachInterrupt(interruptPin,interrupt,RISING);               
//  }
//  else {
//  if(c != 0x90) Serial.println(" BMA400 not functioning!");
//  }
//}
///*_____________________________ Fin _____________________________*/
//
//void Reception_Data(){
//  //Serial.println(mssg);
////  if(mssg > 500){
////    mssg2 = mssg;
////  }
//  valorCadena = String(mssg);
//
//  int large_valorCadena = valorCadena.length();
//
// // if (large_valorCadena > 6){
//    
//    for(int i = 0; i <= large_valorCadena; i++){
//      for(int j = 0; j <= large_valorCadena; j++){
//        if(j == i + 2){
//          if(j % 2 == 0){
//            Dato[i] = valorCadena.substring(i,j);
//            //Serial.println(Dato[i]);
//            mySerial.println(Dato[i]);
//            //Serial.print("wii");
//            //Serial.println(large_valorCadena);
//            
//            //delay(4000);
//            }
//          }
//        }
//      }
////  }
////  if (large_valorCadena == 1){
////    Serial.print("Parametros: ");
////    Serial.println(mssg2);
//
//
////    mySerial.print("Parametros: ");
////    mySerial.println(mssg2);
////    }
//  }
//  
//void Parameters(){
//  
//    //BMA400.resetBMA400();  
//  //if(mssg != 0){
//    
//   //Serial.flush();
//   //Serial.println(mssg);
//   if(Dato[0].toInt() == 10){    
//    Ascale = AFS_2G;
//    } else if(Dato[0].toInt() == 11){
//    Ascale = AFS_4G;
//      } else if (Dato[0].toInt() == 12){
//        Ascale = AFS_8G; 
//        } else if (Dato[0].toInt() == 13){
//          Ascale = AFS_16G;
//          //} 
//  }
//
//   if(Dato[2].toInt() == 20){
//    SR = SR_12_5Hz;
//    } else if(Dato[2].toInt() == 21){
//      SR = SR_25Hz;
//      } else if(Dato[2].toInt() == 22){
//      SR = SR_50Hz;
//      } else if(Dato[2].toInt() == 23){
//      SR = SR_100Hz;
//      } else if(Dato[2].toInt() == 24){
//      SR = SR_200Hz;
//      } else if(Dato[2].toInt() == 25){
//      SR = SR_800Hz;
//      }
//
//    if(Dato[4].toInt() == 30){
//      power_Mode = sleep_Mode;
//      } else if(Dato[4].toInt() == 31){
//        power_Mode = lowpower_Mode;
//        } else if(Dato[4].toInt() == 32){
//        power_Mode = normal_Mode;
//        }
//
//    if(Dato[6].toInt() == 40){
//      OSR = osr0;
//      } else if(Dato[6].toInt() == 41){
//      OSR = osr1;
//      } else if(Dato[6].toInt() == 42){
//      OSR = osr2;
//      } else if(Dato[6].toInt() == 43){
//      OSR = osr3;
//      } 
//
//    if(Dato[8].toInt() == 50){
//      acc_filter = acc_filt1;
//      } else if(Dato[8].toInt() == 51){
//      acc_filter = acc_filt2;
//      } else if(Dato[8].toInt() == 52){
//      acc_filter = acc_filt_lp;
//      }
//
//  
//      
//   //Ascale = Ascale;
//    
//   //Serial.println("*****************");
//   //mySerial.println(Ascale);
//   //Serial.println("*****************");
//   delay(2000);
//   //byte c = BMA400.getChipID();
//   //if(c == 0x90){
//   //Serial.println("BMA400 is online..."); //Serial.println(" ");
//   //BMA400.resetBMA400();                                                  
//          
//   //BMA400.SetWakeupInterruption();     
//   //attachInterrupt(interruptPin,interrupt,RISING);               
//  //}
//  //else {
//  //if(c != 0x90) Serial.println(" BMA400 not functioning!");
//  //}
//  
//  }
//
///************************* Main Funccion *************************/
//void Read(){
//  BMA400.readBMA400AccelData(ax,ay,az);
//  digitalWrite(WAKEUP_PIN ,LOW);
//  //Serial.print("a"); Serial.print(ax);Serial.print(",");Serial.print(ay);Serial.print(",");Serial.println(az);   
//  Serial.print(ax,DEC);   mySerial.print(ax,DEC);
//  Serial.print(",");      mySerial.print(",");
//  Serial.print(ay,DEC);   mySerial.print(ay,DEC);
//  Serial.print(",");      mySerial.print(",");
//  Serial.println(az,DEC); mySerial.println(az,DEC);
//  }
///*_____________________________ Fin _____________________________*/
//
///************************* Main Funccion *************************/
//void sleepNow(){
//  Serial.print("\nBMA400 went to sleep - Put MSP to sleep now \n");
//  suspend();
//  }
///*_____________________________ Fin _____________________________*/
//
///************************ Main Funccion **************************/
//void interrupt(){
//  wakeup();
//  }
///*_____________________________ Fin _____________________________*/
//
///************************** Main Loop ****************************/
//void loop() { 
//
//
//  
//
//  valInterrupt = digitalRead(interruptPin);
//  //if(valInterrupt == 1){
//        
//      if (mySerial.available() > 0){
//          //mssg = mySerial.parseInt();
//          
//          mssg = mySerial.read();
//          mySerial.write(mssg);
//          Serial.println(mssg);
//          //sleep(100);
//          //Reception_Data();
//          //Parameters();
//          //BMA400.initBMA400(Ascale, SR, normal_Mode, OSR, acc_filter);
//          //BMA400.SetWakeupInterruption();     
//        }
//    //interrupt();
//    //digitalWrite(WAKEUP_PIN ,LOW);
//    
//    //Read();
//    //} 
////  else{
////    digitalWrite(WAKEUP_PIN, HIGH);
////    //sleepNow();
////    //Read();
////      }
//
//   //Read();
//}
/*_____________________________ Fin _____________________________*/


#include <SoftwareSerial.h>
#include "BMA400.h"

#define interruptPin P2_5
#define WAKEUP_PIN P2_1

SoftwareSerial mySerial(P2_4, P2_3); // RX, TX

uint8_t Ascale = AFS_2G, SR = SR_200Hz, power_Mode = normal_Mode, OSR = osr3, acc_filter = acc_filt1;
uint8_t thr = 0x08;//threshold , para el umbral
uint8_t n_samples = 0x03;

int Dato;

int16_t ax, ay, az;       
//const int WAKEUP_PIN = P2_1;
//bool valInterrupt = 0;
BMA400 BMA400;
 
void setup(){
  Serial.begin(9600);
  delay(10);
  mySerial.begin(9600);
  delay(10);
  
  BMA400.begin(P2_0);
  Serial.println("BMA400 accelerometer...");
  byte c = BMA400.getChipID();  
  Serial.print("BMA400 "); Serial.print("I AM "); Serial.print(c, HEX);
  Serial.println(" ");
  delay(1000); 
  /*__________________________________________________________*/
  mySerial.begin(9600);
  delay(200);
  /*__________________________________________________________*/

  if(c == 0x90){
   Serial.println("BMA400 is online..."); Serial.println(" ");
   BMA400.resetBMA400();                                                  
   BMA400.initBMA400(Ascale, SR, normal_Mode  , OSR, acc_filter);           
   BMA400.SetWakeupInterruption(thr,n_samples);     
   //attachInterrupt(interruptPin,interrupt,RISING);               
  }
  else {
    if(c != 0x90) Serial.println(" BMA400 not functioning!");
  }
 }

void Read(){
  BMA400.readBMA400AccelData(ax,ay,az);
  digitalWrite(WAKEUP_PIN ,LOW);
  //Serial.print("a"); Serial.print(ax);Serial.print(",");Serial.print(ay);Serial.print(",");Serial.println(az);   
  Serial.print(ax,DEC);   mySerial.print(ax,DEC); //mySerial.print("aaaaa");
  Serial.print(",");      mySerial.print(","); 
  Serial.print(ay,DEC);   mySerial.print(ay,DEC); //mySerial.print("bbbbb");
  Serial.print(",");      mySerial.print(",");
  Serial.println(az,DEC); mySerial.println(az,DEC); 
  }

void Parameters(){
  
    //BMA400.resetBMA400();  
  //if(mssg != 0){
      
   //Serial.flush();
   //Serial.println(mssg);
   //Serial.println("wooooooooooooo");
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

      //BMA400.initBMA400(Ascale, SR, normal_Mode, OSR, acc_filter);

     if(Dato >= 6000 and Dato < 7000){
             //thr = Dato - 0x258 ;
        thr = Dato - 0x1770;
      }
      
     if(Dato >= 7000 and Dato < 8000){
        n_samples = Dato - 0x1B58;
      }
  
  }


void loop(){
  //Serial.println(thr);
  //Serial.println(n_samples);
   
  if(mySerial.available() > 0){
    //mySerial.println("");

    Dato = mySerial.parseInt();
    //Serial.println("Recibido");
    Serial.println(Dato);

   if(Dato > 0 ){ 
      Parameters();
      BMA400.initBMA400(Ascale, SR, normal_Mode, OSR, acc_filter);
      BMA400.SetWakeupInterruption(thr,n_samples);
      }
   }
   
  Read();
  delay(100);
  
  }
