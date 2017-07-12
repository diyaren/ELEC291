#include <Wire.h>
#include <Servo.h>
#include <Password.h> 
#include <LiquidCrystal.h>


int door1 = 5;
int Buzzer = 8;
int alarmStatus;
int alarmActive;
int motionDetect;

volatile int passwordState = 0 ;

void setup() { 
Wire.begin();
pinMode(Buzzer, OUTPUT);
Wire.onReceive(receiveEvent);
Serial.begin(9600);
}

void loop() {



}




void activate(){     // Activate the system if correct PIN entered and display message on the screen

  alarmActive = 1;
  //if door is open and the password entered is wrong 
   if((check()== HIGH && passwordState == 0)||(motionDetect==1 && passwordState == 1)){
   alarmTriggered();
   }
   delay(2000);
}
  else{
    deactivate();   // if PIN not corrected, run "deactivate" loop
  }
}



void deactivate()
{ 
  alarmStatus = 0;
  digitalWrite(Buzzer, LOW);
  alarmActive = 0;
  delay(5000);
  
  //signal the master board to clean the screen
  
}


void alarmTriggered(){
//buzzer 
while(passwordState == 0){
tone(Buzzer,123,1000);
alarmStatus = 1;
}
//send message to the master
}

int check(){
//Reading values from the pins
door1= digitalRead(5);
//testRight = digitalRead(4);

if (door1 == 1){
  Serial.println("door closed");
  return 1;
}

else {
  Serial.println("door open");
  //do stuff for open door here
  return 0;
}
}


// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany) {

  
   while (Wire.available() > 0) { // loop through all but the last
    int c  = Wire.read(); // receive byte as an int
    passwordState = c;
    Serial.println(passwordState);
  }
    if(passwordState==1){
      tone(Buzzer,200,1000);
    }else{
      Serial.print(passwordState); // print the character
    }

}





