#include "MPU6050.h"

const int SERIAL_BAUD_RATE = 9600;
const int SERIAL_PRINT_DELAY = 333;

MPU6050 mpu;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    mpu.WakeUp();
}

void loop()
{
    const auto accel = mpu.Acceleration();
    const auto gyro = mpu.Gyroscope();
    const float temp = mpu.Temperature();

    // Print in CSV format.
    Serial.print(accel.x);
    Serial.print(",");
    Serial.print(accel.y);
    Serial.print(",");
    Serial.print(accel.z);
    Serial.print(",");
    Serial.print(gyro.x);
    Serial.print(",");
    Serial.print(gyro.y);
    Serial.print(",");
    Serial.print(gyro.z);
    Serial.print(",");
    Serial.print(temp);
    Serial.println();

    delay(SERIAL_PRINT_DELAY);
}
