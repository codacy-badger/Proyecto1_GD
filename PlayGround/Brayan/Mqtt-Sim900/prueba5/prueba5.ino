/**************************************************************
 *
 * For this example, you need to install PubSubClient library:
 *   https://github.com/knolleary/pubsubclient
 * TinyGSM Getting Started guide:
 *   https://tiny.cc/tinygsm-readme
 *************************************************************
 * EXAMPLE: SENDING BMA400 data to 54.200.157.213 Server 
 *************************************************************
 * HIVEMQ DATA:
 * Broker: 54.200.157.213
 * User:get-test
 * Pasword:get_test
 * Port: 1883
 * Serverlink:
 *    http://www.mqtt-dashboard.com/index.html
 *    http://www.hivemq.com/demos/websocket-client/?
 *************************************************************    
 * Conecction Parameters
 * 
 */

// Select your modem (Tiny GSM)
 #define TINY_GSM_MODEM_SIM900
// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set Software Serial on Uno, Nano
#include <SoftwareSerial.h>
//Include BMA400 library
#include "BMA400.h"

//BMA400 configuration
uint8_t Ascale = AFS_2G, SR = SR_200Hz, power_Mode = normal_Mode, OSR = osr3, acc_filter = acc_filt1;
int16_t ax, ay, az;       // variables to hold latest sensor data values 
BMA400 BMA400;

SoftwareSerial SerialAT(8, 9); // RX, TX
// Define the serial console for debug prints
#define TINY_GSM_DEBUG SerialMon

// Define how you're planning to connect to the internet
#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false

// set GSM PIN, if any
//#define GSM_PIN "3"

// Your GPRS credentials, if any
const char apn[] = "claro.pe";
const char gprsUser[] = "claro";
const char gprsPass[] = "claro";

// MQTT Server Details
const char* broker = "54.200.157.213";
const char* topicLed = "Brayan/led";
const char* topicInit = "test";
const char* topicLedStatus = "Brayan/ledStatus";

//Include TinyGsmClient to initiate TCP on SIM900
//Include PubSubClient to initiate Mqtt conection
#include <TinyGsmClient.h>
#include <PubSubClient.h>

TinyGsm modem(SerialAT);      //Create a modem instance
TinyGsmClient client(modem);  //Create a simple conection
PubSubClient mqtt(client);    //Create a MQTT client

uint32_t lastReconnectAttempt = 0;

void mqttCallback(char* topic, byte* payload, unsigned int len) {
  SerialMon.print("Message arrived [");
  SerialMon.print(topic);
  SerialMon.print("]: ");
  SerialMon.write(payload, len);
  SerialMon.println();

  // Only proceed if incoming message's topic matches
  if (String(topic) == topicLed) {
    mqtt.publish(topicLedStatus, ledStatus ? "{1}" : "0");
  }
}

boolean mqttConnect() {
  SerialMon.print("Connecting to ");
  SerialMon.print(broker);

  // Connect to MQTT Broker
  //boolean status = mqtt.connect("Brayan");

  // Or, if you want to authenticate MQTT:
  boolean status = mqtt.connect(" Brayan", "get-test", "get-test");

  if (status == false) {
    SerialMon.println(" fail");
    SerialMon.println(mqtt.state());
    return false;
  }
  SerialMon.println(" success");
  mqtt.publish(topicInit, "Hola a todos");
  mqtt.subscribe(topicLed);
  return mqtt.connected();
}

void setup() {
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);
  BMA400.begin(10);
  byte c = BMA400.getChipID();  // Read CHIP_ID register for BMA400
  //pinMode(LED_PIN, OUTPUT);
  if(c == 0x90){
   SerialMon.println("BMA400 is online..."); SerialMon.println(" ");
   BMA400.resetBMA400();                                                // software reset before initialization
   BMA400.initBMA400(Ascale, SR, normal_Mode, OSR, acc_filter);          // Initialize sensor in desired mode for application 
  }
  else 
  {
  if(c != 0x90) SerialMon.println("BMA400 not functioning!");
  }
  
  // !!!!!!!!!!!
  // Set your reset, enable, power pins here
  // !!!!!!!!!!!
  
  SerialMon.println("Wait...");
  SerialAT.begin(9600);            //Initialize Serial conexion
  delay(6000);
  SerialMon.println("Initializing modem...");
  //Restart modem to ensures don't have lingering connections
  modem.restart();                
  //Get de modem info
  String modemInfo = modem.getModemInfo();
  SerialMon.print("Modem Info: ");
  SerialMon.println(modemInfo);

#if TINY_GSM_USE_GPRS
  // Unlock your SIM card with a PIN if needed
  if ( GSM_PIN && modem.getSimStatus() != 3 ) {
    modem.simUnlock(GSM_PIN);
  }
#endif

#if TINY_GSM_USE_GPRS && defined TINY_GSM_MODEM_XBEE
  // The XBee must run the gprsConnect function BEFORE waiting for network!
  modem.gprsConnect(apn, gprsUser, gprsPass);
#endif

  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }
  SerialMon.println(" success");

  if (modem.isNetworkConnected()) {
    SerialMon.println("Network connected");
  }

#if TINY_GSM_USE_GPRS
  // GPRS connection parameters are usually set after network registration
    SerialMon.print(F("Connecting to "));
    SerialMon.print(apn);
    while (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      SerialMon.println(" fail");
      delay(10000);
      return;
    }
    SerialMon.println(" success");

  if (modem.isGprsConnected()) {
    SerialMon.println("GPRS connected");
  }
#endif

 // Set server details
  mqtt.setServer(broker, 1883);
 // Initializa Callback function
  mqtt.setCallback(mqttCallback);
  
}

void loop() {
  if (!mqtt.connected()) {
    SerialMon.println("=== MQTT NOT CONNECTED ===");
    // Reconnect every 10 seconds
    uint32_t t = millis();
    if (t - lastReconnectAttempt > 10000L) {
      lastReconnectAttempt = t;
      if (mqttConnect()) {
        lastReconnectAttempt = 0;
      }
    }
    delay(100);
    return;
  }
else{
    BMA400.readBMA400AccelData(ax,ay,az);
    char* message ="";
    char* formato="{'ax': %d, 'ay': %d, 'az': %d}";
    sprintf(message, formato, ax,ay,az);
    mqtt.publish("shovel/terminal/data",message);
  }
  mqtt.loop();
}
