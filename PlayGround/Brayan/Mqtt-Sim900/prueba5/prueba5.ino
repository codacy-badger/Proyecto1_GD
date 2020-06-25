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
 * ClientID: terminal
 * User:get-test (Noavaiable)
 * Pasword:get_test (Noavaiable)
 * Port: 1883
 *************************************************************    
 * Conecction Parameters
 * 
 */

// Select modem (Tiny GSM)
  #define TINY_GSM_MODEM_SIM900
// Set serial for debug console (to the Serial Monitor, default speed 9600)
  #define SerialMon Serial
  #define SerialAT Serial3
  #define SerialMSP Serial2
//Include BMA400 library
  //#include "BMA400.h"
//BMA400 configuration
  //uint8_t Ascale = AFS_2G, SR = SR_200Hz, power_Mode = normal_Mode, OSR = osr3, acc_filter = acc_filt1;
  int16_t ax, ay, az;       // variables to hold latest sensor data values 
  //BMA400 BMA400;
// Define the serial console for debug prints
  #define TINY_GSM_DEBUG SerialMon
// Define how to connect to the internet
  #define TINY_GSM_USE_GPRS true
  #define TINY_GSM_USE_WIFI false
// set GSM PIN, if any
  #define GSM_reset 9
  #define GSM_PIN ""
// Your GPRS credentials (for claro Perú)
  const char apn[] = "claro.pe";
  const char gprsUser[] = "claro";
  const char gprsPass[] = "claro";
// MQTT Server Details
  const char* broker = "54.200.157.213";
  const char* clientID = "terminal"; 
  const char* topicConf = "shovel/terminal/mensaje";
  const char* topicInit = "shovel/terminal/status";
  const char* topicDatatable = "shovel/terminal/data";
//Include TinyGsmClient to initiate TCP on SIM900
//Include PubSubClient to initiate Mqtt conection
  #include <TinyGsmClient.h>
  #include <PubSubClient.h>
//Create a modem instance
  TinyGsm modem(SerialAT);  
//Create simple conection    
  TinyGsmClient client(modem);
//Create MQTT client
  PubSubClient mqtt(client);    
//Vaiable to store lastconection attempt
  uint32_t lastReconnectAttempt = 0;
  
/**************************************************************************************************
**                                       MQTT Callback fun                                       **
**                               To response each configuration development                      **
***************************************************************************************************/
  void mqttCallback(char* topic, byte* payload, unsigned int len) {
    char p[len+1];
    memcpy(p,payload,len);
    p[len]=NULL;
    String message(p);
    SerialMon.print("Message arrived [");
    SerialMon.print(topic);
    SerialMon.print("]: ");
    //SerialMon.write(payload, len);
    int data=message.toInt();
    SerialMon.println(message);
  //Only proceed if incoming message's topic matches
    if (String(topic) == topicConf) {
      mqtt.publish(topicDatatable, "OK");
      Serial2.println(data);
     }
  }
  
/**************************************************************************************************
**                                            MQTT CONECCT                                       **
**                                    Makes the conecction to the server                         **
***************************************************************************************************/
  int8_t mqttConnect() {
    int8_t State;
    SerialMon.print("Connecting to ");
    SerialMon.print(broker);
    // Connect to MQTT Broker
    boolean status = mqtt.connect(clientID);
    // Or, if you want to authenticate MQTT:
    //boolean status = mqtt.connect(" Brayan", "get-test", "get-test");
    if (status == false) {
      State=mqtt.state();
      SerialMon.println(" fail");
      SerialMon.println(State);
      return State;
    }
    SerialMon.println(" OK");
    mqtt.publish(topicInit, "Conected");
    mqtt.subscribe(topicConf);
    return mqtt.connected()*6;
  }
