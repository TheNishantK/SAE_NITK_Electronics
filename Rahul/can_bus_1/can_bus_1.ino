#include <SoftwareSerial.h>
#include <Canbus.h>
char buffer[512];  //Data will be temporarily stored to this buffer before being written to the file
char tempbuf[15];
char lat_str[14];
char lon_str[14];

int read_size=0;   //Used as an indicator for how many characters are read from the file
int count=0;       //Miscellaneous variable

int D10 = 10;

int LED2 = 8;
int LED3 = 7;
#define BUFFSIZ 90 // plenty big
//char buffer[BUFFSIZ];
char *parseptr;
char buffidx;
uint8_t groundspeed, trackangle;
char status;
uint32_t waypoint = 0;


 void setup()
 {
  pinMode(LED2, OUTPUT); 
  pinMode(LED3, OUTPUT); 
  digitalWrite(LED2, LOW);
   Serial.begin(9600);
  Serial.println("ECU Reader"); 
  Serial.println("CAN");
 
 delay(1000); 
 }
 void loop()
 {if(Canbus.init(CANSPEED_500))  /* Initialise MCP2515 CAN controller at the specified speed */
  {  Serial.println("CAN Init ok");Canbus.ecu_req(ENGINE_RPM,buffer);
 Serial.println(buffer);}
 else{
     Serial.println("Can't init CAN");
 return;}
 
 delay(1000);
 }

