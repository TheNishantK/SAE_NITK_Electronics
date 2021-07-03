int timer = 800;    
int U18 = 7;
int State = 0;         
int lastState = 0;     


boolean space[]={0,0,0,0,0};   
boolean A[]={1,1,1,1,1,1,0,1,0,0,1,0,1,0,0,1,1,1,1,1};
boolean U[]={1,1,1,1,1,0,0,0,0,1,0,0,0,0,1,1,1,1,1,1};
boolean T[]={1,0,0,0,0,1,1,1,1,1,1,0,0,0,0};
boolean O[]={1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,1,1,1};
boolean K[]={1,1,1,1,1,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1};
boolean R[]={1,1,1,1,1,1,0,1,0,0,1,0,1,0,0,1,1,0,1,1};
boolean I[]={1,0,0,0,1,1,1,1,1,1,1,0,0,0,1};
boolean nine[]={0,1,0,0,0,1,0,1,0,0,0,1,1,1,1};
boolean dot[]={0,0,0,0,1,0,0,0,0,1};
boolean zero[]={0,1,1,1,0,1,0,0,0,1,0,1,1,1,0};
int m;

void setup() {
  for (int Pin = 2; Pin <=6; Pin++) {
    pinMode(Pin, OUTPUT);}
  pinMode(U18, INPUT);
}

void loop() {
State = digitalRead(U18);
if (State != lastState){
  if (State == HIGH){
delayMicroseconds(5000);
WriteLetter4Width(A);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter4Width(U);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter3Width(T);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter4Width(O);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter4Width(K);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter4Width(R);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter3Width(I);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter3Width(T);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter3Width(I);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter3Width(nine);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter2Width(dot);
WriteLetter1Width(space);
WriteLetter1Width(space);
WriteLetter3Width(zero);
WriteLetter1Width(space);
WriteLetter1Width(space);
}}
lastState = State;
}

void WriteLetter4Width(boolean letter[]){
  m=0;
  for (int n=0; n<=3; n++){
  for (int Pin = 2; Pin <=6; Pin++) {
    digitalWrite(Pin, letter[m]);
    m=m+1;}
    delayMicroseconds(timer);}}

void WriteLetter3Width(boolean letter[]){
  m=0;
  for (int n=0; n<=2; n++){
  for (int Pin = 2; Pin <=6; Pin++) {
    digitalWrite(Pin, letter[m]);
    m=m+1;}
    delayMicroseconds(timer);}}

 void WriteLetter2Width(boolean letter[]){
  m=0;
  for (int n=0; n<=1; n++){
  for (int Pin = 2; Pin <=6; Pin++) {
    digitalWrite(Pin, letter[m]);
    m=m+1;}
    delayMicroseconds(timer);}}
 
 void WriteLetter1Width(boolean letter[]){
  m=0;
   for (int Pin = 2; Pin <=6; Pin++) {
    digitalWrite(Pin, space[m]);
    m=m+1;}
    delayMicroseconds(timer);}
  

