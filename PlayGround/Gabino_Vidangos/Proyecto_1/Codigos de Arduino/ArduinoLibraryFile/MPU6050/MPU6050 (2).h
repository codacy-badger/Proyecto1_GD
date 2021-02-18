#ifndef MPU6050_H
#define MPU6050_H

struct Vector
{
    float x;
    float y;
    float z;
};

class MPU6050
{
public:
    MPU6050();
    ~MPU6050() = default;

    void WakeUp();

    Vector Acceleration();
    Vector Gyroscope();
    float Temperature();

private:
    Vector AccelerationRaw();
    Vector GyroscopeRaw();
    float TemperatureRaw();
};

#endif
