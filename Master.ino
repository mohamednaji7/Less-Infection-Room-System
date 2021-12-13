// C++ code
//MASTER
#include <Wire.h>
#define slaveAddress 1
#define tempRequest 1
#define distRequest 0x02
#define red 13
#define green 12
#define blue 11
#define motorPin1 6  // Pin 14 of L293
#define motorPin2 5  // Pin 10 of L293
#define peizo0o0o 2  
void setup()
{
  pinMode(peizo0o0o, OUTPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  Wire.begin();        // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}
void loop()
{
  //send a command(teamprature request)
  Wire.beginTransmission(slaveAddress);
  Wire.write(tempRequest);
  Wire.endTransmission();
  signed char temp;
  Wire.requestFrom(slaveAddress, 1);// request 1 bytes 
  while (Wire.available()) { 
    temp = Wire.read(); // receive a signed temp
  }
  if(temp<20){
    //blue alarm
    digitalWrite(blue, HIGH);
    digitalWrite(green, LOW);
    digitalWrite(red, LOW);
    
    //rotate anit-clockwise
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
    
  }else if(temp<=30){
    //gree alarm
    digitalWrite(blue, LOW);
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    //break
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  }else{
    //red alarm
    digitalWrite(blue, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    
    //rotate clockwise
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, HIGH);
  }
  
  //send a command(distance request)
  Wire.beginTransmission(slaveAddress);
  Wire.write(distRequest);
  Wire.endTransmission();
  byte dist;
  Wire.requestFrom(slaveAddress, 1);// request 1 bytes 
  while (Wire.available()) { 
    dist = Wire.read(); // receive a byte 
  }
  if(dist<2){
    digitalWrite(peizo0o0o, LOW);
  }else{
    digitalWrite(peizo0o0o, HIGH);
	Serial.println("Stay away !!"); // print the decimal 
  }
}

