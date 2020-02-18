
#include <MPU6050_tockn.h>
#include <Wire.h>

MPU6050 mpu6050(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu6050.begin();
  //mpu6050.calcGyroOffsets(true);
}

void loop() {
  mpu6050.update();
  float x = mpu6050.getAngleX();
  float y = mpu6050.getAngleY();
  float z = mpu6050.getAngleZ();
  float t = mpu6050.getTemp();
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.print(z);
  Serial.print(",");
  Serial.println(t);    
  delay(150);
}
