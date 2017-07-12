/*
   Based on switch settings, chooses between 4 possible functionalities:
   1. Moves through a course at full speed until it senses an obstacle in its path.
   As it approaches obstacle, robot slows gradually until it comes to a complete stop
   about 15cm away. Then it scans left and right to determine the appropriate next path,
   and turns in that direction. Finally it continues it's forward motion at full speed.
   While in forward motion, hall effect sensors are used to measure frequency of rotation
   of the wheels and adjust speed to account for any discrepencies.

   2. Tracks a dark line on a lighter background using optical sensors. If robot happens to
   lose track of line, or line comes to an end, robot will turn counterclockwise until it
   senses line again.

   3. Additional servo lifts and lowers marker, which is then used to write a short message.
   Message reads ' Hi! '.

   4. Additional servo lifts and lowers marker, which is then used to draw a flower pattern
   composed of semi-circles.

   Last modified: Mar 8, 2016
   by Group 1 (Team 2C/3C)
*/

// Include servo library
#include <Servo.h>

// Initialize digital I/O pins (currently mostly arbitrary values)
const int servoPin = 8;
const int servo2Pin = 9;
const int echoPin = 13;
const int trigPin = 12;
const int hall1Pin = 11;
const int hall2Pin = 10;
//change switch pins!!!
const int switch1Pin = 2;
const int switch2Pin = 3;
// Initialize analog input pins
const int tempPin = 0;
const int leftSensor = 1;
const int centreSensor = 2;
const int rightSensor = 3;
// Initialize motor pins
const int E1 = 5;
const int M1 = 4;
const int E2 = 6;
const int M2 = 7;

// Initialize servo object
Servo mainServo;
Servo drawServo;

// Declare variables
int turn;     //direction of longest path
int value;     //speed of motors
int leftRead;   //left optical sensor
int centreRead; //centre optical sensor
int rightRead;  //right optical sensor
int switch1;    //state of switch for principle function 1 and 2
int switch2;    //state of switch for additional functionality
float tempC;    //temperature of room
float tempVolt;    //raw temp sensor data
float distance;    //calculated distance
float speedOfSound;   //calculated speed of sound
unsigned long interval;    //interval for range sensor
const unsigned long maxDuration =  38000;

//variables used for checking hall effect sensors and adjusting speed of individual motors
int valueLeft = 255;
int valueRight = 255;
int testLeft  = HIGH;
int testRight = HIGH;
long rotationLeft = 0;
long rotationRight = 0;
int left;
int right;
int speedDifference1;
int speedDifference2;
long firstMillis1;
long secondMillis1;
long firstMillis2;
long secondMillis2;

//variables uses for additional funcitonality
int totalMillis = 0;
int forwardTotal = 0;
int circleMillis2 = 0;
int circleMillis1 = 0;
int forwardMillis1;
int forwardMillis2 = 0;
int stopForward = 200;
int startTime =  0;
int endTime = 16000;

void setup() {
  //Set up servo
  mainServo.attach(servoPin);
  mainServo.write(90); //Set servo to midpoint

  // Set up servo for additional funtionality
  drawServo.attach(servo2Pin);
  drawServo.write(0);//Set servo to lift marker from ground

  //Set up serial monitor
  Serial.begin(9600);

  //Set motor pins as outputs
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  // Set range finder pins to desired mode
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Set switch pins as inputs
  pinMode(switch1Pin, INPUT);
  pinMode(switch2Pin, INPUT);

  //Set hall effect sensor pins as inputs
  pinMode(hall1Pin, INPUT);
  pinMode(hall2Pin, INPUT);

  delay(1000);
}

void loop() {
  //Read switch states
  switch1 = digitalRead(switch1Pin);
  switch2 = digitalRead(switch2Pin);

  if (switch2 == 1 && switch1 == 1) {
    //additional functionality (draw message: 'Hi!')
    drawH();
    drawi();
    drawExclamation();
    delay(10000);
  }
  else if (switch2 == 1 && switch1 == 0) {
    //additional functionality (draw flower design)
    drawCircles();
  }
  else if (switch2 == 0 && switch1 == 0) {
    //principle functionality #1
    rangeFinder();
  }
  else {
    //principle functionality #2
    lineTracker();
  }
}

