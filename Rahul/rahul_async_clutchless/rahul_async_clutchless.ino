

#include <Arduino_FreeRTOS.h>

// define two tasks for Blink & AnalogRead
void clutchRead( void *pvParameters );
void gearRead( void *pvParameters );

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
int flag=0;
int bcs;         //button clutch slow
int bdn;
int bup;
int lbdn=HIGH;
int lbup=HIGH;
int gear,lastgear=-1;


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
  scan_gear();            //check gear
  Serial.print(gear);
  lastgear = gear;
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
    lastgear=-1;
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
  { scan_gear();
    clutch_button= digitalRead(c_btn);
  if(clutch_button==LOW){
    digitalWrite(c_ft_ip,HIGH);
    delay(20);
    while(clutch_button==LOW)
   clutch_button= digitalRead(c_btn);
   digitalWrite(c_ft_ip,LOW);
   delay(20);
   } 
  }
}

void gearRead(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  
  lastgear=gear;
  for (;;)
  {
    scan_gear();
    if(lastgear!=gear){
      Serial.print(gear);
      lastgear=gear;
      if(gear==1)
      flag=1;
      else flag=0;
    }
   bdn=digitalRead(gdn);
   bup=digitalRead(gup);   
   
      if(bup != lbup)
      {
        if(bup==LOW)
        { 
          /*if(gear==1&&flag)
            {//do nothing
              digitalWrite(g_dn_ip,LOW);
              digitalWrite(g_up_ip,LOW);
              digitalWrite(c_sw_ip,LOW);
              digitalWrite(c_ft_ip,LOW);
            }
          else
            {*/
                     if(lastgear==0||gear==0)
                    digitalWrite(c_sw_ip,HIGH);
                    else
                    digitalWrite(c_ft_ip,HIGH);
                    delay(20);
                    digitalWrite(g_dn_ip,LOW);
                    digitalWrite(g_up_ip,LOW);
                    while(analogRead(up)<=100)
                    { 
                      digitalWrite(g_up_ip,HIGH);
                    }
                    digitalWrite(g_up_ip,LOW);
                    delay(5);
             //}
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
          delay(30);
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
            delay(20);
            digitalWrite(g_dn_ip,LOW);
            digitalWrite(g_up_ip,LOW);
            while(analogRead(dn)<=100)
            {
              digitalWrite(g_dn_ip,HIGH);
            }
            digitalWrite(g_dn_ip,LOW);
            delay(20);
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
            delay(30);
          }
          lbdn=bdn;
        } 
  }                     //end of for loop
}                       // end of function 
