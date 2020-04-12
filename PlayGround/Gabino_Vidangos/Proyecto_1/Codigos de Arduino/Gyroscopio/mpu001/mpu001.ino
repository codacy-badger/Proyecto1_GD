#include <MPU6050.h>
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif
int16_t ax, ay, az;
int16_t gx, gy, gz;
const int SERIAL_BAUD_RATE = 9600;
const int SERIAL_PRINT_DELAY = 333;

MPU6050 mpu;

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    Wire.begin();
}

void loop()
{
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    //const float temp = mpu.readTemperature();

    // Print in CSV format.
    #ifdef OUTPUT_READABLE_ACCELGYRO
    Serial.print("a/g:\t");
    Serial.print(ax);
    Serial.print(",");
    Serial.print(ay);
    Serial.print(",");
    Serial.print(az);
    Serial.print(",");
    Serial.print(gx);
    Serial.print(",");
    Serial.print(gy);
    Serial.print(",");
    Serial.print(gz);
    Serial.print(",");
    Serial.print(12);
    Serial.println();
    #endif
   #ifdef OUTPUT_BINARY_ACCELGYRO
        Serial.write((uint8_t)(ax >> 8)); Serial.write((uint8_t)(ax & 0xFF));
        Serial.write((uint8_t)(ay >> 8)); Serial.write((uint8_t)(ay & 0xFF));
        Serial.write((uint8_t)(az >> 8)); Serial.write((uint8_t)(az & 0xFF));
        Serial.write((uint8_t)(gx >> 8)); Serial.write((uint8_t)(gx & 0xFF));
        Serial.write((uint8_t)(gy >> 8)); Serial.write((uint8_t)(gy & 0xFF));
        Serial.write((uint8_t)(gz >> 8)); Serial.write((uint8_t)(gz & 0xFF));
    #endif
}
