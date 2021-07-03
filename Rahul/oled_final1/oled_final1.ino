#include<SPI.h>
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
int OLED_RESET=4;
int lastgear=-1;
Adafruit_SSD1306 display(OLED_RESET);
#include<SoftwareSerial.h>
SoftwareSerial gear(5,6);
 void update_display(int gear)
{  display.clearDisplay();
  display.setCursor(40,0);
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("GEAR");
   display.setCursor(48,32);
    display.setTextSize(5);
  display.setTextColor(WHITE);
  display.print(gear);
  display.display();
}
void setup()
{ Serial.begin(9600);
gear.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
 display.clearDisplay();
  display.setCursor(40,0);
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("GEAR");
 //display.drawLine(75,0,75,64,WHITE);
display.display();
}
void loop()
{  int g;
  if(gear.available())
{g=gear.read()-48;
  if(g>=0&&g<=6)
  {Serial.println(g);
  if(g!=lastgear)
  {
    update_display(g);
  lastgear=g;}
}}
else Serial.println("NOT CONNECTED");

  

}


