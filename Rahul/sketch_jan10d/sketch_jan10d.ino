#include <SoftwareSerial.h>

SoftwareSerial lcd(10,11);
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
lcd.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
if (lcd.available()) {
    int inByte = lcd.read();
    Serial.write(inByte);
  }

  // read from port 0, send to port 1:
  if (Serial.available()) {
    int inByte = Serial.read();
    lcd.write(inByte);
  }
}