//executes primary functionality 1: sensing and navigating around walls and obsticals
void rangeFinder() {
  //infinite loop to stay in this functionality
  //(in order to switch functionality turn robot off and adjust switches)
  while (1) {
    delay(100);
    // distance to next object read using readRange() function
    distance = readRange();

    Serial.println("functionality 1");
    Serial.println(distance);

    // while the distance to an object is greater than 90cm, move forward
    if (distance > 90)
      forward();
    // if the distance to an object is less than 15cm, stop robot
    else if (distance < 25) {
      stopMotors();
      delay(200);
      // turn servo to use range finder to scan left and right
      turn = scan();
      //if left has more space, turn left
      if (turn == 0) {
        turnLeft();
        //Serial.println("turning left");
      }
      //if right has more space, turn right
      else {
        turnRight();
        //Serial.println("turning right");
      }
    }
    // Otherwise if distance to object is between 15 and 40cm, slow robot down
    else
      slow(distance);
  }
}

//execute principle function 2: tracking a line with the robot
void lineTracker() {
  //infinite loop to stay in this functionality
  while (1) {
    // Reads values from the optical sensors
    leftRead = analogRead(leftSensor);
    centreRead = analogRead(centreSensor);
    rightRead = analogRead(rightSensor);

    // If centre sensor is reading black, move forwards
    if ((centreRead > 50 && centreRead < 300) /*&& (leftRead > 300) && (rightRead > 300)*/)
    {
      opticalForward();
    }

    /*
      // If all sensors read black, reverse
      else if ((centreRead > 50 && centreRead < 300) && (leftRead > 50 && leftRead < 300) && (rightRead > 50 && rightRead < 300)) {
      for (value = 0 ; value <= 200; value += 5)
      {
        digitalWrite(M1, LOW);
        digitalWrite(M2, LOW);
        analogWrite(E1, value);   //PWM Speed Control
        analogWrite(E2, value);   //PWM Speed Control
      }
      }
    */

    // If left sensor is reading black, turn left gradually
    else if (/*(centreRead > 300 ) &&*/ (leftRead > 50 && leftRead < 300)/* && (rightRead > 300)*/) {
      opticalLeft();
    }

    // If right sensor is reading black, turn right gradually
    else if (/*(centreRead > 300 ) && (leftRead > 300) && */(rightRead > 50 && rightRead < 300)) {
      opticalRight();
    }

    // Otherwise (if no sensors read black), turn left until sensors find a line again
    else {
      opticalLeft();
    }
  }
}

// Turns both motors on to move forwards for principle functionality #2
void opticalForward() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 255);   //PWM Speed Control
  analogWrite(E2, 255);   //PWM Speed Control
}

// Pivots robot counterclockwise until either centre or right optical sensor detects black line again
void opticalLeft() {
  value = 0; //set speed to 0 initially
  float left1 = analogRead(centreSensor); //read centre sensor

  //execute loop while centre sensor reads white
  while (!(left1 > 50 && left1 < 300)) {
    //if centre sensor reads black, set left1 to read centre sensor in order to exit loop
    if (analogRead(centreSensor) > 50 && analogRead(centreSensor) < 300)
      left1 = analogRead(centreSensor);
    //if right sensor reads black, set left1 to read right sensor in order to exit loop
    if (analogRead(rightSensor) > 50 && analogRead(rightSensor) < 300)
      left1 = analogRead(rightSensor);

    //turn motors to pivot left
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    //gradually increase speed of turn
    if (value <= 100) {
      value += 5;
    }
  }
}

