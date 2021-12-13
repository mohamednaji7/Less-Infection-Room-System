// C++ code
// SLAVE
#include <Wire.h>
#define slaveAddress 1
#define tempRequest 0x01
#define distRequest 0x02
#define distPin 7
int tempPin = A0;
byte CMD;
 
void setup()
{
  Serial.begin(9600);
  Wire.begin(slaveAddress); // join i2c bus with address 
  Wire.onRequest(requestEvent); // register event
  Wire.onReceive(receiveEvent); // receive event  

}

void loop()
{
}



long readUltrasonicDistanceInMeteres(int Pin)
{
  pinMode(Pin, OUTPUT);  // Clear the trigger
  digitalWrite(Pin, LOW);
  delayMicroseconds(2);
  // Sets the trigger pin to HIGH state for 10 microseconds
  digitalWrite(Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Pin, LOW);
  pinMode(Pin, INPUT);
  // Reads the echo pin, and returns the sound wave travel time in microseconds
  // measure the ping time in m
  return 0.01723 * pulseIn(Pin, HIGH) / 100;
}
float getTemperature(int Pin){
  // temp in celcius 
  float temp = analogRead(Pin)*0.004882814;
  temp =(temp-0.5)*100;
  return temp;
}
float roudTmp(float d){
  int pol = -1; 
  if(d>0){
    pol = 1;
  }
  return floor(d + 0.5*pol);
}
void receiveEvent(int n){
  // to know what the master want 
  if(Wire.available()>0){
  	CMD = Wire.read();
  }
}
void requestEvent() {
  float data;
  if(CMD == tempRequest){
    // temp in range -40 to 125
    data = getTemperature(tempPin);
    data = roudTmp(data); 
  }else if(CMD == distRequest){
    //distance in range 0 to 3/more meters 
    data = readUltrasonicDistanceInMeteres(distPin);
  }else{
    return;
  }
  byte x = data;
  Wire.write(x); // respond with message of 1 byte(s)
  // as expected by master
}
