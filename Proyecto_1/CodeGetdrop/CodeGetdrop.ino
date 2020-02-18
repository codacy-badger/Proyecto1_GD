#include <Sleep_n0m1.h>
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <SimpleKalmanFilter.h>

Adafruit_BMP085 bmp;
SimpleKalmanFilter pressureKalmanFilter(1, 1, 0.01);

int count = 0;
Sleep sleep;
unsigned long sleepTime; //how long you want the arduino to sleep

void setup()
{
   Serial.begin(9600);
   sleepTime = 8000; //set sleep time in ms, max sleep time is 49.7 days
   for(int i=2; i<=11;i++){
   pinMode(i,0);}
   if(!bmp.begin()){
   Serial.println("BMP180 Sensor not found");
   while(1){}}
}

void loop()
{
  //digitalWrite(12,1);
  //digitalWrite(13,1);
  delay(100); //delay to allow serial output to be ready after wake up
  //Serial.print("Awake for ");
  // Serial.print(count);
  //Serial.println("sec");
  count++;
  delay(400);    
  float estimated_altitude = pressureKalmanFilter.updateEstimate(bmp.readAltitude(101500)-2250);
  //Serial.print(bmp.readAltitude(101500));
  //Serial.print(" - - ");
  //Serial.print('b');
  Serial.println(estimated_altitude);
  //Serial.println(bmp.readAltitude(101500));
  delay(100);
  
  if(count >= 5)
  {
    count = 0;
    //Serial.print("");
    //Serial.println(sleepTime); 
    delay(100); //delay to allow serial to fully print before sleep
    //digitalWrite(12,0);
    //digitalWrite(13,0);
    sleep.pwrDownMode(); //set sleep mode
    sleep.sleepDelay(sleepTime); //sleep for: sleepTime
  }
 
  
}
