 #include<SPI.h>
#include<Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
int OLED_RESET=4;
Adafruit_SSD1306 display(OLED_RESET);
 int half_revolutions=0 ;
 int a;
 int rpm = 0;
 unsigned long lastmillis = 0;
 void update_display(int rpm)
{ randomSeed(analogRead(A1));

int k=random(-55,55);
float f=(float)k/9; 
  float temp=45+f;
  Serial.print(temp);
  display.clearDisplay();
 display.drawLine(0,32,188,32,WHITE);
  display.drawLine(56,32,56,64,WHITE);
  display.setCursor(60,0);
    display.setTextSize(3);
  display.setTextColor(WHITE);
  display.print(rpm);
  display.setCursor(3,45);
    display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("45 K");
   display.setCursor(62,45);
    display.print(temp);
     //display.setCursor(70,45);
 //display.print("C");
  display.display();
  delay(2000);
}
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC,0x3C);
 display.clearDisplay();
 display.drawLine(0,32,188,32,WHITE);
 display.drawLine(56,32,56,64,WHITE);
 display.setTextSize(3);
  display.setTextColor(WHITE);
 display.setCursor(40,0);
 display.print("RPM");
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.setCursor(5,45);
 display.print("DIST");
 display.setTextSize(2);
  display.setTextColor(WHITE);
 display.setCursor(58,45);
 display.print(" TEMP");
 display.display();
 delay(1000);
  attachInterrupt(0,rpm_fan,FALLING);
}

void loop() {
  

  
if (millis() - lastmillis >= 1000){ //Uptade every one second, this will be equal to reading frecuency (Hz).
  //Disable interrupt when calculating
  detachInterrupt(0);
 a = half_revolutions/2;
 rpm = a * 60; // Convert frecuency to RPM, note: this works for one interruption per full rotation. For two interrups per full rotation use half_revolutions * 30.
 //Serial.print("Check \t ");
 //Serial.print(a);
 Serial.print("\t RPM =\t"); //print the word "RPM" and tab.
 Serial.print(rpm); // print the rpm value
 Serial.print("\t Hz=\t"); //print the word "Hz".
 Serial.println(a); //print revolutions per second or Hz. And print new line or enter.M
 half_revolutions = 0; // Restart the RPM counter
 lastmillis = millis(); // Uptade lasmillis
 update_display(rpm);
 }
 //Serial.println("ghjk");
  attachInterrupt(0,rpm_fan,FALLING);
 // update_display(0);
}

void rpm_fan()
{
  half_revolutions++;
}
 






