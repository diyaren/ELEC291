
#include <Wire.h>
int Buzzer = 3;
volatile int passwordState = 0 ;


void setup() {
Wire.begin(8);
pinMode(Buzzer, OUTPUT);
Wire.onReceive(receiveEvent);
Serial.begin(9600);


}

void loop() {


}

void receiveEvent(int howMany) {
  Serial.println("get here");
  while (Wire.available() > 0) { // loop through all but the last
    int c  =Wire.read(); // receive byte as a character
    passwordState = c;
    Serial.println(passwordState);
  }
    if(passwordState==1){
        Serial.print("get here 2");
      tone(Buzzer,200,1000);
    }else{
      Serial.print(passwordState); // print the character
    }

}

