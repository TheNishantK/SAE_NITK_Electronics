int buz=10;
int led=13;
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  pinMode(10,OUTPUT);
  
}
void loop(){}

// the loop function runs over and over again forever
void loop1(1000) {
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);                       // wait for a second
}void loop2(2000) {
  digitalWrite(buz, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(buz, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);  
  Serial.println("hello");// wait for a second
}


