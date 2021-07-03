#include <SoftwareSerial.h>
#include<SPI.h>
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int OLED_RESET=4;
int lastgear=-1;
  int g;
Adafruit_SSD1306 display(OLED_RESET);

SoftwareSerial gear(5,6);
SoftwareSerial espSerial =  SoftwareSerial(10,11);      // arduino RX pin=2  arduino TX pin=3    connect the arduino RX pin to esp8266 module TX pin   -  connect the arduino TX pin to esp8266 module RX pin


String apiKey = "teamAccelerons";     // replace with your channel's thingspeak WRITE API key
String ssid="ZY";    // Wifi network SSID
String password ="1234567890";  // Wifi network password

boolean DEBUG=true;

long potentiometer_dist=0;
long mean=0;

void showResponse(int waitTime){
    long t=millis();
    char c;
    while (t+waitTime>millis()){
      if (espSerial.available()){
        c=espSerial.read();
        if (DEBUG) Serial.print(c);
      }
    }
}
boolean thingSpeakWrite(float value1,float value2){
  String cmd = "AT+CIPSTART=\"TCP\",\"";                  // TCP connection
  cmd += "dweet.io";                               // api.thingspeak.com
  cmd += "\",80";
  //String cmd ="https://dweet.io/dweet/for/my-thing-name?hello=world;
  espSerial.println(cmd);
  if (DEBUG) Serial.println(cmd);
  if(espSerial.find("Error")){
    if (DEBUG) Serial.println("AT+CIPSTART error");
    return false;
  }
  String getStr = "GET /dweet/for/";   // prepare GET string
  getStr += apiKey;
  getStr +="?a=";
  getStr += String(value1);
  getStr +="&b=";
  getStr += String(value2);
  // getStr +="&field3=";
  // getStr += String(value3);
  // ...
  getStr += "\r\n\r\n";
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  espSerial.println(cmd);
  if (DEBUG)  Serial.println(cmd);
  delay(10);
  if(espSerial.find(">")){
    espSerial.print(getStr);
    if (DEBUG)  Serial.print(getStr);
  }
  else{
    espSerial.println("AT+CIPCLOSE");
    // alert user
    if (DEBUG)   Serial.println("AT+CIPCLOSE");
    return false;
  }
  return true;
}

 void update_display(int gear)
{ 
  
  Serial.println("001");
  display.clearDisplay();
  
  Serial.println("002");
  display.setCursor(40,0);
      display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("GEAR");
  
  Serial.println("003");
   display.setCursor(48,32);
    display.setTextSize(5);
  display.setTextColor(WHITE);
  //display.print(gear);
  //display.display();
  
  Serial.println("004");
}


void Update_display()
{
  
  Serial.println("01");
  if(gear.available())
{g=gear.read()-48;
  if(g>=0&&g<=6)
  {
  if(g!=lastgear)
  {
    update_display(g);
  lastgear=g;}
  }
}
else{
  
  Serial.println("02");
  update_display(0);
  
  Serial.println("03");
}

  Serial.println("04");
}
void setup() {                

  gear.begin(115200);
Serial.begin(115200);  
Serial.println("inside setuo");
  
Serial.println("out");
  DEBUG=true;
  
  espSerial.begin(115200); 
  espSerial.println("AT+RST"); 
 // showResponse(10);
  espSerial.println("AT+CWMODE=1");  
  //showResponse(10);
  espSerial.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");  
  //showResponse(50);
   if (DEBUG)  Serial.println("Setup completed");
/*
  int dis_pot=0;
  for(int i=0;i<10;i++){
      dis_pot+=analogRead(A3);
  }
  mean=dis_pot/10;
  */
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  
  Serial.println("001");
  display.clearDisplay();
  display.setCursor(40,0);
  
  Serial.println("001");
  display.setTextSize(2);
  display.setTextColor(WHITE);
 // display.print("GEAR");
 // display.display();
 
  Serial.println("001");
}
void loop() {
  Serial.println("1--");
Update_display();

  Serial.println("2");
  int gear_esp=g;
  
  Serial.println("3");
  int distance=(analogRead(A3)-mean)/7.3;
  
  Serial.println("4");
        if(thingSpeakWrite(gear_esp,distance)){
          Serial.println("datawritten");
        }
        else{
          Serial.println("sorry ");
        }
}
