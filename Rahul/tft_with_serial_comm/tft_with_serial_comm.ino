#define LCD_CS A3    
#define LCD_CD A2    
#define LCD_WR A1   
#define LCD_RD A0    
#define LCD_RESET A4
#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF

#include "TFTLCD.h"

char x;
TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);


uint8_t rotation=1;

void setup(void) {
 
  Serial.begin(9600);
  tft.reset();
  tft.fillScreen(BLACK);
  tft.initDisplay();
  tft.setRotation(rotation);
  setBgd(CYAN,0,70,5);
  tft.println("WELCOME");
  setBgd(CYAN,0,110,5);
  tft.println("BACK");
  delay(1000);
  tft.fillScreen(BLACK);
}

void loop(void) {
  if(Serial.available())
  {
  x = Serial.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
  gearDisplay(x);  
  delay(100);
  }
}

void setBgd(uint16_t color,int x,int y,int size) {
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(size);
 }

void gearDisplay(char x)
{
  if(x=='0')
  {
    setBgd(WHITE,140,10,6);
    tft.println("N");
   
    setBgd(RED,40,60,6);
    tft.println("1");
   
    setBgd(RED,240,60,6);
    tft.println("2");
   
    setBgd(RED,40,110,6);
    tft.println("3");
   
    setBgd(RED,240,110,6);
    tft.println("4");
   
    setBgd(RED,40,160,6);
    tft.println("5");
   
    setBgd(RED,240,160,6);
    tft.println("6");
   
  } 
  
  
  else if(x=='1')
  {
   
    setBgd(RED,140,10,6);
    tft.println("N");
   
    setBgd(WHITE,40,60,6);
    tft.println("1");
   
    setBgd(RED,240,60,6);
    tft.println("2");
   
    setBgd(RED,40,110,6);
    tft.println("3");
   
    setBgd(RED,240,110,6);
    tft.println("4");
   
    setBgd(RED,40,160,6);
    tft.println("5");
   
    setBgd(RED,240,160,6);
    tft.println("6");
   
  } 
  
  else if(x=='2')
  {
   
    setBgd(RED,140,10,6);
    tft.println("N");
   
    setBgd(RED,40,60,6);
    tft.println("1");
   
    setBgd(WHITE,240,60,6);
    tft.println("2");
   
    setBgd(RED,40,110,6);
    tft.println("3");
   
    setBgd(RED,240,110,6);
    tft.println("4");
   
    setBgd(RED,40,160,6);
    tft.println("5");
   
    setBgd(RED,240,160,6);
    tft.println("6");
   
  } 
  
  else if(x=='3')
  {
   
    setBgd(RED,140,10,6);
    tft.println("N");
   
    setBgd(RED,40,60,6);
    tft.println("1");
   
    setBgd(RED,240,60,6);
    tft.println("2");
   
    setBgd(WHITE,40,110,6);
    tft.println("3");
   
    setBgd(RED,240,110,6);
    tft.println("4");
   
    setBgd(RED,40,160,6);
    tft.println("5");
   
    setBgd(RED,240,160,6);
    tft.println("6");
   
  } 
  
  else if(x=='4')
  {
   
    setBgd(RED,140,10,6);
    tft.println("N");
   
    setBgd(RED,40,60,6);
    tft.println("1");
   
    setBgd(RED,240,60,6);
    tft.println("2");
   
    setBgd(RED,40,110,6);
    tft.println("3");
   
    setBgd(WHITE,240,110,6);
    tft.println("4");
   
    setBgd(RED,40,160,6);
    tft.println("5");
   
    setBgd(RED,240,160,6);
    tft.println("6");
   
  } 
  
  else if(x=='5')
  {
   
    setBgd(RED,140,10,6);
    tft.println("N");
   
    setBgd(RED,40,60,6);
    tft.println("1");
   
    setBgd(RED,240,60,6);
    tft.println("2");
   
    setBgd(RED,40,110,6);
    tft.println("3");
   
    setBgd(RED,240,110,6);
    tft.println("4");
   
    setBgd(WHITE,40,160,6);
    tft.println("5");
   
    setBgd(RED,240,160,6);
    tft.println("6");
   
  }
 
 else if(x=='6')
  {
   
    setBgd(RED,140,10,6);
    tft.println("N");
   
    setBgd(RED,40,60,6);
    tft.println("1");
   
    setBgd(RED,240,60,6);
    tft.println("2");
   
    setBgd(RED,40,110,6);
    tft.println("3");
   
    setBgd(RED,240,110,6);
    tft.println("4");
   
    setBgd(RED,40,160,6);
    tft.println("5");
   
    setBgd(WHITE,240,160,6);
    tft.println("6");
   
  }  
  
 else 
  {
   
    setBgd(RED,140,10,6);
    tft.println("N");
   
    setBgd(RED,40,60,6);
    tft.println("1");
   
    setBgd(RED,240,60,6);
    tft.println("2");
   
    setBgd(RED,40,110,6);
    tft.println("3");
   
    setBgd(RED,240,110,6);
    tft.println("4");
   
    setBgd(RED,40,160,6);
    tft.println("5");
   
    setBgd(RED,240,160,6);
    tft.println("6");
   
  }  
  
  
}
