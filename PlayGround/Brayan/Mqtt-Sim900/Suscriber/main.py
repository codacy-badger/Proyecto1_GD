import paho.mqtt.client as mqtt
import time
client = mqtt.Client()
client.connect("54.200.157.213", 1883, 60)
# for i in range (0,10):
with open("noMotion.txt", "r") as file:
    # This is the Publisher
    while True:
        for linea in file.readlines():
            print(linea)
            client.publish("shovel/terminal/data", linea)
            time.sleep(0.2)
# client.disconnect();
