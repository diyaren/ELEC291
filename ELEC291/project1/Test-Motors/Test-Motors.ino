//Arduino PWM Speed Control：
int E1 = 5;  
int M1 = 4; 
int E2 = 6;                      
int M2 = 7;                        
 
void setup() 
{ 
    pinMode(M1, OUTPUT);   
    pinMode(M2, OUTPUT); 
} 
 
void loop() 
{ 
  int value;
  //move forward
  for(value = 0 ; value <= 255; value+=5) 
  { 
    digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    delay(30); 
  } 
   
  delay(1000);

  // move back
  for(value = 0 ; value <= 255; value+=5) 
  { 
    /*digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    delay(3000); */
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    delay(30);
  }  

  delay(1000);

  //stop
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0);   //PWM Speed Control
  analogWrite(E2, 0);   //PWM Speed Control
  delay(100);

  //Turn right
  for(value = 0 ; value <= 255; value+=5) 
  { 
    /*digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    delay(3000); */
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    delay(50);
  }  

  delay(50);

  //stop
  analogWrite(E1, 0);   //PWM Speed Control
  analogWrite(E2, 0);   //PWM Speed Control
  delay(50);

  //Turn left
  for(value = 0 ; value <= 255; value+=5) 
  { 
    /*digitalWrite(M1,HIGH);   
    digitalWrite(M2, HIGH);       
    analogWrite(E1, value);   //PWM Speed Control
    analogWrite(E2, value);   //PWM Speed Control
    delay(3000); */
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E2, value);   //PWM Speed Control
    analogWrite(E1, value);   //PWM Speed Control   
    delay(50);
  }  

  delay(50);
}

  

