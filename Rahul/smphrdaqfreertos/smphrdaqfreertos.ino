#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
#include "max6675.h"
// Declare a mutex Semaphore Handle which we will use to manage the Serial Port.
// It will be used to ensure only only one Task is accessing this resource at any time.
SemaphoreHandle_t xSerialSemaphore;

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

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  // Semaphores are useful to stop a Task proceeding, where it should be paused to wait,
  // because it is sharing a resource, such as the Serial port.
  // Semaphores should only be used whilst the scheduler is running, but we can set it up here.
  if ( xSerialSemaphore == NULL )  // Check to confirm that the Serial Semaphore has not already been created.
  {
    xSerialSemaphore = xSemaphoreCreateMutex();  // Create a mutex semaphore we will use to manage the Serial Port
    if ( ( xSerialSemaphore ) != NULL )
      xSemaphoreGive( ( xSerialSemaphore ) );  // Make the Serial Port available for use, by "Giving" the Semaphore.
  }

  // Now set up two Tasks to run independently.
   xTaskCreate(
    Temp
    ,  (const portCHAR *)"Temperature"   // A name just for humans
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
  // Now the Task scheduler, which takes over control of scheduling individual Tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void Temp(void *pvParameters __attribute__((unused)))  // This is a task.
{
  (void) pvParameters;

  for (;;) // A Task shall never return or exit.
  { Serial.begin(9600);
   if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
     Serial.print("Temp=");
    Serial.println(ktc.readCelsius());
      xSemaphoreGive( xSerialSemaphore );
    }
  
    delay(1000);
    //vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}

void Calc_RPM(void *pvParameters __attribute__((unused)))  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
     
    // detachInterrupt(0);// flowrate
     detachInterrupt(1);// rpm
     
   rpm = half_revolutions * 60; 
   
   if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
     Serial.print("RPM=");
 Serial.println(rpm); 
      xSemaphoreGive( xSerialSemaphore );
    }
   half_revolutions = 0; // Restart the RPM counter
  
 
    
   
      attachInterrupt(1, rpm_fan, FALLING); //enable interrupt
     // attachInterrupt(0, pulseCounter, FALLING);
  delay(1000);
    //vTaskDelay(1000/portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
  }
}
void Calc_Flow(void *pvParameters __attribute__((unused)))  // This is a task.
{
  (void) pvParameters;

  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);

  for (;;)
  {
     
    // detachInterrupt(0);// flowrate
     detachInterrupt(0);// rpm
     flowRate =  pulseCount / (calibrationFactor);
   
 if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      Serial.print("FLOW=");
 Serial.println(flowRate);
      xSemaphoreGive( xSerialSemaphore );
    }
   pulseCount  = 0; // Restart the RPM counter
   
     attachInterrupt(0, pulseCounter, FALLING);
     
  delay(1000);
    }
}
void Calc_Air_Flow(void *pvParameters __attribute__((unused)))  // This is a task.
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
    if ( xSemaphoreTake( xSerialSemaphore, ( TickType_t ) 5 ) == pdTRUE )
    {
      Serial.print("Air Flow=");
    Serial.println(velocity);
      xSemaphoreGive( xSerialSemaphore );
    }
//    delay(1000);
     //vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}
