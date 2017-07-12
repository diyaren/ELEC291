const int ledPin=13;
int ledState=LOW;
unsigned long previousMillis=0;
const long timeInterval= 2000;
void setup() {
  // put your setup code here, to run once:
pinMode(ledPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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

}
