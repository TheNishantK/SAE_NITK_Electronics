#include<SPI.h>
#include<Wire.h>
#include<math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
int OLED_RESET=4;
Adafruit_SSD1306 display(OLED_RESET);
#define degreesToRadians(angleDegrees) (angleDegrees * M_PI / 180.0)
int half_revolutions=0 ;
 int a;
 int rpm = 0;
 unsigned long lastmillis = 0;
void drawmeter()
{
 display.fillCircle(32, display.height()/2, 32, WHITE);
  display.fillCircle(32, display.height()/2, 30, BLACK);
  for(int i=-30;i<=210;i=i+30)
  { double cos_i=cos(degreesToRadians(i));
  double sin_i=sin(degreesToRadians(i));
    display.drawLine((32*(1-cos_i)),(32*(1-sin_i)),32,32,WHITE);//(26*(1-cos_i)),(26*(1-sin_i)),WHITE);
     display.display(); 
    display.drawLine((26*(1-cos_i)),(26*(1-sin_i)),32,32,BLACK);
     if(i==-30){
    display.setCursor((32*(1-cos_i))+5,(32*(1-sin_i)));
    display.setTextSize(1);
  display.setTextColor(WHITE);
    display.print(" 0");
    display.setCursor((32*(1-cos_i))+20,(32*(1-sin_i))+5);
     display.print("RPM");
    }
    if(i==210){
    display.setCursor((32*(1-cos_i))-11,(32*(1-sin_i))-1);
    display.setTextSize(1);
  display.setTextColor(WHITE);
    display.print("8");
    }
    display.fillCircle((32*(1-cos_i)),(32*(1-sin_i)),4,WHITE);
    display.drawLine(68,64,68,0,WHITE);
    display.drawLine(68,32,128,32,WHITE);
     display.setCursor(70,0);
     display.print("RPM");
     display.setCursor(70,34);
    display.print("GEAR");
    display.display();
  } 
}
void update_display(int rpm,int gear)
{  display.clearDisplay();
   display.drawLine(73,64,73,0,WHITE);
   display.setCursor(16,0);
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("RPM");
   display.setCursor(0,32);
    display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(rpm);
  display.setCursor(80,0);
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("GEAR");
   display.setCursor(95,32);
    display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(gear);
  display.display();
}
void setup()
{ Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
 display.clearDisplay();
 drawmeter();
attachInterrupt(0, rpm_fan, FALLING);
}
void loop()
{static int i=0;
  if (millis() - lastmillis == 1000){ //Uptade every one second, this will be equal to reading frecuency (Hz).
 detachInterrupt(0);//Disable interrupt when calculating
 a = half_revolutions/2;
 rpm = a * 60; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.

 Serial.print("\t RPM =\t"); //print the word "RPM" and tab.
 Serial.print(rpm); // print the rpm value.
 Serial.print("\t Hz=\t"); //print the word "Hz".
 Serial.println(a); //print revolutions per second or Hz. And print new line or enter.M
 half_revolutions = 0; // Restart the RPM counter
 lastmillis = millis(); // Uptade lasmillis
 drawmeter();
 double angle=(rpm-60)/2;
 double sin_angle=sin(degreesToRadians(angle));
 double cos_angle=cos(degreesToRadians(angle));
 display.drawLine(32,32,32*(1-cos_angle),32*(1-sin_angle),WHITE);
 display.setCursor(90,16);
  display.setTextSize(2);
 display.print(rpm);
     display.setCursor(90,50);
    display.print("0");
 display.display();
  
 update_display(analogRead(A1),0);
 attachInterrupt(0, rpm_fan, FALLING); //enable interrupt  
}
}
void rpm_fan(){
  half_revolutions++;
 }
 
