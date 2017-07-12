uint8_t  LCD_Ard_d7=10;
uint8_t  LCD_Ard_d6=11;
uint8_t  LCD_Ard_d5=12;
uint8_t  LCD_Ard_d4=13;

uint8_t  LCD_Ard_RS=1;
//uint8_t  LCD_Ard_RW=8;
uint8_t  LCD_Ard_EN=9;

// LCD module information
#define _LineOne     0x00                    // start of line 1
#define LCD_LineTwo     0x40                    // start of line 2

// LCD instructions
#define LCD_Clear           0b00000001          // replace all characters with ASCII 'space'
#define LCD_Home            0b00000010          // return cursor to first position on first line
#define LCD_EntryMode       0b00000110          // shift cursor from left to right on read/write
#define LCD_DisplayOff      0b00001000          // turn display off
#define LCD_DisplayOn       0b00001100          // display on, cursor off, don't blink character
#define LCD_FunctionReset   0b00110000          // reset the LCD
#define LCD_FunctionSet4bit 0b00101000          // 4-bit data, 2-line display, 5 x 7 font
#define LCD_SetCursor       0b10000000          // set cursor position
uint8_t welcomeString1[]="Hello&welcome";
uint8_t welcomeString2[]="to our demo!";

void setup() {
pinMode(LCD_Ard_d7,OUTPUT);
pinMode(LCD_Ard_d6,OUTPUT);
pinMode(LCD_Ard_d5,OUTPUT);
pinMode(LCD_Ard_d4,OUTPUT);

pinMode(LCD_Ard_EN,OUTPUT);
pinMode(LCD_Ard_RS,OUTPUT);
pinMode(LCD_Ard_RW,OUTPUT);

initialLCD();
writeCommand(welcomeString1);
checkingSensor();
writeInstruction(LCD_SetCursor|LCD_LineTwo);
writeCommand(welcomeString2);


}

void loop() {
}

void initialLCD(void){
  delay(100);
  digitalWrite(LCD_Ard_RS,LOW);
  digitalWrite(LCD_Ard_EN,LOW);
  LCDWrite4(LCD_FunctionReset);
  delay(10);
  LCDWrite4(LCD_FunctionReset);
  delayMicroseconds(300);
  LCDWrite4(LCD_FunctionReset);
  delayMicroseconds(300);
  LCDWrite4(LCD_FunctionSet4bit);   //set mode 
  delayMicroseconds(300);
 
  checkingSensor();         
  writeInstruction(LCD_DisplayOff);
  checkingSensor();
  writeInstruction(LCD_Clear);
  checkingSensor();
  writeInstruction(LCD_EntryMode);
  checkingSensor();
  writeInstruction(LCD_DisplayOn);
}
void writeCommand(uint8_t passingString[] ){
  volatile int i=0;
  while(passingString[i]!=0)
  {
    checkingSensor();
    writeCharacter(passingString[i]);
    i++;
  }
}

void writeCharacter(uint8_t passingData){
  digitalWrite(LCD_Ard_RW,LOW);
  digitalWrite(LCD_Ard_RS,HIGH);
  digitalWrite(LCD_Ard_EN,LOW);
  LCDWrite4(passingData);//write upper four bits of the data 
  LCDWrite4(passingData<<4);//write lower four bits of the data 
  
}

void writeInstruction(uint8_t passingInstruction){
  digitalWrite(LCD_Ard_RW,LOW);
  digitalWrite(LCD_Ard_RS,LOW);
  digitalWrite(LCD_Ard_EN,LOW);
  LCDWrite4(passingInstruction);//write upper four bits of the data 
  LCDWrite4(passingInstruction<<4);//write lower four bits of the data 
  
}

void LCDWrite4(uint8_t theByte)
{
  digitalWrite(LCD_Ard_d7,LOW); 
  if(theByte&1<<7){
  digitalWrite(LCD_Ard_d7,HIGH);         
  }
  digitalWrite(LCD_Ard_d6,LOW);
  if(theByte&1<<6){
  digitalWrite(LCD_Ard_d6,HIGH);         
  }
   digitalWrite(LCD_Ard_d5,LOW);
  if(theByte&1<<5){
  digitalWrite(LCD_Ard_d5,HIGH) ;        
  }
   digitalWrite(LCD_Ard_d4,LOW);
  if(theByte&1<<4){
  digitalWrite(LCD_Ard_d4,HIGH);        
  }

  digitalWrite(LCD_Ard_EN,HIGH);     
  delayMicroseconds(1); 
  digitalWrite(LCD_Ard_EN,LOW);
  delayMicroseconds(1); 
}

void checkingSensor(void){

    uint8_t busy_flag_copy;                         // busy flag 'mirror'

    pinMode(LCD_Ard_d7, INPUT);                  // set D7 data direction to input
    digitalWrite(LCD_Ard_RS, LOW);               // select the Instruction Register (RS low)
    digitalWrite(LCD_Ard_RW, HIGH);              // read from the LCD module (RW high)

    do
    {
        busy_flag_copy = 0;                        // initialize busy flag 'mirror'      
        digitalWrite(LCD_Ard_EN,HIGH);            // Enable pin high
        delayMicroseconds(1);                       // implement 'Delay data time' (160 nS) and 'Enable pulse width' (230 nS)
 
        busy_flag_copy = digitalRead(LCD_Ard_d7);   // get actual busy flag status 

        digitalWrite(LCD_Ard_EN,LOW);             // Enable pin low
        delayMicroseconds(1);                     // implement 'Address hold time' (10 nS), 'Data hold time' (10 nS), and 'Enable cycle time' (500 nS )
// read and discard alternate nibbles (D3 information)
        digitalWrite(LCD_Ard_EN,HIGH);            // Enable pin high
        delayMicroseconds(1);                     // implement 'Delay data time' (160 nS) and 'Enable pulse width' (230 nS)
        digitalWrite(LCD_Ard_EN,LOW);             // Enable pin low
        delayMicroseconds(1);                     // implement 'Address hold time' (10 nS), 'Data hold time' (10 nS), and 'Enable cycle time' (500 nS )

    }   while (busy_flag_copy);                   // check again if busy flag is high    

// arrive here if busy flag is clear -  clean up and return
    digitalWrite(LCD_Ard_RW, LOW);               // write to the LCD module (RW low)
    pinMode(LCD_Ard_d7, OUTPUT);                 // set D7 data direction to output
}



