 int half_revolutions=0 ;
 int a;
 int rpm = 0;
 unsigned long aa=0,b=0;
 void setup(){
 Serial.begin(9600);
 delay(5000);
 Serial.println("2");
 delay(5000);
 Serial.println("2");
// lastmillis=millis()-1000;
 attachInterrupt(0, rpm_fan, FALLING); //pin 2 is interrupt 0 and pin 3 is interrupt 1
 
 }
 void loop(){
 if (1){ //Update every one second, this will be equal to reading frecuency (Hz).
 detachInterrupt(0);//Disable interrupt when calculating
 a = half_revolutions/2;
 rpm = a * 60; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
  //Serial.print("Check \t ");
 //Serial.print(a);
 Serial.print("\t RPM =\t"); //print the word "RPM" and tab.
 Serial.print(rpm); // print the rpm value.
 Serial.print("\t Hz=\t"); //print the word "Hz".
 Serial.println(a); //print revolutions per second or Hz. And print new line
 half_revolutions = 0; // Restart the RPM counter
// lastmillis = millis(); // Update lasmillis
  //enable interrupt
  attachInterrupt(0, rpm_fan, FALLING);  
  }

  delay(1000);
 }
 
 // this code will be executed every time the interrupt 0 (pin2) gets low.
 void rpm_fan(){
  half_revolutions++;
 }
 
