#include <dht.h>
#include <LiquidCrystal.h>
#include <Wire.h>
#include <Servo.h>

LiquidCrystal lcd(8, 12, 5, 4, 3, 2); //defines pins the LCD is connected to 

dht DHT; //defines name for the DHT sensor
#define DHT11_PIN 7 //Pin the DHT sensor is conneced to
#define MOTOR 6 //Defines motor pin
#define Alarmout 13 //Defines Arduino interconnection pin
#define TestPin A5 //pushbutton input pin
Servo servo1; //servo output pin
const int waitValue =500; //easily modifiable wait value
void setup(){
  Serial.begin(9600); //serial enable
   lcd.begin(16, 2); //initializes LCD screen
  pinMode(MOTOR, OUTPUT); //initializes Motor as output
  pinMode(Alarmout, OUTPUT); //initializes Alarm Arduino interconnection as output
  pinMode(TestPin, INPUT);  //Initializes pushbutton as input
  servo1.attach(9); //initializes servo
}
void loop(){
  lcd.setCursor(0,0); 
  int testADC=analogRead(TestPin); //reads pushbutton value
  digitalWrite(Alarmout, LOW); //alarm interconnect is naturally, normally low
  if(testADC<=100){ //runs program normally if pushbutton is not depressesd
  if((DHT.temperature*1.8+32.00)>=100 || DHT.humidity>=90){ //Turns alarm on if temperature or humidity is too high
    digitalWrite(Alarmout, HIGH);
    delay(100);
  }
  
  int chk = DHT.read11(DHT11_PIN),F,H,P; //initializes DHT 11 temperature system values
 

  int mpercent=0; //initializes fan motor speed to 0
  if(mspeed(DHT.temperature*1.8+32.00)>=mspeed(DHT.humidity)){ //sets motor speed to temperature or humidity dependent on which is calling for a faster speed
    mpercent=mspeed(DHT.temperature*1.8+32.00);
  }
  else {
    mpercent=mspeed(DHT.humidity);
  }
      lcd.print("Temp: "+String(numup(DHT.temperature*1.8+32.00))+String((char)223)+"F"); //prints temperature to LCD display
  
  lcd.setCursor(0,1); //sets LCD cursor to second line
  
 
 lcd.print("H:"+ String(numup(DHT.humidity))+"% FAN:" + String(mpercent)+ "%"); //prints humidity and fan speed percentage to LCD screen
  Serial.println("Temp: "+String(numup(DHT.temperature*1.8+32.00))+String((char)223)+"F"); //prints information to serial monitor for debug
  Serial.println("H:"+ String(numup(DHT.humidity))+"% FAN:" + String(mpercent)+ "%");
  Serial.println("TestPin " +String(testADC));
  Serial.println();
  delay(waitValue);
  lcd.clear(); //clears LCD to reduce print errors
  
  
  analogWrite(MOTOR,(2.55*mpercent)); //sets PWM motor speed
 
  if(mpercent!=0){//sets servo (damper) direction based on if motor is operating or not
    
    servo1.write(180);
    delay(100);
  }
  else{
   
    servo1.write(90);
    delay(100);
  }
  
  }
  else{//runs if pushbutton is depressed
    lcd.clear(); //clears LCD
    lcd.print("TEST MODE");//Prints Test Mode on first line of LCD
    lcd.setCursor(0,1); //sets cursor to second line
    lcd.print("FAN: 100%");//Prints fan speed to second line
    analogWrite(MOTOR, 255);//sets fan speed to 100%
    digitalWrite(Alarmout, HIGH);//sets alarm to on
    servo1.write(180);// opens damper
    delay(waitValue);
    lcd.clear();
  }
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
  
