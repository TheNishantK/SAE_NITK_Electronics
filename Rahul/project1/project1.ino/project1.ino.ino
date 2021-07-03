#include<SPI.h>
#include<Wire.h>
#include<math.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
int OLED_RESET=4;
Adafruit_SSD1306 display(OLED_RESET);
void setup()
{ Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
 display.clearDisplay();
}
void loop()
{
  display.setCursor(0,0);
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.print("123");
  display.display();
}


