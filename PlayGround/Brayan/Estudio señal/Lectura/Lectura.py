import serial
import time
with open("noMotionJ.txt", "w") as file:
    with serial.Serial('COM18', baudrate=9600, timeout=1.0) as MSP:
        while True:
            comand=input("Enter R to record...\n")
            if "R" == comand:
                print("Press S to Stop")
                time.sleep(0.5)
            while "R"==comand:
                print("Grabando...")
                data: bytes = MSP.readline().decode("utf-8")
                #print(data)
                file.write(data)
    #file.close()
    #print(data.decode("utf-8"))
 #   print(type(data))
