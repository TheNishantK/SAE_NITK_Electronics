byte N=7;
byte i;
byte gear[7]={2,3,4,5,6,7,8};
bool stat[7];
bool prestat[7];

void setup() {
Serial.begin(9600);
for(i=0;i<N;i++){
  pinMode(gear[i],INPUT);
}
}
void getstat(){
  for(i=0;i<N;i++){
    stat[i]=digitalRead(gear[i]);
  }
}

bool comparestat(){
  for(i=0;i<N;i++){
    if(stat[i]!=prestat[i]){
      return false;
    }
    else
    return true;
  }
}

void printstat(){
  for(i=0;i<N;i++){
    Serial.print(stat[i]);
    Serial.print("    ");
  }
  Serial.println("\n");
}



void loop() {
getstat();
printstat();
bool s;
s=comparestat();
if(s==false){
  printstat();
}
else{
  
}
for(i=0;i<7;i++){
  prestat[i]=stat[i];
}
}
