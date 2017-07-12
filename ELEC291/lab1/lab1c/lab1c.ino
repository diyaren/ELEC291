


const int ledPin=13;//for the build-in LED
int i =0;
unsigned long previousMillis=0;
//digital pin 5 has a red cathode attached to it:
int redLed=5;
//digital pin 4 has a green cathode attached to it:
int greenLed=4;
//digital pin 3 has a blue cathode attached to it:
int blueLed=3;
//digital pin 9 has switch1 attached to it:
int switch1=9;
//digital pin 8 has switch2 attached to it:
int switch2=8;


void setup() {
//initialize serial communication at 9600 bits per second:
Serial.begin(9600);


pinMode(ledPin,OUTPUT);


//Make all the LEDs as outputs
pinMode(redLed,OUTPUT);
pinMode(greenLed,OUTPUT);
pinMode(blueLed,OUTPUT);

//set two switches as inputs
pinMode(switch1,INPUT);
pinMode(switch2,INPUT);
}


void loop() {
int switch1State=digitalRead(switch1);
int switch2State=digitalRead(switch2);

unsigned long currentMillis=millis();

if(currentMillis-previousMillis==200){
    previousMillis=currentMillis;
    i++;
    if(switch1State&&switch2State==0){
        
        digitalWrite(redLed,LOW);
        Serial.println("redLed=0");
        
        digitalWrite(greenLed,LOW);
        Serial.println("greenLed=0");
        
        digitalWrite(blueLed,LOW);
        Serial.println("blueLed=0");
        
       
     }
     if((i==5)&&(switch1State==0)&&(switch2State==1)){

           digitalWrite(redLed,HIGH);
           Serial.println("redLed=1");
           

           
      }
      
      if((i==10)&&(switch1State==0)&&(switch2State==1)){
               
            digitalWrite(redLed,HIGH);
            Serial.println("redLed=1");
               
            digitalWrite(blueLed,HIGH); 
            Serial.println("blueLed=1"); 
        }
       if((i==15)&&(switch1State==0)&&(switch2State==1)){
            digitalWrite(redLed,HIGH);
            Serial.println("redLed=1");
            
            digitalWrite(blueLed,HIGH);
            Serial.println("blueLed=1");
            
            digitalWrite(greenLed,HIGH);
            Serial.println("greenLed=1"); 
            i==0;
         }
//second patten     
       if((i==5)&&(switch1State==1)&&(switch2State==0)){
            digitalWrite(redLed,HIGH);
            Serial.println("redLed=1");
            
       }
       if((i==10)&&(switch1State==1)&&(switch2State==0)){
            digitalWrite(redLed,HIGH);
            Serial.println("redLed=1");
            
            digitalWrite(greenLed,HIGH);
            Serial.println("blueLed=1");
       }
       if((i==15)&&(switch1State==1)&&(switch2State==0)){
       
            digitalWrite(redLed,HIGH);
            Serial.println("redLed=1");
            
            digitalWrite(greenLed,HIGH);
            Serial.println("blueLed=1");
            
            digitalWrite(blueLed,HIGH);
            Serial.println("greenLed=1");
            i==0;
       }

 //third pattern 
 
       if((i==5)&&(switch1State==1)&&(switch2State==1)){
            digitalWrite(greenLed,HIGH);
            Serial.println("redLed=1");
            
       }
       if((i==10)&&(switch1State==1)&&(switch2State==1)){
            digitalWrite(greenLed,HIGH);
            Serial.println("redLed=1");
            
            digitalWrite(blueLed,HIGH);
            Serial.println("blueLed=1");
            
          
       }
       if((i==15)&&(switch1State==1)&&(switch2State==1)){
            digitalWrite(greenLed,HIGH);
            Serial.println("redLed=1");
            
            digitalWrite(blueLed,HIGH);
            Serial.println("blueLed=1");
            
            digitalWrite(redLed,HIGH);
            Serial.println("greenLed=1");
            i==0;
       }
       
            






}
}



