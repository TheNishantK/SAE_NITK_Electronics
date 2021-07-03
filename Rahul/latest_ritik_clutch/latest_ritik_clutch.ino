
const int gup=9;
const int gdn=8;
const int c_sw=6;         //clutch slow
const int G1=10;
const int G2=11;
const int G3=12;
const int c_sw_ip=5;
const int c_ft_ip=4;

const int g_up_ip=3;
const int g_dn_ip=2;
const int dn = A0;
const int up = A1;

int clutch_button;
int bdn;
int bup;
int lbdn;
int lbup;
int gear,lastgear=8;

void setup() 
{

 Serial.begin(9600);
  pinMode(gup,INPUT);
  pinMode(gdn,INPUT);
  pinMode(c_sw,INPUT);
  pinMode(G1,INPUT);
  pinMode(G2,INPUT);
  pinMode(G3,INPUT);
  pinMode(up,INPUT);
  pinMode(dn,INPUT);
  pinMode(c_sw_ip,OUTPUT);
  pinMode(c_ft_ip,OUTPUT);
  pinMode(g_up_ip,OUTPUT);
  pinMode(g_dn_ip,OUTPUT);
digitalWrite(13,HIGH);
     
}

void scan_gear()
{
  if(digitalRead(G1)==LOW&&digitalRead(G2)==HIGH&&digitalRead(G3)==HIGH)
   gear=0;
   if(digitalRead(G1)==HIGH&&digitalRead(G2)==LOW&&digitalRead(G3)==HIGH)
   gear=1;
   if(digitalRead(G1)==LOW&&digitalRead(G2)==LOW&&digitalRead(G3)==HIGH)
   gear=2;
   if(digitalRead(G1)==HIGH&&digitalRead(G2)==HIGH&&digitalRead(G3)==LOW)
   gear=3;
   if(digitalRead(G1)==LOW&&digitalRead(G2)==HIGH&&digitalRead(G3)==LOW)
   gear=4;
   if(digitalRead(G1)==HIGH&&digitalRead(G2)==LOW&&digitalRead(G3)==LOW)
   gear=5;
   if(digitalRead(G1)==LOW&&digitalRead(G2)==LOW&&digitalRead(G3)==LOW)
   gear=6;
}


void loop() 
{

   clutch_button= digitalRead(c_sw);
   bdn=digitalRead(gdn);
   bup=digitalRead(gup);   
   scan_gear();            //check gear
//   lastgear = gear;

  if(clutch_button==LOW)
  {
    digitalWrite(c_sw_ip,HIGH);
    delay(20);
      while(clutch_button==LOW)
      {
                if(bup != lbup && bup==LOW)
                        {
                          while(analogRead(up)<=100)
                          {
                            digitalWrite(g_up_ip,HIGH);
                            delay(10);
                          }
                            digitalWrite(g_up_ip,LOW);
                        }
                if(bdn != lbdn && bdn==LOW)
                        {
                          while(analogRead(dn)<=100)
                          {
                            digitalWrite(g_dn_ip,HIGH);
                            delay(10);
                          }
                            digitalWrite(g_dn_ip,LOW);
                          }
        clutch_button= digitalRead(c_sw);
      
               lbdn=bdn;
               lbup=bup;
//               scan_gear();
//        if(gear!=lastgear)
//            {
//              Serial.print(gear);
//              lastgear=gear;
//            }
         }
   digitalWrite(g_up_ip,LOW);
   digitalWrite(g_dn_ip,HIGH);
   digitalWrite(c_sw_ip,LOW);
   }
   
  if(bup != lbup && gear!=6 && bup==LOW)
          {
              digitalWrite(c_ft_ip,HIGH);
              delay(25);
              while(analogRead(up)<=100)
              {
                digitalWrite(g_up_ip,HIGH);
                delay(10);
              }
              digitalWrite(g_up_ip,LOW);
              delay(25);
              digitalWrite(c_ft_ip,LOW);
          }
  if(bdn != lbdn && gear !=1 && bdn==LOW)
            {
              digitalWrite(c_ft_ip,HIGH);
              delay(25);
              while(analogRead(dn)<=100)
              {
                digitalWrite(g_dn_ip,HIGH);
                delay(10);
              }
              digitalWrite(g_dn_ip,LOW);
              delay(25);
              digitalWrite(c_ft_ip,LOW);
            }

       lbdn=bdn;
       lbup=bup;
       scan_gear();
    if(gear!=lastgear)
    {
      Serial.print(gear);
      lastgear=gear;
    }
}

