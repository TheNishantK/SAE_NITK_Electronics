#include <Arduino_FreeRTOS.h>
#include "max6675.h"
int ktcSO = 13;
int ktcCS = 12;
int ktcCLK = 11;
MAX6675 ktc(ktcCLK, ktcCS, ktcSO);

 int half_revolutions=0;
int a;
int rpm = 0;
unsigned long lastmillis = 0;
float calibrationFactor = 4.5;
int  pulseCount=0;  

const int trigPin = 9; // ultrasonic-- flowrate
const int echoPin = 5;
long duration;
float distance;
float velocity;

float flowRate;
 void rpm_fan(){
  half_revolutions++;
 }
 void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
// define two tasks for Blink & AnalogRead
void Temp( void *pvParameters );
void Calc_RPM( void *pvParameters );
void Calc_Flow( void *pvParameters );
void Calc_Air_Flow( void *pvParameters );
// the setup function runs once when you press reset or power the board
void setup() {

  // Now set up two tasks to run independently.
  xTaskCreate( Temp ,  (const portCHAR *)"Temperature"   // A name just for humans
    ,  128  // Stack size
    ,  NULL
    ,  1  // priority
    ,  NULL );

  xTaskCreate(
    Calc_RPM
    ,  (const portCHAR *) "Calculation of RPM"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  1  // priority
    ,  NULL );
 
  xTaskCreate(
    Calc_Air_Flow
    ,  (const portCHAR *) "Calculation of RPM"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,    1// priority
    ,  NULL );
    
    xTaskCreate(
    Calc_Flow
    ,  (const portCHAR *) "Calculation of RPM"
    ,  128 // This stack size can be checked & adjusted by reading Highwater
    ,  NULL
    ,  1  // priority
    ,  NULL );
    attachInterrupt(0, pulseCounter, FALLING);
    
    attachInterrupt(1, rpm_fan, FALLING);
  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void Temp(void *pvParameters __attribute__((unused)))  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  { Serial.begin(9600);
  Serial.print("Temp=");
    Serial.println(ktc.readCelsius());
    delay(1000);
    //vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void Calc_RPM(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
     
    // detachInterrupt(0);// flowrate
     detachInterrupt(1);// rpm
     
   rpm = half_revolutions * 60; 
   Serial.print("RPM=");
 Serial.println(rpm);  
   half_revolutions = 0; // Restart the RPM counter
  
 
     /// lastmillis = millis(); // Update lasmillis
   
      attachInterrupt(1, rpm_fan, FALLING); //enable interrupt
     // attachInterrupt(0, pulseCounter, FALLING);
  delay(1000);
    //vTaskDelay(1000/portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}
void Calc_Flow(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
     
    // detachInterrupt(0);// flowrate
     detachInterrupt(0);// rpm
     flowRate =  pulseCount / (calibrationFactor);
  Serial.print("FLOW=");
 Serial.println(flowRate);  
   pulseCount  = 0; // Restart the RPM counter
  
 
      // Update lasmillis
   
      //attachInterrupt(1, rpm_fan, FALLING); //enable interrupt
     attachInterrupt(0, pulseCounter, FALLING);
  delay(1000);
   // vTaskDelay(1000/portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}
void Calc_Air_Flow(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
     digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); 
    velocity=(135000/(duration))-344;
    Serial.print("Air Flow=");
    Serial.println(velocity);
    delay(1000);
     //vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
