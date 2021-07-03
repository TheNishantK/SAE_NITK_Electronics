#include <SoftwareSerial.h>
#include <TinyGPS.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <max6675.h>

Adafruit_SSD1306 display(4);
MAX6675 ktc(12, 11, 10);
TinyGPS gps;

SoftwareSerial espSerial =  SoftwareSerial(5,6);
SoftwareSerial l =  SoftwareSerial(8,9); 

/* rpm*/
int half_revolutions=0 ;
/*rpm*/

/* flow rate*/
 byte pulseCount;
/* flow rate*/

/*writting data*/
boolean DEBUG=true;
/*writting data*/ 


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

//  if(thingSpeakWrite(lat,lang,deg_c,totalMilliLitres,rpm)){
boolean thingSpeakWrite(float value1,float value2,float value3,float value4,float value5){
String apiKey = "eventBaja";     

String cmd = "AT+CIPSTART=\"TCP\",\"";                  // TCP connection
cmd += "dweet.io";                    
cmd += "\",80";
espSerial.println(cmd);
if (DEBUG) Serial.println(cmd);
if(espSerial.find("Error")){
  if (DEBUG) Serial.println("AT+CIPSTART error");
  return false;
}
String getStr = "GET /dweet/for/";
getStr += apiKey;
getStr +="?lat=";
getStr += String(value1,6);
getStr +="&long=";
getStr += String(value2,6);
getStr +="&temp=";
getStr += String(value3,6);
getStr +="&fuel=";
getStr += String(value4,6); 
getStr +="&rpm=";
getStr += String(value5);
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
    if (DEBUG)   Serial.println("AT+CIPCLOSE");
    return false;
  }
return true;
}
void display_oled(int rpm,float fuel,float temp)
{
  display.clearDisplay();
  display.drawLine(0,32,128,32,WHITE);
  display.drawLine(55,32,55,64,WHITE);
  display.setCursor(32,0);
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.print(rpm);
  display.setCursor(0,45);
  display.setTextSize(2);
  display.print(fuel);
  display.setCursor(38,45);
  display.print("L");
  display.setCursor(59,45);
  display.setTextSize(2);
  display.print(temp);
  display.setCursor(111,45);
  display.print("C");
  display.display();
}

// this code will be executed every time the interrupt 0 (pin2) gets low.
void rpm_fan(){
  half_revolutions++;
}

void pulseCounter()
{
// Increment the pulse counter
  pulseCount++;
}
void setup() {
  
  Serial.begin(115200);   
  DEBUG=true; 
  espSerial.begin(115200); 
  espSerial.println("AT+RST"); 
  showResponse(1000);
  espSerial.println("AT+CWMODE=1");  
  showResponse(1000);
String ssid="BDDN";    
String password ="9896790301";

  espSerial.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");  
  showResponse(5000);
  if (DEBUG)  Serial.println("Setup completed");
  espSerial.end();
  attachInterrupt(0, rpm_fan, FALLING); //pin 2 is interrupt 0 and pin 3 is interrupt 1
  
  pulseCount        = 0;
  
  attachInterrupt(1, pulseCounter, FALLING);
  Serial.println("1");
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);              
  Serial.println("2");

}
void loop() {
  float lat,lang;
int a;
int rpm = 0;
unsigned long lastmillis = 0;

byte sensorPin = 2;
float calibrationFactor = 4.5;  
float flowRate=0.0;
unsigned int flowMilliLitres=0;
float totalMilliLitres=0;
unsigned long oldTime=0;

Serial.println("3");
display_oled(0,4.5,5);
Serial.println("4");
float deg_c=ktc.readCelsius();

 if (1){ //Update every one second, this will be equal to reading frecuency (Hz).
 detachInterrupt(0);//Disable interrupt when calculating
 detachInterrupt(1);
 a = half_revolutions/2;
 rpm = a * 60; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.

 //Serial.print("Check \t ");
 //Serial.print(a);
 Serial.print("\t RPM =\t"); //print the word "RPM" and tab.
 Serial.print(rpm); // print the rpm value.
 Serial.print("\t Hz=\t"); //print the word "Hz".
 Serial.println(a); //print revolutions per second or Hz. And print new line
 half_revolutions = 0; // Restart the RPM counter


  flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
  oldTime = millis();
  flowMilliLitres = (flowRate / 60) * 1000;
  totalMilliLitres += flowMilliLitres;
  unsigned int frac;
  frac = (flowRate - int(flowRate)) * 10;
  Serial.print("  Output Liquid Quantity: ");             // Output separator
  Serial.print(totalMilliLitres);
  Serial.println("mL"); 
  totalMilliLitres/=1000;
  pulseCount = 0;
  attachInterrupt(1, pulseCounter, FALLING);
  attachInterrupt(0, rpm_fan, FALLING); //enable interrupt
}
/*rpm*/

/* gps start*/
l.begin(9600);

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (l.available())
    {
      char c = l.read();
        if (gps.encode(c)) // Did a new valid sentence come in?
          newData = true;
    }
  }          
  
  if (newData)
  {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
     Serial.print("LAT=");
    Serial.println( flat, 6);
    Serial.print(" LON=");
    Serial.println(flon, 6);
    lat=flat;
    lang=flon;
  }
l.end();
/* gps end*/

/*thermocouple start*/
/*thermocouple end*/

/* oled*/
 display_oled(rpm,totalMilliLitres,deg_c);
 /*oled*/
Serial.print("latitude ");
Serial.println(lat);
Serial.print("latitude ");
Serial.println(lang);
Serial.print("temp ");
Serial.println(deg_c);
Serial.print("volume ");
Serial.println(flowRate);
Serial.print("lrpms ");
Serial.println(rpm);
/*ESP8266 start*/
espSerial.begin(115200); 
  if(thingSpeakWrite(lat,lang,deg_c,totalMilliLitres,rpm)){
    Serial.println("datawritten");
  }
  else{
    Serial.println("sorry ");
  }
espSerial.end();
/*ESP8266 end*/
}
