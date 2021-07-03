const int gup=11;
const int gdn=12;
const int s_up=9;
const int s_dn=10;
const int g2=2;
const int g3=3;
const int g4=4;
const int g5=5;
const int g6=6;
const int g7=7;
const int g8=8;
int bdn;
int bup;
int lbdn;
int lbup;
int gear,lastgear=-1;
void setup() {
 Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(g2,INPUT);
  pinMode(g3,INPUT);
  pinMode(g4,INPUT);
  pinMode(g5,INPUT);
  pinMode(g6,INPUT);
  pinMode(g7,INPUT);
  pinMode(g8,INPUT);
  pinMode(bup,INPUT);
  pinMode(bdn,INPUT);
  pinMode(s_up,OUTPUT);
  pinMode(s_dn,OUTPUT);
}
void scan_gear()
{
  if(digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH&&digitalRead(g7)==HIGH&&digitalRead(g8)==HIGH)
   gear=0;
   if(digitalRead(g3)==LOW&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH&&digitalRead(g7)==HIGH&&digitalRead(g8)==HIGH)
   gear=1;
   if(digitalRead(g3)==HIGH&&digitalRead(g4)==LOW&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH&&digitalRead(g7)==HIGH&&digitalRead(g8)==HIGH)
   gear=2;
   if(digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==LOW&&digitalRead(g6)==HIGH&&digitalRead(g7)==HIGH&&digitalRead(g8)==HIGH)
   gear=3;
   if(digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==LOW&&digitalRead(g7)==HIGH&&digitalRead(g8)==HIGH)
   gear=4;
   if(digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH&&digitalRead(g7)==LOW&&digitalRead(g8)==HIGH)
   gear=5;
   if(digitalRead(g3)==HIGH&&digitalRead(g4)==HIGH&&digitalRead(g5)==HIGH&&digitalRead(g6)==HIGH&&digitalRead(g7)==HIGH&&digitalRead(g8)==LOW)
   gear=6;
}
void loop() 
{
   digitalWrite(13,HIGH);
   bdn=digitalRead(gdn);
   bup=digitalRead(gup);   
   scan_gear();            //check gear
 if(bup != lbup)
      {
        if(bup==LOW)
        {
          digitalWrite(s_up,HIGH);
          delay(65);
          digitalWrite(s_up,LOW);
        }
        delay(16);
      }
      if(bdn != lbdn)
      {
        if(bdn==LOW)
        {
          digitalWrite(s_dn,HIGH);
          delay(65);
          digitalWrite(s_dn,LOW);
        }
        delay(16);
      }
       lbdn=bdn;
       lbup=bup;
       scan_gear();
if(lastgear!=gear)
    {
  Serial.print(gear);
    lastgear=gear;
    }
    digitalWrite(13,HIGH);
}
