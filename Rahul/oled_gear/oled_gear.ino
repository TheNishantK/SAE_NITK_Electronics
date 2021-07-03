#include<SPI.h>
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include<SoftwareSerial.h>
SoftwareSerial gear(5,6);

int OLED_RESET=4;
int lastgear=-1;

Adafruit_SSD1306 display(OLED_RESET);

 void update_display(int gear)
{  display.clearDisplay();
 display.fillRect(0,0,128,19,WHITE);
  display.setCursor(38,1);
  display.setTextSize(2);
  display.setTextColor(INVERSE);
  display.print("GEAR");;
   display.setCursor(54,22);
    display.setTextSize(5);
  display.setTextColor(WHITE);
  display.print(gear);
  display.display();
}

void setup()
{ 
  Serial.begin(9600);
  gear.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.clearDisplay();
  //display.setRotation(2);
  display.fillRect(0,0,128,19,WHITE);
  display.setCursor(38,1);
  display.setTextSize(2);
  display.setTextColor(INVERSE);
  display.print("GEAR");
  display.setCursor(46,30);
  display.print("N/A");
  display.display();
  //delay(3000);
  //update_display(0);delay(2000);update_display(1);delay(2000);update_display(2);delay(2000);update_display(3);delay(2000);update_display(4);delay(2000);update_display(5);delay(2000);update_display(6);
}

void loop()
{  int g;
 
  if(gear.available())
{ 
  g=gear.read()-48;     //ASCII Adjust
  Serial.println(g);
  update_display(g);
}
 
}
