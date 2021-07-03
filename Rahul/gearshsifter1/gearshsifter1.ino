const int bgu=11;
const int bgd=12;
const int sgu=9;
const int sgd=10;
int currentgear,expectedgear;
void setup() {
  // put your setup code here, to run once:
pinMode(2,INPUT);
pinMode(3,INPUT);
pinMode(4,INPUT);
pinMode(5,INPUT);
pinMode(6,INPUT);
pinMode(7,INPUT);
pinMode(8,INPUT);
pinMode(sgu,OUTPUT);
pinMode(sgd,OUTPUT);
pinMode(bgu,INPUT);
pinMode(bgd,INPUT);
digitalWrite(13,HIGH);
}
void checkgear()
{
  if(digitalRead(3)==LOW)
  currentgear=0;
  else if(digitalRead(2)==LOW)
  currentgear=1;  
  else if(digitalRead(4)==LOW)
  currentgear=2;
  else if(digitalRead(5)==LOW)
  currentgear=3;
  else if(digitalRead(6)==LOW)
  currentgear=4;
  else if(digitalRead(7)==LOW)
  currentgear=5;
  else if(digitalRead(8)==LOW)
  currentgear=6;
}
void loop() {
 int gearup=0;
 geardown=0;
 if(digitalRead(bgu)==LOW&& digitalRead(bgd)==HIGH)
 {
 while(digitalRead(bgu)==LOW&& digitalRead(bgd)==HIGH)
 gearup=1; 
 geardown=0;
 }
 else if(digitalRead(bgu)==HIGH&& digitalRead(bgd)==LOW)
 {
 while(digitalRead(bgu)==HIGH&& digitalRead(bgd)==LOW)
 geardown=1;
 gearup=0; 
 }
  if(gearup==1&&digitalRead(8)==HIGH)
  {
    checkgear();
    expectedgear=currentgear+1;
    while(currentgear!=expectedgear)
    digitalWrite(sgu,HIGH);
    digitalWrite(sgd,LOW);
  }
  else if(geardown==1&&digitalRead(2)==HIGH)
  { checkgear();
    expectedgear=currentgear-1;
    while(currentgear!=expectedgear)
    digitalWrite(sgu,LOW);
    digitalWrite(sgd,HIGH);  
    }
  
}
