// MPU-6050 Short Example Sketch
// By Arduino User JohnChi
// August 17, 2014
// Public Domain
#include<Wire.h>
const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ; // declare accellerometer and gyro variables
void setup(){
  Wire.begin(); // initiate i2c system
  Wire.beginTransmission(MPU_addr); // be sure we talk to our MPU vs some other device
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true); // done talking over to MPU device, for the moment
  Serial.begin(9600); // initialize serial port to 9600 bps so you can see your debug messages in Arduino IDE via debug channel
}
void loop(){ // main program loop
  unsigned int t1=millis();
  Wire.beginTransmission(MPU_addr); // get ready to talk to MPU again
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false); // done talking to MPU for the time being
  Wire.requestFrom(MPU_addr,6,true);  // request a total of 14 registers
  // all the fancy <<8| stuff is to bit shift the first 8 bits to
  // the left & combine it with the next 8 bits to form 16 bits
  AcX=Wire.read()<<8|Wire.read();  // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)    
  AcY=Wire.read()<<8|Wire.read();  // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
  AcZ=Wire.read()<<8|Wire.read();  // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
 
  // the above lines have gathered Accellerometer values for X, Y, Z

  Serial.print("AcX = "); Serial.println(AcX); // share accellerometer values over debug channel 
  Serial.print("AcY = "); Serial.println(AcY);
  Serial.print("AcZ = "); Serial.println(AcZ);
  delay(300);
  unsigned int t2=millis();
  Serial.println(t2-t1);
}

