const int ledPin=13;//for the build-in LED
//initialize the state of build-in LED:
int ledState=LOW;
unsigned long previousMillis=0;
//timer:
const long timeInterval= 2000;
//digital pin 3 has a red cathode attached to it:
int redLed=3;
//digital pin 4 has a green cathode attached to it:
int greenLed=4;
//digital pin 5 has a blue cathode attached to it:
int blueLed=5;
void setup() {
//initialize serial communication at 9600 bits per second:
Serial.begin(9600);
//Make all the LEDs as outputs
pinMode(ledPin,OUTPUT);
pinMode(redLed,OUTPUT);
pinMode(greenLed,OUTPUT);
pinMode(blueLed,OUTPUT);
}

void loop() {
digitalWrite(redLed,LOW);
delay(1000);
digitalWrite(blueLed,LOW);
delay(1000);
digitalWrite(greenLed,LOW);
delay(1000);
unsigned long currentMillis=millis();
if(currentMillis- previousMillis>= timeInterval){
 previousMillis=currentMillis;
 if(ledState==LOW){
  ledState=HIGH;
 }else{
  ledState=LOW;
 }
digitalWrite(ledPin,ledState);
}
digitalWrite(redLed,HIGH);
delay(1000);
digitalWrite(blueLed,HIGH);
delay(1000);
digitalWrite(greenLed,HIGH);
delay(1000);
}
