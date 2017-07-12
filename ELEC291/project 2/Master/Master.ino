#include <Wire.h>
#include <LiquidCrystal.h>
#include <Password.h> 
#include <Keypad.h> 
#include <Servo.h> 

const byte ROWS = 4; // Four rows
const byte COLS = 3; // Four columns
int password_position=15;
volatile int receivedData;

//Password for active the system 
Password activePW= Password( "1234" );
//password for deactive the system
Password deactivePW = Password("1230");

byte rowPins[ROWS] = {
  8,7,6,5};     //connect to the row pinouts of the keypad
byte colPins[COLS] = {
  4,3,2};     //connect to the column pinouts of the keypad

char keys[ROWS][COLS] = { // Define the Keymap
  {
    '1','2','3'      }
  ,
  {
    '4','5','6'      }
  ,
  {
    '7','8','9'     }
  ,
  {
    '*','0','#'     }
};

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(A0,13,12,11,10,9); // Assignign arduino pins to LCD display module

void setup() {
Serial.begin(9600);
//lcd in place
lcd.begin(16,2);
//master address wire transmission address is 6
Wire.begin(6);
displayCodeEntryScreen();
keypad.addEventListener(keypadEvent);//running the keypadEvent all the way through
Wire.onReceive(receiveEvent);//receive message event 
}

void loop() {
//get key 
keypad.getKey();

}

//event for keypad
void keypadEvent(KeypadEvent anotherKey){
  switch (keypad.getState()){
    case PRESSED:
    if (password_position - 15 >= 5){
      return;
    }

    switch (anotherKey){ 
      //as finished signal of entering the password
      case '#':
        password_position = 15;
        checkPassword();
        break;
      //encode password  
      case '*':
        activePW.reset();
        deactivePW.reset();
        password_position = 15;
        break;
      
      default:
        activePW.append(anotherKey);
        deactivePW.append(anotherKey);
        lcd.print("*");
        
    }
  }


 
}

void checkPassword(){
  //if the password entered is active password 
   if(activePW.evaluate()==1){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("please leave");
   Wire.beginTransmission(8);
   Wire.write(1);
   Wire.endTransmission();
   Wire.beginTransmission(12);
   Wire.write(1);
   Wire.endTransmission();
   delay(15000);
   lcd.setCursor(0,1);
   lcd.print("system active");
   activePW.reset();
   
 
//if the password entered is deactive password   
   }else if(deactivePW.evaluate()==1){
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("System Deactive");
   //send 2 when the deactivate password is correct 
   lcd.setCursor(0,1);
   lcd.print("Alarm dead");
   delay(4000);
   displayCodeEntryScreen();
   //start transmitting to slave 1
   Wire.beginTransmission(8);
   Wire.write(2);
   Wire.endTransmission();
   //start transmitting to slave 2
   Wire.beginTransmission(12);
   Wire.write(2);
   Wire.endTransmission();
}else{
  //if password is not correct 
  invalidCode();
}
}

//when the code is invalid,call this function 
void invalidCode(){
  activePW.reset();
  deactivePW.reset();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Invalid code!");
  lcd.setCursor(0,1);
  lcd.print("Try again");
  delay(2000);
  //clean screen 
  displayCodeEntryScreen();
  
}

//screen refresh function 
void displayCodeEntryScreen(){
  lcd.clear();
  activePW.reset();
  deactivePW.reset();
  lcd.setCursor(0,0);
  lcd.print("Enter password");
  lcd.setCursor(0,1);
  lcd.print("PIN:");
 }



  
void receiveEvent(int howMany) {
while (Wire.available() > 0) { // loop through all but the last
    receivedData  = Wire.read(); // receive byte as an int
    Serial.println(receivedData);
    //receive message from hall effect sensor
    if(receivedData==1){
    
    checkPassword();
   
     //receive message from motion detector 
    }else if(receivedData==2){
    
    checkPassword();
  
    }
}
}








