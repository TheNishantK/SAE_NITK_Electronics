int g1=3;
int g2=4;
int g3=5;
int g4=6;
int g5=7;
int g6=8;
int b_up=11;
int b_dn=12;
int s_up=9;
int s_dn=10;

int gear;
int previousgear;
int debouncedelay=50;
long int lastdebouncetime=0;


void setup()
{
  pinMode(g1,INPUT);
  pinMode(g2,INPUT);
  pinMode(g3,INPUT);
  pinMode(g4,INPUT);
  pinMode(g5,INPUT);
  pinMode(g6,INPUT);
  pinMode(b_up,INPUT);
  pinMode(b_dn,INPUT);
  pinMode(s_up,OUTPUT);
  pinMode(s_dn,OUTPUT);
  Serial.begin(9600);
  
  if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=0;
   if(digitalRead(g1)==LOW&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=1;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==LOW&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=2;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==LOW&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=3;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==LOW&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=4;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==LOW&&digitalRead(g6)==HIGH)
   gear=5;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==LOW)
   gear=6;
 
  previousgear=gear;    // sets the value of previousgear : for later use
 
}
void loop()
{
 
  if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=0;
   if(digitalRead(g1)==LOW&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=1;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==LOW&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=2;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==LOW&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=3;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==LOW&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH)
   gear=4;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==LOW&&digitalRead(g6)==HIGH)
   gear=5;
   if(digitalRead(g1)==HIGH&&digitalRead(g2)==HIGH&&digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==LOW)
   gear=6;

 if(digitalRead(b_up)==LOW && (millis()-lastdebouncetime>debouncedelay) && previousgear<6)
  {digitalWrite(s_up,HIGH); //to operate solenoid
    lastdebouncetime=millis();}
  if(gear != previousgear)
  {digitalWrite(s_up,LOW);
  previousgear=gear;
  Serial.print(gear);}
  
 if(digitalRead(b_dn)==LOW && (millis()-lastdebouncetime>debouncedelay) && (previousgear>1 || previousgear==0))
   { digitalWrite(s_dn,HIGH); //to operate solenoid
     lastdebouncetime=millis();}
   if(gear != previousgear)
   {digitalWrite(s_dn,LOW);
   previousgear=gear;
   Serial.print(gear);}
 
  
}


