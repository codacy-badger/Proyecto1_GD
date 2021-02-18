#include <SoftwareSerial.h>

const size_t dataLength = 3;
int16_t  data[dataLength];
int dataIndex = 0;

//int16_t BMA400_Data[3];
SoftwareSerial mySerial(10, 11); // RX, TX


uint16_t byteToInt(byte byte1, byte byte2)
{
   return (uint16_t)byte1 << 8 | (uint16_t)byte2;
}



void OkAction()
{
  Serial.print(data[0]);Serial.print(",");Serial.print(data[1]);Serial.print(",");Serial.println(data[2]);
}

void setup()
{
   Serial.begin(9600);
   mySerial.begin(9600);
}
 
void loop()
{
  // if(TryGetSerialData(data, NUM_BYTES))
  // {
  //    OkAction();
  // }
//   if(mySerial.available() >= sizeof(data[0]))
//  {
//    byte byte1 = mySerial.read();
//    byte byte2 = mySerial.read();
//    data[dataIndex] = byteToInt(byte1, byte2);
// 
//    dataIndex++;
//    if(dataIndex >= dataLength)
//    {
//      dataIndex = 0;
//    }
//    OkAction();
//  } 
//  
  if (mySerial.available()){
      //delay(200);
      Serial.write(mySerial.read());
      //delay(100);
  //    mySerial.readBytes((byte*)data, NUM_BYTES*sizeof(data[0]));
  //    BMAdataToInt(data,BMA400_Data); 
      //OkAction();
      
  }
}


 
