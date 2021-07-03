#include<SoftwareSerial.h>
//SoftwareSerial mySerial(5,6);
void setup() {
 // mySerial.begin(9600);
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//int k=123;
  //mySerial.print(k);
  Serial.print("a");
  delay(100);
}

