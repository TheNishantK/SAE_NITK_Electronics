#include "max6675.h"
int ktcSO = 13;
int ktcCS = 12;
int ktcCLK = 11;

 int half_revolutions = 0;
 int rpm = 0;
  int half_revolutions1 = 0;
 int rpm1 = 0;
 unsigned long lastmillis = 0;
 MAX6675 ktc(ktcCLK, ktcCS, ktcSO); 
float flowRate=0.0;
float calibrationFactor = 4.5;
 void setup(){
 Serial.begin(9600); 
// pinMode(13, OUTPUT);
// pinMode(12, OUTPUT);
 attachInterrupt(0, rpm_fan, FALLING);
 attachInterrupt(1, rpm_fan1, FALLING);

 }
 void loop(){
//  digitalWrite(13,HIGH);
//  digitalWrite(12,LOW);
 
  if (millis() - lastmillis == 1000){ //Uptade every one second, this will be equal to reading frecuency (Hz).
  
   detachInterrupt(0);//Disable interrupt when calculating
   detachInterrupt(1);
   
   flowRate = ( half_revolutions) / calibrationFactor;
   
   //rpm=rpm*1;

    Serial.print("\tRPM=\t");
   Serial.print(flowRate);
    
   half_revolutions = 0; // Restart the RPM counter

   rpm1 = (half_revolutions1-1)*60;
   //rpm1=rpm1*1;
 
  Serial.print("\tRPM 1=\t");
   Serial.println(rpm1);
    
   half_revolutions1 = 0; // Restart the RPM counter
    Serial.println(ktc.readCelsius());
   lastmillis = millis(); // Uptade lasmillis
 
  attachInterrupt(0, rpm_fan, FALLING);
   attachInterrupt(1, rpm_fan1, FALLING); 
  }
 }
 // this code will be executed every time the interrupt 0 (pin2) gets low.
 void rpm_fan(){
  half_revolutions++;
 }
 void rpm_fan1(){
  half_revolutions1++;
 }
