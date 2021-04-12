
#define LCD_Backlight 9
#define tonepin 6

const int LIGHT_PIN = A0;         //Defines photocell pin
const int AlarmPin =A5;           //Defines Alarm input pin from optocoulper
const int Speaker = 10;           //Defines Pizeo Speaker Pin
const float DARK_THRESHOLD = 10;  
const int DARK = 120;
const int LIGHT =255;

int buttonState =0;
int whichSensor;

void setup(){
  Serial.begin(9600);
  pinMode(LIGHT_PIN, INPUT);
  pinMode(AlarmPin, INPUT);  
}

void loop(){
  int LIGHTVALUE = 255;  //initialized backlight value (100% dark)
  int light_ADC = analogRead(LIGHT_PIN);  //Reads Analog Value from photocell Voltage divider input
  int Alarm_ADC = analogRead(AlarmPin);   //Reads Analog input value from optocoulper
    Serial.println("LightValue: "+ String(light_ADC)); //Serial print for programming and Debug purposes
    Serial.println((255-light_ADC));
    Serial.println("AlarmPin: "+String(Alarm_ADC));
    if(Alarm_ADC>=100){ //turns on alarm essentially if it is digital HIGH except its connect to an analog input
      tone(tonepin, 300);// plays alarm tone
      Serial.println(1);//debug serial text
    }
    else{
      Serial.println(2);//debug serial text
      noTone(tonepin); //stops alarm sound
      
    }
 
analogWrite(LCD_Backlight,(255-light_ADC)); //sets PWM output for LCD backlight based on the photocell input

delay(500);
} 
