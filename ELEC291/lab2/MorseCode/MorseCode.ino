int wordPerMin = 0;
int incomeByte = 0;
int dotDuration = 0;
int ledPin = 13;
int buzzPin = 11;
int segLed4 = 3; 
int segLed3 = 4; 
int segLed2 = 5; 
int segLed10 = 10; 
int segLed9 = 9; 
int segLed8 = 7; 
int segLed7 = 8; 
int segLedP = 6;

//A-Z(0-25), '.'(26), ','(27), ':'(28), '-'(29)
char* characters[] = {".-p", "-...p", "-.-.p", "-..p", ".p", "..-.p", "--.p", "....p", "..p", ".---p", "-.-p", ".-..p", "--p", "-.p", "---p", ".--.p", "--.-p", 
".-.p", "...p", "-p", "..-p", "...-p", ".--p", "-..-p", "-.--p", "--..p", ".-.-.-p", "--..--p", "---...p", "-....-p"};

char* digits[] = {"-----p", ".----p", "..---p", "...--p", "....-p", ".....p", "-....p", "--...p", "---..p", "----.p"};
void setup() {

  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(ledPin, OUTPUT); 
  pinMode(buzzPin, OUTPUT);
  pinMode(segLed4, OUTPUT);
  pinMode(segLed3, OUTPUT);
  pinMode(segLed2, OUTPUT);
  pinMode(segLed10, OUTPUT);
  pinMode(segLed9, OUTPUT);
  pinMode(segLed8, OUTPUT);
  pinMode(segLed7, OUTPUT);
  pinMode(segLedP, OUTPUT);
}

void loop() {
    ledDisplay('$');
    delay(2000);
    //Serial.print('\n');
    //Serial.print('\n');
    Serial.print("Please enter your desired WPM:");
    while (Serial.available()==0) {}
    wordPerMin = Serial.parseInt();
    Serial.println(wordPerMin);
    dotDuration = 1200 /2 wordPerMin;
    Serial.print("The dot duration is: ");
    Serial.println(dotDuration, DEC);
    Serial.print("\n");
    
    Serial.println("Please enter the message: ");
    while (Serial.available() == 0){}
    String string = Serial.readString();
    Serial.println(string);
    Serial.print("\n");
    
    int q = 0;
    char m = string[q];
    while(m != '\0'){
      m = string[q];
      q++;
    }
    
    for(int i = 0; i <= q; i++){
        char message = string[i];
        Serial.print(message);
        ledDisplay('$');
        ledDisplay(message);
             
             if (message >= 'a' && message <= 'z') //based on the decoding rule of ASCII
             {
                 codingMethod(message-'a');
             }
             else if (message >= 'A' && message <= 'Z')
             {
                 codingMethod(message-'A');
             }
             else if (message >= '0' && message <= '9')
             {
                 codingMethod(message-'0');
             }
             else if (message == ' ')
             {
                 delay(dotDuration * 7);
             }
             else if (message == '.'){
                 codingMethod(26);
             }
             else if (message == ','){
                 codingMethod(27);
             }
             else if (message == ':'){
                 codingMethod(28);
             }
             else if (message == '-'){
                 codingMethod(29);
             }
             else if (message == '*'){
               for(int l = 0; l < 8; l++){
                 getNotation('.');
               }
             }
       }
  }


void codingMethod(int index)
{
  int n = 0;
  while ( *(characters[index]+n) != 'p')
  {
    getNotation(*(characters[index]+n));
    n++;
  }
  delay(dotDuration * 3);
}

void getNotation(char dotOrDash)
{
  digitalWrite(ledPin, HIGH);
  if (dotOrDash == '-')
  {
    tone(buzzPin, 50);
    delay(dotDuration * 3);
    noTone(buzzPin);
  } else {
    tone(buzzPin, 50);
    delay(dotDuration);
    noTone(buzzPin);
  }
  digitalWrite(ledPin, LOW);
  delay(dotDuration);
}