// Pivots robot clockwise until either centre or left optical sensor detects black line again
void opticalRight() {
  value = 0; //set speed to 0 initially
  float right1 = analogRead(centreSensor); //read centre sensor

  //execute loop while centre sensor reads white
  while (!(right1 > 50 && right1 < 300)) {
    //if centre sensor reads black, set left1 to read centre sensor in order to exit loop
    if (analogRead(centreSensor) > 50 && analogRead(centreSensor) < 300)
      right1 = analogRead(centreSensor);
    //if left sensor reads black, set left1 to read right sensor in order to exit loop
    if (analogRead(leftSensor) > 50 && analogRead(leftSensor) < 300)
      right1 = analogRead(leftSensor);

    //turn motors to pivot right
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    //gradually increase speed of turn
    if (value <= 100) {
      value += 5;
    }
  }
}

//slows down motors gradually as it approaches an object (based on range finder data)
void slow(float dist) {
  //full speed at 90cm away and stop at 15cm away
  value = 255 - (3.3 * (95 - dist));
  //if distance is less than 15 and value is negative, make value 0
  if (value < 0)
    value = 0;
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, value);   //PWM Speed Control
  analogWrite(E2, value);   //PWM Speed Control
  delay(30);
}

//turns both motors on and to high, causing robot to move forward
void forward() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, valueLeft);   //PWM Speed Control
  analogWrite(E2, valueRight);   //PWM Speed Control

  //Serial.println("forward");
  check();
}

//turns both motors on and to low, causing robot to move forward
void reverse() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 225);   //PWM Speed Control
  analogWrite(E2, 225);   //PWM Speed Control
  delay(30);
}

//stops motors and causes robot to stop its motion
void stopMotors() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 0);   //PWM Speed Control
  analogWrite(E2, 0);   //PWM Speed Control
}

// pivots robot in a 90 degree turn to the right
void turnRight() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 120);   //PWM Speed Control
  analogWrite(E2, 120);   //PWM Speed Control
  delay(550);

  //reinitialize speed to max values for forward motion
  valueLeft = 255;
  valueRight = 255;
}

// pivots robot in a 90 degree turn to the left
void turnLeft() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 120);   //PWM Speed Control
  analogWrite(E2, 120);   //PWM Speed Control
  delay(550);

  //reinitialize speed to max values for forward motion
  valueLeft = 255;
  valueRight = 255;
}

//scan right and left, returns 1 if right is longest path, and 0 if left is longest path
int scan() {
  float distance1 = 0;
  float distance2 = 0;

  for (int pos = 90; pos >= 0; pos -= 1) // goes from 0 degrees to 90 degrees
  {
    mainServo.write(pos);   // tell servo to go to position in variable 'pos'
    distance1 = distance1 + readRange();

    delay(5); // waits 50ms for the servo to reach the position
  }

  mainServo.write(90);
  delay(1000); //stops motor for 1 second

  for (int pos = 90; pos <= 180; pos += 1) // goes from 90 degrees to 180 degrees
  { // in steps of 1 degree
    mainServo.write(pos);              // tell servo to go to position in variable 'pos'
    distance2 = distance2 + readRange();
    delay(5);      // waits 50ms for the servo to reach the position
  }

  mainServo.write(90);
  if (distance1 > distance2) {
    return 0;//turn right
  }
  else {
    return 1;//turn left
  }
}

//read from the temp sensor and find the temperature of the room
float readTemp() {
  tempVolt = analogRead(tempPin);
  tempC = ((tempVolt * 5.0 * 100) / 1024.0); // converts temperature voltage to degrees Celsius
  return tempC;
}

//read from range sensor to find distance to objects
float readRange() {
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
  interval = pulseIn(echoPin, HIGH);
  delayMicroseconds(40);

  // temperature read using readTemp() function
  tempC = readTemp();

  //calculate the speed of sound in m/s
  speedOfSound = 331.5 + (0.6 * tempC);


  //find the speed of sound in cm/us
  speedOfSound /= 10000;

  // find distance from the sensor to the object
  float dist = interval * (speedOfSound);
  dist /= 2;

  return dist;
}

