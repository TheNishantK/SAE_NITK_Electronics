#include<SoftwareSerial.h>
SoftwareSerial sample(9,10); //Rx,Tx

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
sample.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available())
{
  sample.write(Serial.read());
  if(sample.available())
  { 
    char c=sample.read();
    Serial.print(c);
    
  }

}

}