/**********************************************************************************************************
 **                                               TCPINITFUN                                             **
 **                                     Do the TCP conection using SIM900                                ** 
 **********************************************************************************************************/
 boolean tcpinitfun(){
  //turn on GSM SIM900
    digitalWrite(GSM_reset,HIGH);
    delay(2000);
  //Display initialization
    SerialMon.println("Initializing...");
  //Restart modem to ensures don't have lingering connections
    modem.restart();                
  //Get de modem info
    String modemInfo = modem.getModemInfo();
    SerialMon.print("Modem Info: ");
    SerialMon.println(modemInfo);
  //Only will be compiled if GSM need Pin
  #if TINY_GSM_USE_GPRS
    // Unlock your SIM card with a PIN if needed
    if ( GSM_PIN && modem.getSimStatus() != 3 ) {
      modem.simUnlock(GSM_PIN);
    }
  #endif
  SerialMon.print("Waiting for network...");
  if (!modem.waitForNetwork()) {
    SerialMon.println(" fail");
    delay(5000);
    return;
  }
  SerialMon.println(" ok");
  if (modem.isNetworkConnected()) {
    SerialMon.println("Network connected");
  }

#if TINY_GSM_USE_GPRS
  // GPRS connection parameters are usually set after network registration
    SerialMon.print(F("Connecting to "));
    SerialMon.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
      SerialMon.println(" fail");
      delay(10000);
      return;
    }
    SerialMon.println(" ok");

  if (modem.isGprsConnected()) {
    SerialMon.println("GPRS connected");
  }
#endif
    digitalWrite(GSM_reset,LOW);
  }
 //boolean BMA400initseq(){
  //BMA400.begin(10);
  //byte c = BMA400.getChipID();  // Read CHIP_ID register for BMA400
  //pinMode(LED_PIN, OUTPUT);
  //if(c == 0x90){
   //SerialMon.println("BMA400 is online..."); SerialMon.println(" ");
  // BMA400.resetBMA400();                                                // software reset before initialization
  // BMA400.initBMA400(Ascale, SR, normal_Mode, OSR, acc_filter);          // Initialize sensor in desired mode for application 
  //}
  //else 
  //{
  //if(c != 0x90) SerialMon.println("BMA400 not functioning!");
  //}
  //}
/***********************************************************************************************************
**                                               GETMSPDATA                                               **
**                                    Read Serial MSP data from UART port                                 **
************************************************************************************************************/
void GetMSPdata(int16_t &Xdata,int16_t &Ydata,int16_t &Zdata){
  /* Data format "Daccx,accy,accz"
     Example: "D36,2,500"*/
  //Number of max characters in each parameter   
  char n[5];    
  while(Serial2.available()){
    int com = (int)Serial.read();
    if(com)
    while (Serial2.read() != 'D');
    n[Serial2.readBytesUntil(',', n,sizeof(n)-1)]=0;
    Xdata=atoi(n);
    n[Serial2.readBytesUntil(',', n,sizeof(n)-1)]=0;
    Ydata=atoi(n);
    n[Serial2.readBytesUntil('\r', n,sizeof(n)-1)]=0;
    Zdata=atoi(n);
  }
}


/***********************************************************************************************************
**                                               MAIN PROGRAM                                             **
************************************************************************************************************/
void setup() {
  // Set console baud rate
  SerialMon.begin(9600);
  delay(10);
  //define serial reset for SIM900
  pinMode(GSM_reset, OUTPUT);   
  //Initialize Serial conexion
  SerialAT.begin(9600);
  SerialMSP.begin(9600);            
  delay(6000);
  //Initialize TCP conection
  tcpinitfun();
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
      if (mqttConnect()==6) {
        lastReconnectAttempt = 0;
      }
      else if(mqttConnect()==-2){
        tcpinitfun();
      }
    }
    return;
  }
else{
  GetMSPdata(ax,ay,az);
  // Serial.print(ax);
  //  Serial.print(",");
  //  Serial.print(ay);
  //  Serial.print(",");
  //  Serial.println(az);
  char* message ="";
  //char* formato="{'ax': %d, 'ay': %d, 'az': %d}";
  char* formato="%d,%d,%d";
  sprintf(message, formato, ax,ay,az);
  mqtt.publish("shovel/terminal/data",message);
  //delay(100);
  }
  mqtt.loop();
}
