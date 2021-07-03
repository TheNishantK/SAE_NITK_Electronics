#include<SoftwareSerial.h>
SoftwareSerial A(9,10); //Rx,Tx

void setup() {
A.begin(9600);
Serial.begin(9600);
}

void loop() {

while(Serial.available())
A.write(Serial.read());
if(A.available())
{ char c=A.read();
  Serial.print(c);
  
}

}
