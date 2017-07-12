/*
 * Project 1 Arduino Code
 * To Do (functionality #1):
 *  - motor speed control (ie. high speed and gradual slow down) 
 *  - motor direction control (straight line & turn)
 *  - servo motor control (180 degree rotation)
 *  - range finder sensor
 *  - temperature sensor
 *  - hall effect sensor
 *  - lcd display (display useful info)
 *  - switch (on/off)
 *  (+ hardware and wiring)
 *  
 *  Functionality #2?
 *  
 *  Working on:
 *  - copying code for range finder and temp sensor from lab5
 *  - setting up servo motor code (copying example)
 */

// Initialize pins (currently mostly arbitrary values)
const int servoPin = 9;

// Initialize servo object
Servo myservo;
int distance1;
int distance2;
// Declare variables
float tempC;    //temperature of room
float tempVolt;    //raw temp sensor data
float distance;    //calculated distance
float speedOfSound;   //calculated speed of sound
unsigned long interval;    //interval

void setup() {
  //Set up servo
  myservo.attach(servo_pin);
  myservo.write(90); //Set servo to midpoint

  // Set range finder pins to desired mode
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

}

void loop() {
  
  // distance to next object read using readSensor() function
  //distance = readRange();

}

//scan right and left, returns 1 if right is longest path, and 0 if left is longest path
//TO DO: check which 0/180 degrees is left or right
//       callibrate 0&180 degrees 
int scan(){
  distance1=0;
  for(pos = 90; pos>=0; pos-=1)// goes from 0 degrees to 90 degrees
  {                                
    
    myservo.write(pos);   // tell servo to go to position in variable 'pos' 
    distance1=distance1+readRange();
    
    delay(15); // waits 15ms for the servo to reach the position 

  }
   myservo.write(90);              
    delay(2000); //stops motor for 2 seconds   
  for(pos = 90; pos <=180; pos +=1) // goes from 90 degrees to 180 degrees 
  {                                  // in steps of 1 degree 
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    distance2=distance2+readRange(); 
    delay(15);      // waits 15ms for the servo to reach the position

  } 
  if(distance1>distance2){
    return 0;//turn left
    
  }else{
    return 1;//turn right 
  }
  
}

//read from the temp sensor and find the temperature of the room
float readTemp(){
  tempVolt = analogRead(tempSensor);
  tempC = ((tempVolt * 5.0 * 100) / 1024.0);
  return tempC;
}

//read from range sensor to find distance to objects
float readRange(){
    //Set trigger pin to low and then after a delay set it to high
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4);
  digitalWrite(trigPin, HIGH);
  // after delaying to ensure the trigger pin is HIGH long enough
  // to activate the echo pin set the trigger pin to LOW
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //set interval to the time to recieve a signal if it takes longer
  //than 38ms then no data is expected to be recieved
  interval = pulseIn(echoPin, HIGH, maxDuration);
  delayMicroseconds(40);

  // temperature read using readTemp() function
  tempC = readTemp();
  
  //calculate the speed of sound in m/s
  speedOfSound = 331.5 + (0.6 * tempC);

  //find the speed of sound in cm/us
  speedOfSound /= 10000;

  // find distance from the sensor to the object
  long dist = interval * (speedOfSound);
  dist /= 2;

  return dist;
}

