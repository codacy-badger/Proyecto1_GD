#include "MPU6050.h"
#include <Wire.h>

const int I2C_ADDRESS = 0x68;

// Registers 59 to 64 - Accelerometer Measurements (Read Only)
const int ACCEL_XOUT_H = 0x3B;
const int ACCEL_XOUT_L = 0x3C;
const int ACCEL_YOUT_H = 0x3D;
const int ACCEL_YOUT_L = 0x3E;
const int ACCEL_ZOUT_H = 0x3F;
const int ACCEL_ZOUT_L = 0x40;
const int ACCEL_OUT_SIZE = 6;

// Registers 65 and 66 - Temperature Measurement (Read Only)
const int TEMP_OUT_H = 0x41;
const int TEMP_OUT_L = 0x42;
const int TEMP_OUT_SIZE = 2;

// Registers 67 to 72 - Gyroscope Measurements (Read Only)
const int GYRO_XOUT_H = 0x43;
const int GYRO_XOUT_L = 0x44;
const int GYRO_YOUT_H = 0x45;
const int GYRO_YOUT_L = 0x46;
const int GYRO_ZOUT_H = 0x47;
const int GYRO_ZOUT_L = 0x48;
const int GYRO_OUT_SIZE = 6;

// Register 107 - Power Management 1 (Read/Write)
const int PWR_MGMT_1 = 0x6B;

// Accelerometer Sensitivity in LSB/g-force
const float ACCEL_SENSITIVITY = 16384.0;

// Gyroscope Sensitivity in LSB/°/s
const float GYRO_SENSITIVITY = 16.4;

// Temperature formula from data sheet ((TEMP / DIV) + ADD)
const double TEMP_FORMULA_DIV = 340.0;
const double TEMP_FORMULA_ADD = 36.53;

MPU6050::MPU6050()
{
    Wire.begin();
}

void MPU6050::WakeUp()
{
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(PWR_MGMT_1);
    Wire.write(0);
    Wire.endTransmission();
}

Vector MPU6050::Acceleration()
{
    Vector accelRaw = AccelerationRaw();

    Vector accel;
    accel.x = accelRaw.x / ACCEL_SENSITIVITY;
    accel.y = accelRaw.y / ACCEL_SENSITIVITY;
    accel.z = accelRaw.z / ACCEL_SENSITIVITY;

    return accel;
}

Vector MPU6050::Gyroscope()
{
    Vector gyroRaw = GyroscopeRaw();

    Vector gyro;
    gyro.x = gyroRaw.x / GYRO_SENSITIVITY;
    gyro.y = gyroRaw.y / GYRO_SENSITIVITY;
    gyro.z = gyroRaw.z / GYRO_SENSITIVITY;

    return gyro;
}

float MPU6050::Temperature()
{
    return (TemperatureRaw() / TEMP_FORMULA_DIV) + TEMP_FORMULA_ADD;
}

Vector MPU6050::AccelerationRaw()
{
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(ACCEL_XOUT_H);
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDRESS, ACCEL_OUT_SIZE);
    const int accelXH = Wire.read();
    const int accelXL = Wire.read();
    const int accelYH = Wire.read();
    const int accelYL = Wire.read();
    const int accelZH = Wire.read();
    const int accelZL = Wire.read();

    Vector accelRaw;
    accelRaw.x = (accelXH << 8) | accelXL;
    accelRaw.y = (accelYH << 8) | accelYL;
    accelRaw.z = (accelZH << 8) | accelZL;
    return accelRaw;
}

Vector MPU6050::GyroscopeRaw()
{
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(GYRO_XOUT_H);
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDRESS, GYRO_OUT_SIZE);
    const int gyroXH = Wire.read();
    const int gyroXL = Wire.read();
    const int gyroYH = Wire.read();
    const int gyroYL = Wire.read();
    const int gyroZH = Wire.read();
    const int gyroZL = Wire.read();

    Vector gyroRaw;
    gyroRaw.x = (gyroXH << 8) | gyroXL;
    gyroRaw.y = (gyroYH << 8) | gyroYL;
    gyroRaw.z = (gyroZH << 8) | gyroZL;
    return gyroRaw;
}

float MPU6050::TemperatureRaw()
{
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(TEMP_OUT_H);
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDRESS, TEMP_OUT_SIZE);
    const int tempH = Wire.read();
    const int tempL = Wire.read();

    const int tempRaw = (tempH << 8) | tempL;
    return tempRaw;
}
