long reading,reading1;
float angle;
int initial=0;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
reading1=analogRead(A2);
//loat dist1=(reading1-146)/7.3;

}

void loop() {
  // put your main code here, to run repeatedly:
reading=analogRead(A2);
float dist;
dist=(reading-reading1)/7.3;
Serial.print(reading);
Serial.print("         ");
Serial.println(dist);
/*angle=-(reading-442)/3.1529411764705882352941176470588;
Serial.print("     ");
Serial.println(angle);*/
delay(500);
}