// Function check starts
void check() {
  //Reading values from the pins
  testLeft = digitalRead(10);
  testRight = digitalRead(11);

  //Printing values on Serial Monitor
  Serial.print(testLeft);
  Serial.print("    ");
  Serial.println(testRight);

  //Assgins maximum speed in value goes less then 255
  if (valueLeft <= 200 || valueRight <= 200 ) {
    valueLeft = 255;
    valueRight = 255;
  }

  //Assigns testLeft to be value 1
  testLeft = 1;

  //Stalling
  if (testLeft == 1) {
    while (testLeft == 1) {
      testLeft = digitalRead(10);
    }
  }

  //Debouncing
  if (testLeft == 0) {
    while (testLeft == 0) {
      testLeft = digitalRead(10);
    }

    //Reads first time stamp
    firstMillis1 = millis();

    //Waits until it completes the rotation
    while (testLeft == 1) {
      delay(50);
      testLeft = digitalRead(10);
    }
    //Reads second time stamp
    secondMillis1 = millis();

    //Computes the time for 1 rotation
    Serial.print("Left Value");
    rotationLeft = secondMillis1 - firstMillis1;
    left = (int)rotationLeft;
    Serial.println("  ");
    Serial.print(left);
  }

  //Stalling
  if (testRight == 1) {
    while (testRight == 1) {
      testRight = digitalRead(11);
    }
  }

  //Debouncing
  if (testRight == 0) {
    while (testRight == 0) {
      testRight = digitalRead(11);
    }

    //Reads the second time stamp
    firstMillis2 = millis();

    //Waits for the rotation to complete
    while (testRight == 1) {
      delay(50);
      testRight = digitalRead(11);
    }

    // Reads the second time stamp
    secondMillis2 = millis();
    Serial.print("Right");
    // Computes the time for a rotation
    rotationRight = secondMillis2 - firstMillis2;
    right = (int) rotationRight;
    Serial.print("  ");
    Serial.println(right);
  }

  //Conditions to select only accurate values
  if ((left <= 400 || left >= 600) || (right <= 400 || right >= 600) ) {
    ;
  }

  //Computes the value for the speed to get equal rotations
  else {
    if (abs(left - right) >= 100) {
      if (left > right) {
        valueLeft = valueLeft - 1;
      }
      else {
        valueRight = valueRight - 1;
      }
    }
    //Write speed and changes to serial monitor for testing
    Serial.print(valueRight);
    Serial.print("  CHECKS  ");
    Serial.println(valueLeft);

    Serial.print(left);
    Serial.print("  COMPARES  ");
    Serial.println(right);
    Serial.println();

  }
}

/*
 * Code for additional functionality: Writing the message 'Hi!' and drawing a flower pattern
 */

//draw the letter 'H'
void drawH() {
  drawServo.write(90); //lower servo with pen
  drawStraight(1000, 1);
  drawServo.write(0); //lift pen
  drawStraight(500, 0);
  drawRight();
  drawStraight(150, 1);
  drawServo.write(90); //lower pen
  drawStraight(250, 1);
  drawLeft();
  drawStraight(400, 1);
  drawServo.write(95); //adjust pen position for drawing when reversing
  drawStraight(1200, 0);
  drawServo.write(0); //lift pen

  //move to start position for next character
  drawRight();
  drawStraight(500, 1);
  drawLeft();
  stopMotors();
}

//Draw letter 'i'
void drawi() {
  drawServo.write(90); //lower pen
  delay(100); //allow time for pen to move to position before drawing line
  drawStraight(500, 1);
  drawServo.write(0); //lift pen
  delay(100);
  drawStraight(100, 1);
  drawServo.write(90); //lower pen
  delay(500);
  drawServo.write(0); //lift pen
  drawStraight(600, 0);

  //move to start position for next character
  drawRight();
  drawStraight(200, 1);
  drawLeft();
  stopMotors();
}

