#include "TFTLCD.h"
#include "TouchScreen.h"


//Duemilanove/Diecimila/UNO/etc ('168 and '328 chips) microcontoller:



#define YP A1  // must be an analog pin, use "An" notation!
#define XM A2  // must be an analog pin, use "An" notation!
#define YM 7   // can be a digital pin
#define XP 6   // can be a digital pin

#define TS_MINX 180//150
#define TS_MINY 250//120
#define TS_MAXX 920
#define TS_MAXY 910//940

// For better pressure precision, we need to know the resistance
// between X+ and X- Use any multimeter to read it
// For the one we're using, its 300 ohms across the X plate
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0 
// optional
#define LCD_RESET A4

// Color definitions
#define  BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF



TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;

void setup(void) {
  Serial.begin(9600);
  Serial.println("Paint!");
  
  //tft.reset();
  tft.setRotation(1);
  
  tft.fillScreen(0x112200);
  tft.fillRect(0,199,319,239,WHITE);
  tft.drawString(40,80,"TEAM ACCLERONS",BLUE,3);
   tft.drawString(75,123,"NIT KURUKSHETRA",RED,2);
   tft.drawString(20,210,"Touch Here to see magic",BLACK,2);
  pinMode(13, OUTPUT);
}



#define MINPRESSURE 10
#define MAXPRESSURE 1000

void loop()
{
  digitalWrite(13, HIGH);
  Point p = ts.getPoint();
  digitalWrite(13, LOW);
    pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);
  if(p.z>MINPRESSURE&&p.z<MAXPRESSURE){
    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y =239- map(p.y, TS_MINY, TS_MAXY, 0, tft.height());
Serial.println(p.x);
 tft.drawString(40,80,"TEAM ACCLERONS",BLUE,3);
  
   
  
   if(p.y>199)
  {
    tft.fillScreen(WHITE);
    delay(1000);
     tft.drawString(40,80,"MAGIC",BLACK,3);  
     
  }
  }
}
