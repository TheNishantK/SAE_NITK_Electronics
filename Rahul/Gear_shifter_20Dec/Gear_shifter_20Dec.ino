const int up=9; //solenoid
const int dn=10;
int gear=-1,lastgear=-1;
const int  gup=11;// button
const int  gdn=12;

int g0=2;
int g1=3;
int g2=4;
int g3=5;
int g4=6;
int g5=7;
int g6=8;
int bdn;
int bup;
int lbdn;
int lbup;
char x='0',y='1';
int n_time=65;
int s_time=50;

void setup() {
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  pinMode(up,OUTPUT);
  pinMode(dn,OUTPUT);

  pinMode(gup,INPUT);
  pinMode(gdn,INPUT);
  pinMode(g0,INPUT);
  pinMode(g1,INPUT);
  pinMode(g2,INPUT);
  pinMode(g3,INPUT);
  pinMode(g4,INPUT);
  pinMode(g5,INPUT);
  pinMode(g6,INPUT);
  Serial.begin(115200);
  bdn=LOW;
  bup=LOW;
  lbdn=HIGH;
  lbup=HIGH;
}

void loop() 
{
   digitalWrite(13,HIGH);
   if(digitalRead(g1)==HIGH && digitalRead(g2)==HIGH && digitalRead(g3)==HIGH && digitalRead(g4)==HIGH && digitalRead(g5)==HIGH && digitalRead(g6)==HIGH) 
    { gear=0;
      Serial.print("0");
      bdn=digitalRead(gdn);
      bup=digitalRead(gup);
      if(bup != lbup)
      {
        if(bup==LOW)
        {
          digitalWrite(up,HIGH);
          delay(s_time);
          digitalWrite(up,LOW);
        }
        delay(16);
      }
      if(bdn != lbdn)
      {
        if(bdn==LOW)
        {
          digitalWrite(dn,HIGH);
          delay(n_time);
          digitalWrite(dn,LOW);
        }
        delay(16);
      }
                          lbdn=bdn;
          lbup=bup;
     
    }

       
    
    if(digitalRead(g1)==LOW)
    { gear=1;
      Serial.print("1");
      bdn=digitalRead(gdn);
      bup=digitalRead(gup);
      if(bup != lbup)
      {
        if(bup==LOW)
        {
          digitalWrite(up,HIGH);
          delay(n_time);
          digitalWrite(up,LOW);
        }
        delay(16);
        }
      if(bdn != lbdn)
      {
        if(bdn==LOW)
        {
          digitalWrite(dn,LOW);
          delay(s_time);
          digitalWrite(up,LOW);
        }
        delay(16);
      }
                lbdn=bdn;
          lbup=bup;

    }
    
    
    
    if(digitalRead(g2)==LOW)
    { gear=2;
      Serial.print("2");
      bdn=digitalRead(gdn);
      bup=digitalRead(gup);
      if(bup != lbup)
      {
        if(bup==LOW)
        {
          digitalWrite(up,HIGH);
          delay(n_time);
          digitalWrite(up,LOW);
        }
        delay(16);
     }
      if(bdn != lbdn)
      {   
        if(bdn==LOW)
        {
          digitalWrite(dn,HIGH);
          delay(s_time);
          digitalWrite(dn,LOW);
        }
        delay(16);
      }
          lbdn=bdn;
          lbup=bup;
  
  }
    
    
    
    if(digitalRead(g3)==LOW)
    { gear=3;
      Serial.print("3");
      bdn=digitalRead(gdn);
      bup=digitalRead(gup);
      if(bup != lbup)
      {
        if(bup==LOW)
        {
          digitalWrite(up,HIGH);
          delay(n_time);
          digitalWrite(up,LOW);
        }
        delay(16);
      }
      if(bdn != lbdn)
      {  
        if(bdn==LOW)
        {
          digitalWrite(dn,HIGH);
          delay(n_time);
          digitalWrite(dn,LOW);
        }
        delay(16);
      }
          lbdn=bdn;
          lbup=bup;      
    }

    
    
    
    if(digitalRead(g4)==LOW)
    { gear=4;
      Serial.print("4");
      bdn=digitalRead(gdn);
      bup=digitalRead(gup);
      if(bup != lbup)
      {
        if(bup==LOW)
        {
          digitalWrite(up,HIGH);
          delay(n_time);
          digitalWrite(up,LOW);
        }
        delay(16);
    }
      if(bdn != lbdn)
      {    
        if(bdn==LOW)
        {
          digitalWrite(dn,HIGH);
          delay(n_time);
          digitalWrite(dn,LOW);
        }
        delay(16);
      }
          lbdn=bdn;
          lbup=bup;
      
    }

    
    if(digitalRead(g5)==LOW)
    { gear=5;
      Serial.print("5");
      bdn=digitalRead(gdn);
      bup=digitalRead(gup);
      if(bup != lbup)
      {
        if(bup==LOW)
        {
          digitalWrite(up,HIGH);
          delay(n_time);
          digitalWrite(up,LOW);
        }
        delay(16);
     }
      if(bdn != lbdn)
      {   
        if(bdn==LOW)
        {
          digitalWrite(dn,HIGH);
          delay(n_time);
          digitalWrite(dn,LOW);
        }
        delay(16);
      }
          lbdn=bdn;
          lbup=bup;
      
    }

    
    
    
    if(digitalRead(g6)==LOW)
    { gear=6;
      Serial.print("6");
      bdn=digitalRead(gdn);
      bup=digitalRead(gup);
      if(bup != lbup)
      {
        if(bup==LOW)
        {
          digitalWrite(up,LOW);
          digitalWrite(dn,LOW);
        }
        delay(16);
     }
      if(bdn != lbdn)
      {   
        if(bdn==LOW)
           {
          digitalWrite(dn,HIGH);
          delay(n_time);
          digitalWrite(dn,LOW);
        }
        delay(16);
      }
          lbdn=bdn;
          lbup=bup;
        
    }
   /* if(lastgear!=gear)
    {
  Serial.print(gear);
    lastgear=gear;
    }*/
    
  digitalWrite(13,HIGH);
  
}
