#include <SPI.h>
#include <stdlib.h>
#include <WiFi.h> // arduino wifi libnrary
#include <Twitter.h> //ardiono twitter library
#include <Wire.h>
int outputpin= 0;
 
char ssid[] = "Fnce259";  //
char pass[] = "paris149";  
char roomStatus[50];
char msg[50]="something happen in the house";

Twitter twitter("HqJInxj5AGTHV781lbEwtg3WG");
int alarmActive ;
int alarmStatus ;
int c;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  WiFi.begin(ssid, pass);
  Wire.begin(12);
  Wire.onReceive(receiveEvent);
  delay(10000);
  strcpy(msg, "something happend inside the house");
  if(alarmActive==1){
  strcpy(roomStatus,"room is armed");
  }else if(alarmActive == 0 && alarmStatus == 0){
  strcpy(roomStatus,"room is not armed");
  }else if(alarmStatus == 1){
  strcpy(roomStatus,"alarm is triggered");
  }
  strcat(msg,roomStatus);  
  Serial.println("connecting ...");
  if (twitter.post(msg)) {
    int status = twitter.wait(&Serial);
    if (status == 200) {
      Serial.println("OK.");
    } else {
      Serial.print("failed : code ");
      Serial.println(status);
    }
  } else {
    Serial.println("connection failed.");
  }
}
 
void loop()
{
}

void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
     c  = Wire.read(); // receive byte as an int
  
  
  Serial.println(c);
  if (c == 1){
   
    alarmActive = 1;
    
     
    
}  else if (c == 2) {
     
    alarmActive = 0;
    alarmStatus = 0;
  
  }
  else if (c== 3){
    
    alarmStatus = 1;
   
    
  //setup();
}
}
}
