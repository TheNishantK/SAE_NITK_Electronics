#include <SoftwareSerial.h>

SoftwareSerial lcd(10,11);

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
lcd.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
String data="",a="",b="",c="",d="";
  while(lcd.available()) {
    int inByte = lcd.read();
  int a=inByte;
  char c=a;
  data+=c;
  }
  Serial.println(data);
  char charBuf[30];
  data.toCharArray(charBuf,30);
  int count=1;
  a+=charBuf[0];a+=charBuf[1];a+=charBuf[2];a+=charBuf[3];a+=charBuf[4];
  b+=charBuf[6];b+=charBuf[7];b+=charBuf[8];b+=charBuf[9];b+=charBuf[10];
  c+=charBuf[12];c+=charBuf[13];c+=charBuf[14];c+=charBuf[15];c+=charBuf[16];
  d+=charBuf[18];d+=charBuf[19];d+=charBuf[20];d+=charBuf[21];d+=charBuf[22];

  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(d);
  delay(500);
}
