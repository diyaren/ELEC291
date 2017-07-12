int wordPerMin = 0;
int incomeByte = 0;
int dotDuration = 0;
int ledPin = 13;
int i = 0;
char* characters[] = {
  ".-"     //A
  "-..."   //b
  " -.-."  //C
  "-.."    //D
  "."      //E
  "..-."   //F
  "--."    //G
  "...."   //H
  ".."     //I
  ".---"   //J
  "-.-"    //K
  ".-.."   //L
  "--"     //M
  "-."     //N
  "---"    //O
  ".--."   //P
  "--.-"   //Q
  ".-."    //R
  "..."    //S
  "-"      //T
  "..-"    //U
  "...-"   //V
  ".--"    //W
  "-..-"   //X
  "-.--"   //Y
  "--.."   //Z
};

char* digits[] = {
  "-----"  //0
  ".----"  //1
  "..---"  //2
  "...--"  //3
  "....-"  //4
  "....."  //5
  "-...."  //6
  "--..."  //7
  "---.."  //8
  "----."  //9
};

void setup() {

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  Serial.print("Please enter your desired WPM.");
  if (Serial.available()>0) {
    wordPerMin = Serial.read();
    dotDuration = 1200 / wordPerMin;
    Serial.print("The dot duration is: ");
    Serial.println(dotDuration, DEC);
  }
  delay(2000);
  Serial.print("please enter the massage.");
  //when there is infomation show up on the serial monitor
  //for (Serial.available() > 0; i >= Serial.available(); i++) {
  // String massage=Srial
    for(Serial.read()==String string;i>=string.length();i++){
  //char message = Serial.read(); //read the character
       
    Serial.print(message);
    if (message >= 'a' && message <= 'z') //based on the decoding rule of ASCII
    {
      codingMethod(characters[massage - 'a']);
    }
    else if (message >= 'A' && message <= 'Z')
    {
      codingMethod(characters[message - 'A']);
    }
    else if (message >= '0' && message <= '9')
    {
      codingMethod(digits[message - '0']);
    }
    else if (message == ' ')
    {
      delay(dotDuration * 7);
    }
  }
}

void codingMethod(char* sequence)
{
  int n = 0;
  while (sequence[n] != NULL)
  {
    getNotation(sequence[n]);
    n++;
  }
  delay(dotDuration * 3);
}

void getNotation(char dotOrDash)
{
  digitalWrite(ledPin, HIGH);
  if (dotOrDash == '-')
  {
    delay(dotDuration * 3);
  } else {
    delay(dotDuration);
  }
  digitalWrite(ledPin, LOW);
  delay(dotDuration);
}


