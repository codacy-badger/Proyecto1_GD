/* ---------------------------------------------------------------                   
 *      Programa BMA400: Deteccion de movimiento de pala 
 * --------------------------------------------------------------
 * CONECCIONES:
 *        DEVICE   | MSP430
 *        -----------------
 *          MOSI   |  P1.7     
 *          MISO   |  P1.6
 *          SCLK   |  P1.5
 *          CS     |  P2.0
 *          INT1   |  P1.3 
 *          GND    |  GND
 *          VIO    |  3.3v
 *          VS     |  3.3v 
 * DESCRIPCION:
 * Programa capaz de identificar el movimiento circular que realiza la pala
 * Para que el agoritmo funcione eficientemente deberá tener corregidor de
 * offset y deteccion de cambio de velocidad
 */
#include "BMA400.h"           // Libreria BMA400
#define interruptPin P2_5     //Pin de interrupcion

/*----------------------ACC Sensor Variables-------------------------*/
uint8_t Ascale = AFS_8G, SR = SR_200Hz, power_Mode = normal_Mode, OSR = osr3, acc_filter = acc_filt1;
/*---------------------Variables del programa-----------------------*/
int16_t ax, ay, az;             //Variable de acceleración
int16_t num=50;                      //Cantidad de muestras promedio
const int WAKEUP_PIN = P1_3;    //Pin de Wake up
 //Valores iniciales
int16_t ax_m=0;
int16_t ay_m=0;
int16_t az_m=0;

BMA400 BMA400;

void setup()
{
  Serial.begin(9600);
  BMA400.begin(P2_0);
  Serial.println("BMA400 accelerometer...");
  byte c = BMA400.getChipID();  
  Serial.print("BMA400 "); Serial.print("I AM "); Serial.print(c, HEX);
  Serial.println(" ");
  delay(1000); 

  //Deteccion de coneccion
  if(c == 0x90){
   Serial.println("BMA400 is online..."); Serial.println(" ");
   BMA400.resetBMA400();                                                  
   BMA400.initBMA400(Ascale, SR, normal_Mode, OSR, acc_filter);           
   //BMA400.SetWakeupInterruption(0x08);              
  }
  else {
    if(c != 0x90) Serial.println(" BMA400 not functioning!");
  }
}

void Read_promedio(int i_max){
  ax_m=0;
  ay_m=0;
  az_m=0;
  for(int i = 0; i<i_max; i++){
      BMA400.readBMA400AccelData(ax,ay,az);
      ax_m=ax_m+ax;
      ay_m=ay_m+ay;
      az_m=az_m+az;
    }
  //Promedios cada i_max muestras
  ax_m=ax_m/i_max;
  ay_m=ay_m/i_max;
  az_m=az_m/i_max;
  //Derivada
  d_ax=ax_m-ax_m_ant;
  d_ay=ay_m-ay_m_ant;
  d_az=az_m-az_m_ant;
  
  //Serial.print(ax_m);Serial.print(",");Serial.print(ay_m);Serial.print(",");Serial.println(az_m);  
  //delay(100);
  //Valores anteriores
  
}
void loop() { 
   Read_promedio(num);
}
