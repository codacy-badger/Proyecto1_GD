# Import Libraries for I2c and time data
from machine import I2C
import sys
import time
import xbee
def read_i2c_word(register):
    """Read two i2c registers and combine them solvin the complement problem.
    INPUTS:
    register -- the first register to read from.
    OUTPUTS:
    Returns the combined read results.
    """
    # Data bytes
    data_bytes = bytearray(2)
    # Read the data from the registers
    i2c.readfrom_mem_into(MPU6050_ADDR, register, data_bytes)
    value = (data_bytes[0] << 8) + data_bytes[1]
    if value >= 0x8000:
        return -((65535 - value) + 1)
    else:
        return value
# PROGRAM CONSTANTS
# MPU5060 address
MPU6050_ADDR = 0x68
# Energy configuration register
PWR_MGMT_1 = 0x6B
# Accelerometer's registers
ACCEL_XOUT0 = 0X3B
ACCEL_YOUT0 = 0x3D
ACCEL_ZOUT0 = 0x3F
# Gyroscopes Registers
GYRO_XOUT0 = 0X43
GYRO_YOUT0 = 0x45
GYRO_ZOUT0 = 0x47
# Temperature Registers
TEMP_REG = 0x41
# COMUNICATION PARAMETERS
TARGET_64BIT_ADDR = b'\x00\x13\xA2\x00\x41\xA8\x08\xF1'
print(" +-------------------------------------+")
print(" | XBee MicroPython I2C MPU6050 E2I    |")
print(" +-------------------------------------+\n")
# Start I2C peripherals
i2c = I2C(1)
# Verify iF MPU6050 is connected to I2C wire
if MPU6050_ADDR not in i2c.scan():
    print("¡No se pudo encontrar el sensor!")
    sys.exit(1)
# Put the IMU reset in zero and disables the temperature sensor
# (put bit 7 from PWR_MGMT ==>0)
# (put bit 3 from PWR_MGMT ==>1)
i2c.writeto_mem(MPU6050_ADDR, PWR_MGMT_1, b'\x00')
# Read Node Identifier
Nodename = xbee.atcmd("NI")
# Start to read measurements
while True:
    # Reading data from accelerometer
    acc_X = read_i2c_word(ACCEL_XOUT0)
    acc_Y = read_i2c_word(ACCEL_YOUT0)
    acc_Z = read_i2c_word(ACCEL_ZOUT0)
    # Reading gyroscope
    gyro_X = read_i2c_word(GYRO_XOUT0)
    gyro_Y = read_i2c_word(GYRO_YOUT0)
    gyro_Z = read_i2c_word(GYRO_ZOUT0)
    # Reading temperature
    # MPU-6050 Register Map and Descriptions revision 4.2, page 30
    temp = (read_i2c_word(TEMP_REG) / 340) + 36.53
    Volt = xbee.atcmd("%V") * 0.001
    MESSAGE = Nodename + str(acc_X) + "," + str(acc_Y) + "," + str(acc_Z) + "," + str(gyro_X) + "," + str(gyro_Y) + "," + str(gyro_Z) + "," + str(temp) + "," + str(Volt)
    # MESSAGE = acc_X + + acc_Y + + acc_Z + + gyro_X + + gyro_Y + + gyro_Z + + temp
    try:
        xbee.transmit(TARGET_64BIT_ADDR, MESSAGE)
        print("Sending data to %s >> %s" % (''.join('{:02x}'.format(x).upper() for x in TARGET_64BIT_ADDR), MESSAGE))
    # print("Data sent successfully")
    except Exception as e:
        print("Transmit failure: %s" % str(e))
    time.sleep(10)
