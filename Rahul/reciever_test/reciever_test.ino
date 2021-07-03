#include<SoftwareSerial.h>
//#include<SPI.h>
//#include<Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>
//int OLED_RESET=4;

long lastmillis=0;
//Adafruit_SSD1306 display(OLED_RESET);
SoftwareSerial led(10,11);
/* void update_display(int rpm,String temp,String dist)
{  display.clearDisplay();
 display.drawLine(0,32,188,32,WHITE);
  display.drawLine(56,32,56,64,WHITE);
  display.setCursor(40,0);
    display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(rpm);
  display.setCursor(3,45);
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print(dist);
   display.setCursor(62,45);
    display.print(temp);
  display.display();
}*/
void setup() {led.begin(9600);

  // put your setup code here, to run once:
Serial.begin(9600);
Serial.print("0");
//display.begin(SSD1306_SWITCHCAPVCC,0x3C);
Serial.print("!");
 //display.clearDisplay();
Serial.print("2");
 //display.display();
 Serial.print("3");
 /*display.drawLine(0,32,188,32,WHITE);
 display.drawLine(56,32,56,64,WHITE);
 display.setTextSize(3);
  display.setTextColor(WHITE);
 display.setCursor(40,0);
 display.print("RPM");
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.setCursor(5,45);
 display.print("DIST");
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.setCursor(58,45);
 display.print(" TEMP");
 display.display();
 delay(1000);*/
}
float fuel=4.5*1000;
float remDist=45.00;
void loop() {

  // put your main code here, to run repeatedly:
String data="";
char buff[9];
int rpm[4];
if(led.available()>0)
{ led.readBytes(buff,9);
  //char ch=led.read();
  //data+=ch;
for(int i =0;i<4;i++)
rpm[i]=buff[i]-48;
for(int i =4;i<=8;i++)
data+=buff[i];
Serial.println(data);
/*for(int i =0;i<4;i++)
Serial.print(rpm[i]);*/
Serial.println("");
int rpm1=rpm[0]*1000+rpm[1]*100+rpm[2]*10+rpm[3];
Serial.println(rpm1);
  if(millis()-lastmillis>=60000 && rpm1)
  {
    fuel=fuel-25;
    remDist=remDist-(10.5*25/1000);
    lastmillis=millis();
    Serial.println(remDist);
  }  
//update_display(rpm1,data,String(remDist,1));
} else Serial.print("jb");
//led.end();
}