void ledDisplay(char letter)
{ 
       if (letter == 'a' || letter == 'A')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed9, LOW);
	}
	else if (letter == 'b' || letter == 'B')
	{
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed10, LOW);
	}
	else if (letter == 'c' || letter == 'C')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed10, LOW);
	}
	else if (letter == 'd' || letter == 'D')
	{
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed10, LOW);
	}
	else if (letter == 'e' || letter == 'E')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed10, LOW);
	}
	else if (letter == 'f' || letter == 'F')
	{
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed7, LOW);
	}
	else if (letter == 'g' || letter == 'G')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed10, LOW);
	}
	else if (letter == 'h' || letter == 'H')
	{
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed2, LOW);
	}
	else if (letter == 'i' || letter == 'I')
	{
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed9, LOW);
	}
	else if (letter == 'j' || letter == 'J')
	{
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed10, LOW);
		digitalWrite(segLed9, LOW);
	}
	else if (letter == 'k' || letter == 'K')
	{
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed2, LOW);
	}
	else if (letter == 'l' || letter == 'L')
	{
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed10, LOW);
		digitalWrite(segLed9, LOW);
	}
	else if (letter == 'm' || letter == 'M')
	{
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed4, LOW);
	}
	else if (letter == 'n' || letter == 'N')
	{
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed2, LOW);
	}
	else if (letter == '1')
	{
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed2, LOW);
	}
	else if (letter=='y' || letter == 'Y')
	{
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed7,LOW);
     digitalWrite(segLed3,LOW);
     digitalWrite(segLed2,LOW);
     digitalWrite(segLed10,LOW);
	}
	else if(letter=='x'|| letter == 'X')
	{
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed9,LOW);
     digitalWrite(segLed7,LOW);
     digitalWrite(segLed3,LOW);
     digitalWrite(segLed2,LOW);
	}
	else if(letter=='w' || letter == 'W')
	{
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed3,LOW);
     digitalWrite(segLed10,LOW);
	}
	else if(letter=='v' || letter == 'V')
	{
     digitalWrite(segLed9,LOW);
     digitalWrite(segLed10,LOW);
     digitalWrite(segLed2,LOW);
	}
	else if(letter=='u' || letter == 'U')
	{
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed9,LOW);
     digitalWrite(segLed10,LOW);
     digitalWrite(segLed2,LOW);
     digitalWrite(segLed3,LOW);
	}
	else if(letter=='t' || letter == 'T')
	{
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed9,LOW);
     digitalWrite(segLed10,LOW);
     digitalWrite(segLed7,LOW);
     
	}
	else if(letter=='s' || letter == 'S')
	{
     digitalWrite(segLed4,LOW);
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed2,LOW);
     digitalWrite(segLed7,LOW);
     digitalWrite(segLed10,LOW);
	}
	else if(letter=='r' || letter == 'R')
	{
     digitalWrite(segLed9,LOW);
     digitalWrite(segLed7,LOW);
    
	}
	else if(letter=='q' || letter == 'Q')
	{
     digitalWrite(segLed3,LOW);
     digitalWrite(segLed2,LOW);
     digitalWrite(segLed4,LOW);
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed7,LOW);
	}
	else if(letter=='p' || letter == 'P')
	{
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed9,LOW);
     digitalWrite(segLed4,LOW);
     digitalWrite(segLed3,LOW);
     digitalWrite(segLed7,LOW);
	}
	else if(letter=='o' || letter == 'O')
	{
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed4,LOW);
     digitalWrite(segLed3,LOW);
     digitalWrite(segLed2,LOW);
     digitalWrite(segLed10,LOW);
     digitalWrite(segLed9,LOW);
	}
        else if(letter=='z' || letter == 'Z')
	{
     digitalWrite(segLed8,LOW);
     digitalWrite(segLed4,LOW);
     digitalWrite(segLed3,LOW);
     digitalWrite(segLed10,LOW);
     digitalWrite(segLed9,LOW);
	}
	else if (letter == '2')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed10, LOW);
	}
	else if (letter == '3')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed10, LOW);
	}
	else if (letter == '4')
	{
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed2, LOW);
	}
	else if (letter == '5')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed10, LOW);
	}
	else if (letter == '6')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed10, LOW);
		digitalWrite(segLed2, LOW);
	}
	else if (letter == '7')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed2, LOW);
	}
	else if (letter == '8')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed10, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed8, LOW);
	}
	else if (letter == '9')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed8, LOW);
		digitalWrite(segLed7, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed10, LOW);
	}
	else if (letter == '0')
	{
		digitalWrite(segLed4, LOW);
		digitalWrite(segLed3, LOW);
		digitalWrite(segLed9, LOW);
		digitalWrite(segLed10, LOW);
		digitalWrite(segLed2, LOW);
		digitalWrite(segLed8, LOW);
	}
	else if (letter == '.')
        {
		digitalWrite(segLedP, LOW);
        }
        else if (letter == '-')
        {
                digitalWrite(segLed7, LOW);
        }
        else if (letter == '$' || letter == ',' || letter == ':'){
                digitalWrite(segLed4, HIGH);
		digitalWrite(segLed3, HIGH);
		digitalWrite(segLed7, HIGH);
		digitalWrite(segLed9, HIGH);
		digitalWrite(segLed10, HIGH);
		digitalWrite(segLed2, HIGH);
		digitalWrite(segLed8, HIGH);
                digitalWrite(segLedP, HIGH);
        }	
}
