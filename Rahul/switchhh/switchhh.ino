const int buttonPin = 2;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin

// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   

unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50;    




const int buzzer =9;
void setup() {

  pinMode(8, INPUT);
  pinMode(12,OUTPUT);
   pinMode(10,OUTPUT);
   pinMode(buzzer,OUTPUT);


     
}


void loop() {
  tone(buzzer,1000); 
   
noTone(buzzer);    
  int reading = digitalRead(8);


  if (reading != lastButtonState) {
   
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
 
    if (reading != LOW) {
      buttonState = reading;

    
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  digitalWrite(10, HIGH);
  digitalWrite(12,HIGH);
  lastButtonState = reading;
}
