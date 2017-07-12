#define echoPin 7
#define triggerPin 6

int tempSensorPin=A2;
int maximumRange=400;
int minimumRange=2;
float distance,speedOfSound;
float duration,convertSoundSpeed;

void setup() {

Serial.begin(9600);
pinMode(echoPin,INPUT);
pinMode(triggerPin,OUTPUT);

}

void loop() {
  
digitalWrite(triggerPin,LOW);
delayMicroseconds(3);
digitalWrite(triggerPin,HIGH);
delayMicroseconds(10);
digitalWrite(triggerPin,LOW);
duration=pulseIn(echoPin,HIGH);

int readTemSensor = analogRead(tempSensorPin);
//convert the value we read into voltage
float voltage=readTemSensor* 5.0;
voltage=voltage/1024.0;
//converts it into degrees Celsius and print out the temperature 
float tempC=voltage*100.0;
speedOfSound=331.5+(0.6*tempC);
float convertSoundSpeed=(1/speedOfSound)*10000;
Serial.print("the converted speed of sound:");
Serial.println(convertSoundSpeed);
distance=duration/(2*convertSoundSpeed);   //distance in cm

if(distance>=maximumRange||distance<=minimumRange){
Serial.println("out of range");

}
else{
  Serial.print(distance);
  Serial.println("cm");
  
}
delay(1000);
}
