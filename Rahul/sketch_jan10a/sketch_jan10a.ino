#include<SoftwareSerial.h>
SoftwareSerial lcd(10,11);
String data="",rpm="",temp="",fuel="";
char ch;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(9600);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  while(lcd.available())
{ data+=lcd.read();
//data+=ch;
}
Serial.println(data);
}
