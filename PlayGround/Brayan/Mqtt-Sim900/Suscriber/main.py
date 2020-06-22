import paho.mqtt.client as mqtt


# This is the Subscriber

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("shovel/terminal/data")
    #client.subscribe("test")


def on_message(client, userdata, msg):
    mensaje = msg.payload.decode()
    if msg.payload.decode() == "Fin":
        print(mensaje)
        client.disconnect()
    else:
        print(mensaje)


client = mqtt.Client()
client.connect("54.200.157.213", 1883, 60)

client.on_connect = on_connect
client.on_message = on_message

client.loop_forever()