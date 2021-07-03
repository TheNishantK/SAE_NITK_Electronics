#include<SoftwareSerial.h>
SoftwareSerial BT(10,11); //check
String voice;
const int trigpin=6;
const int echopin=7;
long duration,cm;

void setup() {
  BT.begin(38400);
  Serial.begin(38400);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT); 
  pinMode(5,OUTPUT);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(8,OUTPUT);
/* pinMode(22,OUTPUT);
pinMode(24,OUTPUT);
pinMode(26,OUTPUT);*/
}
void loop() {
  while(BT.available())
  {
    delay(10); //stable    
    char c= BT.read();
     if (c == '#') {break;}
    voice+=c;
    }
  
    if(voice.length()>0)
    Serial.println(voice);
//ultrasonic sensor
     digitalWrite(trigpin,LOW);
      delayMicroseconds(2);
      digitalWrite(trigpin,HIGH);
      delayMicroseconds(10);
      digitalWrite(trigpin,LOW);
// a short interval of low pulse 
//and a HIGH pulse interval to set the trig signal 
duration= pulseIn(echopin,HIGH);
 // taking the time interval of the sending and receiving 
 // signal
 cm= microsecondsToCm(duration);//forward
 delay(200);
 //Serial.println(cm);
    if (voice=="*forward")
    {
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      delay(100);
      }
    else if(voice=="*backward")
    {
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);
      delay(100);
    }
    else if(voice=="*left")
    {
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,HIGH);
      delay(100);
      }       
     else if(voice=="*right")
     {
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);
      delay(100);
      }
      else if(voice=="*stop")
      {
        digitalWrite(2,LOW);
      digitalWrite(3,LOW);
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      delay(100);
        }
        
        
else if(cm<5)//forward obstacle
  {   digitalWrite(8,HIGH);
      delay(50);
      digitalWrite(8,LOW);
      delay(50);
       digitalWrite(8,HIGH);
      delay(50);
      digitalWrite(8,LOW);
      delay(50);
      digitalWrite(2,LOW);
      digitalWrite(3,HIGH);
      digitalWrite(4,HIGH);
      digitalWrite(5,LOW);//right
      delay(100);
      delay(5000);//for turning
      digitalWrite(2,HIGH);
      digitalWrite(3,LOW);
      digitalWrite(4,HIGH);//forward
      digitalWrite(5,LOW);
      delay(100); 
      
    }
        
      voice=""; 
}
      long microsecondsToCm (long microseconds)
 {
// The speed of sound = 340m/s or 29microseconds per cm
// The signal travels to- fro motion so we divide by 2
// i.e 29/2
 return microseconds / 29 / 2 ;  
 }


