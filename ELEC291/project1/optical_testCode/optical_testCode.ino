/*
read analog data from A0 and send to PC via Serial port
*/
int opticalPin1=1;
int opticalPin2=2;
int opticalPin3=3;
int opticalRead1 = 100;
int opticalRead2  ;
int opticalRead3;
void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
}

void loop() {
  // send the value of analog input 0:
  int saveForUse=opticalRead2;
  opticalRead1=analogRead(opticalPin1);//left
  opticalRead2=analogRead(opticalPin2);//middle
  opticalRead2=analogRead(opticalPin3);//right 
  Serial.println(opticalRead1);
  Serial.println(opticalRead2);
  while(
  if(opticalRead1>opticalRead3)
  {
     Serial.println("1 is greater");
  }else{
    Serial.println("2 is greater");
  }
  
if(opticalRead1 <320 && opticalRead2)
  {
    Serial.println("the car is on track ");
  } 
  else if(opticalRead  opticalRead )
  {
   
    Serial.println("black line detected");
  }
  else if(opticalRead > 320)
  {
    Serial.println("black line detected");
  }

  // wait a bit for the analog-to-digital converter
  // to stabilize after the last reading (min 2 milli sec):
  delay(2000); //2000=2 sec
}

