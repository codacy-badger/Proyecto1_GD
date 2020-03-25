#define LED RED_LED
char com;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  Serial.setTimeout(0);
  Serial.print("Sensor A");
  Serial.print("a");delay(100);
  Serial.print("a");delay(100);
  Serial.print("a");delay(100);
}

void loop() {
  //Serial.println("a");delay(100);
  while(Serial.available()>0) {
    com = Serial.read();
    switch (com) {
      case 'i':
        Serial.println("Caido"); break;
      case 's':
        sleepuC(); break;
      case 'r':
        response(); break;
        // default: Serial.println("a"); delay(100);
      }
    }
}

void sleepuC(){
  digitalWrite(LED,0); // SLEEP UP XBEE
  Serial.println("Durmiendo");
  delay(50);
}

void response(){
  Serial.println("Sensor A: OK");
  delay(50);
}
