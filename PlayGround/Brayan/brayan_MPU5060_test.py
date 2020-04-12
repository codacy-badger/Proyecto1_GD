# Importar Librerias para datos I2c y tiempo
from machine import I2C
import sys
import time
# CONSTANTES DEL PROGRAMA
MPU6050_ADDR = 0x68     #Direcion del MPU5060
PWR_MGMT_1 = 0x6B       #Registro de configuracion de energia
#Registros Acelerometros
ACCEL_XOUT0 = 0X3B
ACCEL_YOUT0 = 0x3D
ACCEL_ZOUT0 = 0x3F
#Registros Giroscopio
GYRO_XOUT0 = 0X43
GYRO_YOUT0 = 0x45
GYRO_ZOUT0 = 0x47
print(" +-------------------------------------+")
print(" | XBee MicroPython I2C MPU6050 E2I    |")
print(" +-------------------------------------+\n")
# Iniciar el periferico I2C
i2c = I2C(1)
# Verificar que el sensor está conectado con la interfaz I2C
if MPU6050_ADDR not in i2c.scan():
    print("¡No se pudo conectar el sensor!")
    sys.exit(1)
# Seteamos el reset del MPU en cero y deshabilitamos el sensor de temperatura
# (bit 7 del registro PWR_MGMT ==>0)
# (bit 3 del registro PWR_MGMT ==>1)
i2c.writeto_mem(MPU6050_ADDR, PWR_MGMT_1, b'\x08')
# Empezar a leer las mediciones:
while True:
    # Bits de datos
    ACCX_bytes = bytearray(2)
    ACCY_bytes = bytearray(2)
    ACCZ_bytes = bytearray(2)
    GYRX_bytes = bytearray(2)
    GYRY_bytes = bytearray(2)
    GYRZ_bytes = bytearray(2)
    # Leyendo datos
    i2c.readfrom_mem_into(MPU6050_ADDR, ACCEL_XOUT0,   ACCX_bytes)
    acc_X = int.from_bytes(ACCX_bytes, "big")
    i2c.readfrom_mem_into(MPU6050_ADDR, ACCEL_YOUT0, ACCY_bytes)
    acc_Y = int.from_bytes(ACCY_bytes, "big")
    i2c.readfrom_mem_into(MPU6050_ADDR, ACCEL_XOUT0, ACCZ_bytes)
    acc_Z = int.from_bytes(ACCZ_bytes, "big")
    i2c.readfrom_mem_into(MPU6050_ADDR, ACCEL_XOUT0, GYRX_bytes)
    gyro_X = int.from_bytes(GYRX_bytes, "big")
    i2c.readfrom_mem_into(MPU6050_ADDR, ACCEL_XOUT0, GYRY_bytes)
    gyro_Y = int.from_bytes(GYRY_bytes, "big")
    i2c.readfrom_mem_into(MPU6050_ADDR, ACCEL_XOUT0, GYRZ_bytes)
    gyro_Z = int.from_bytes(GYRZ_bytes, "big")
    time.sleep(0.0001)
    # Print results:
    print("- Accel x: %s " % acc_X)
    print("- Accel y: %s " % acc_Y)
    print("- Accel z: %s " % acc_Z)
    print("- Gyro x: %s " % gyro_X)
    print("- Gyro y: %s " % gyro_Y)
    print("- Gyro z: %s " % gyro_Z)
    print("")
    time.sleep(5)
