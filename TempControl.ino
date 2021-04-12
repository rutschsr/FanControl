#include <dht.h>

#include <Wire.h>




dht DHT; //defines name for the DHT sensor
#define DHT11_PIN 12 //Pin the DHT sensor is conneced to
#define MOTOR 10 //Defines motor pin
#define MOTOR2 11 //Defines Arduino interconnection pin

const int waitValue =6000; //easily modifiable wait value
void setup(){
  Serial.begin(9600); //serial enable
   
  pinMode(MOTOR, OUTPUT); //initializes Motor as output
  pinMode(MOTOR2, OUTPUT); //initializes Alarm Arduino interconnection as output
  
}
void loop(){
 
  digitalWrite(MOTOR, LOW);
  digitalWrite(MOTOR2, LOW);
  if((DHT.temperature*1.8+32.00)>=90 || DHT.humidity>=90){ //Turns alarm on if temperature or humidity is too high
    digitalWrite(MOTOR, HIGH);
    digitalWrite(MOTOR2, HIGH);
  }
  
  
  int chk = DHT.read11(DHT11_PIN),F,H,P; //initializes DHT 11 temperature system values
 
 

  Serial.println("Temp: "+String(numup(DHT.temperature*1.8+32.00))+String((char)223)+"F"); //prints information to serial monitor for debug
  Serial.println("H:"+ String(numup(DHT.humidity))+"% FAN:");
  Serial.println();
  delay(waitValue);
  
  
  
 
 
  }
  
  
  
  


int numup(float num){//rounds float numbers correctly
  int intpart =num;
  float decimalpart = num-intpart;
  decimalpart=decimalpart*1000;
  if(decimalpart<500){
    return num;
  }
  return num+1;  
}

int mspeed(float temp) {//sets motor speed based on temperature or humidity
 int ft = 0;
  if(temp <=70){
   ft=0;}
   else if(temp <=74){
    ft=25;
   }
   else if(temp <=90){
    int mt=temp-70;
    ft=mt*5;
  }
  else{
    ft=100;
  }
  return ft;
  }
  