//Draw symbol '!'
void drawExclamation() {
  drawServo.write(90); //lower pen
  delay(500);
  drawServo.write(0); //lift pen
  delay(100);
  drawStraight(150, 1);
  drawServo.write(90); //lower pen
  delay(100);
  drawStraight(850, 1);
  drawServo.write(0); //lift pen
  drawStraight(1000, 0);

  //move robot out of the way to the right so message is clearly visible, then stop all motion
  drawRight();
  drawStraight(3000, 1);
  drawLeft();
  stopMotors();
}

/*Draws a straight line for a given distance
  input: timer - determines distance robot travels and
        forOrBack - determines direction of motion, 1 is forward and 0 is backward
*/
void  drawStraight(int timer, int forOrBack) {
  if (forOrBack == 1) { //forward mode
    long startTime = millis(); //get the timer start time
    //Serial.println(startTime);

    //move the desired distance
    while ((millis() - startTime ) < timer) {
      //Serial.print("check time: ");
      //Serial.println(millis());
      drawForward();
    }
  }

  else if (forOrBack == 0) { //backward mode
    long startTime = millis(); //get the timer start time
    //move the desired distance
    while ((millis() - startTime) < timer) {
      drawReverse();
    }
  }

  //after desired distance has been travelled, stop motors
  stopMotors();
}

//Execute a 90 degree turn to the left with right wheel stationary 
// (so pen remains relatively stationary)
void drawLeft() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 120);   //PWM Speed Control
  analogWrite(E2, 0);   //PWM Speed Control
  delay(1300);
}

//Execute a 90 degree turn to the right with right wheel stationary 
// (so pen remains relatively stationary)
void drawRight() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 120);   //PWM Speed Control
  analogWrite(E2, 0);   //PWM Speed Control
  delay(1100);
}

//Move forward at a medium speed
void drawForward() {
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  analogWrite(E1, 100);   //PWM Speed Control
  analogWrite(E2, 100);   //PWM Speed Control
}

//Move backwards at a medium speed
void drawReverse() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 100);   //PWM Speed Control
  analogWrite(E2, 100);   //PWM Speed Control
}

//Additional functionality: Draw a flower pattern composed of a series of semi-circles
void drawCircles() {
  // draw (execute loop) for 16 seconds
  endTime =  millis() + 16000;
  while (millis() < endTime )
  {
    //get current time
    circleMillis1 = (int)millis();

    drawServo.write(90); //lower pen
    //draw for the duration of a second
    totalMillis = 0;
    while ( totalMillis <=  1000  )  {
      //execute pivot turn at medium speed, while drawing petal (semi-circle)
      digitalWrite(M1, LOW);
      digitalWrite(M2, HIGH);
      analogWrite(E1, 200);   //PWM Speed Control
      analogWrite(E2, 200);   //PWM Speed Control
      //get time elapsed since beginning of circle pattern
      circleMillis2 = (int)millis();
      totalMillis  = circleMillis2 - circleMillis1;
      //Serial.println(totalMillis);
    }

    //Serial.print("Entering Forward");
    drawServo.write(0); //lift pen
    delay(200);
    forwardMillis1 = (int)millis(); //get current time
    forwardTotal = 0;
    //execute forward motion for a given period of time starting at 200 milliseconds
    while ( forwardTotal <= stopForward ) {
      //move forwards at medium speed
      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);
      analogWrite(E1, 200);   //PWM Speed Control
      analogWrite(E2, 200);   //PWM Speed Control
      //get time elapsed since beginning of forward motion
      forwardMillis2 = (int)millis();
      forwardTotal  = forwardMillis2 - forwardMillis1;

      //Serial.println(forwardTotal);
    }
    //Serial.print("I m done");
    //slowly increase length of forward motion, 
    //    (therby increasing distance of petals from centre of circle)
    stopForward = stopForward + 20;

  }

  //after 16 seconds have elapsed, stop motors indefinitely
  while(1){
  stopMotors();
  }
}

