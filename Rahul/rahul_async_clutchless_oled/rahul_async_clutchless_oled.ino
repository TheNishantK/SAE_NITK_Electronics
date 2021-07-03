
#include<SPI.h>
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Arduino_FreeRTOS.h>

// define two tasks for Blink & AnalogRead
void clutchRead( void *pvParameters );
void gearRead( void *pvParameters );
int OLED_RESET=4;


Adafruit_SSD1306 display(OLED_RESET);
const int gup=9;
const int gdn=8;
const int c_btn=6;         //clutch button
const int G1=10;
const int G2=11;
const int G3=12;
const int c_sw_ip=5;
const int c_ft_ip=4;

const int g_up_ip=3;
const int g_dn_ip=2;
const int dn = A0;
const int up = A1;
 int clutch_button;

int bcs;         //button clutch slow
int bdn;
int bup;
int lbdn=HIGH;
int lbup=HIGH;
int gear,lastgear=-1;

void update_oled()
{  
  display.clearDisplay();
  display.setCursor(54,0);
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.print("GEAR");
  display.setCursor(60,10);
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(gear);
  display.display();
}

// the setup function runs once when you press reset or power the board
void setup() {
  
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(gup,INPUT);
  pinMode(gdn,INPUT);
  pinMode(c_btn,INPUT);
  pinMode(G1,INPUT);
  pinMode(G2,INPUT);
  pinMode(G3,INPUT);
  pinMode(up,INPUT);
  pinMode(dn,INPUT);
  pinMode(c_sw_ip,OUTPUT);
  pinMode(c_ft_ip,OUTPUT);
  pinMode(g_up_ip,OUTPUT);
  pinMode(g_dn_ip,OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(c_ft_ip,LOW);
  digitalWrite(c_sw_ip,LOW);
  digitalWrite(g_up_ip,LOW);
  digitalWrite(g_dn_ip,LOW);
  scan_gear();            //check gear
  Serial.print(gear);
  lastgear = gear;
  
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
  display.clearDisplay();
  display.display();
  update_oled();
  xTaskCreate(
    clutchRead
    ,  (const portCHAR *)"Controlling Clutch By Button" 
    ,  128 
    ,  NULL
    ,  1 
    ,  NULL );

  xTaskCreate(
    gearRead
    ,  (const portCHAR *) "Gear Shifter"
    ,  128  
    ,  NULL
    ,  1  
    ,  NULL );
    
    xTaskCreate(
    printGear
    ,  (const portCHAR *) "Printing Gear Value on Oled and Serial Port"
    ,  128  
    ,  NULL
    ,  2 
    ,  NULL );
}

 void scan_gear()
{
  if(digitalRead(G1)==LOW&&digitalRead(G2)==HIGH&&digitalRead(G3)==HIGH)
   gear=0;
   if(digitalRead(G1)==HIGH&&digitalRead(G2)==LOW&&digitalRead(G3)==HIGH)
   gear=1;
   if(digitalRead(G1)==LOW&&digitalRead(G2)==LOW&&digitalRead(G3)==HIGH)
   gear=2;
   if(digitalRead(G1)==HIGH&&digitalRead(G2)==HIGH&&digitalRead(G3)==LOW)
   gear=3;
   if(digitalRead(G1)==LOW&&digitalRead(G2)==HIGH&&digitalRead(G3)==LOW)
   gear=4;
   if(digitalRead(G1)==HIGH&&digitalRead(G2)==LOW&&digitalRead(G3)==LOW)
   gear=5;
   if(digitalRead(G1)==LOW&&digitalRead(G2)==LOW&&digitalRead(G3)==LOW)
   gear=6;
}


void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void clutchRead(void *pvParameters)  
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    clutch_button= digitalRead(c_btn);
  if(clutch_button==LOW){
    digitalWrite(c_ft_ip,HIGH);
    while(clutch_button==LOW)
    {Serial.println("clutch button on");
   clutch_button= digitalRead(c_btn);}
   digitalWrite(c_ft_ip,LOW);
   } 
  }
}

void printGear(void *pvParameters)  
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  {
    scan_gear();
    if(lastgear!=gear)
    {
      Serial.print(gear);
      update_oled();
    }
   } 
}


void gearRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  for (;;)
  {
    digitalWrite(13,HIGH);
   bdn=digitalRead(gdn);
   bup=digitalRead(gup);   
   
      if(bup != lbup)
      { 
        if(bup==LOW)
        { 
          if(lastgear==0)
          digitalWrite(c_sw_ip,HIGH);
          else
          digitalWrite(c_ft_ip,HIGH);
          while(analogRead(up)<=100)
          {
            digitalWrite(g_up_ip,HIGH);
            delay(10);
          }
          digitalWrite(g_up_ip,LOW);
          clutch_button= digitalRead(c_btn);
          if(clutch_button==LOW)
          {
            while(clutch_button==LOW)
              clutch_button= digitalRead(c_btn);
          }
          if(lastgear==0)
          digitalWrite(c_sw_ip,LOW);
          else
          digitalWrite(c_ft_ip,LOW);
          scan_gear();
          Serial.print(gear);
          update_oled();
          lastgear=gear;
        }
        lbup=bup;
      }
      
      if(bdn != lbdn)
      {
          if(bdn==LOW)
          {
            if(lastgear==0)
            digitalWrite(c_sw_ip,HIGH);
            else
            digitalWrite(c_ft_ip,HIGH);
            while(analogRead(dn)<=100)
            {
              digitalWrite(g_dn_ip,HIGH);
              delay(10);
            }
            digitalWrite(g_dn_ip,LOW);
            clutch_button= digitalRead(c_btn);
            if(clutch_button==LOW)
            {
              while(clutch_button==LOW)
                clutch_button= digitalRead(c_btn);
            }

            if(lastgear==0)
            digitalWrite(c_sw_ip,LOW);
            else
            digitalWrite(c_sw_ip,LOW);
            scan_gear();
            Serial.print(gear);
            update_oled();
            lastgear=gear;
          }
          lbdn=bdn;
        } 
  }                     //end of for loop
}                       // end of function 
