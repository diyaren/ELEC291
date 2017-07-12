int LCD1602_RS=8;   
int LCD1602_EN=9;   
int DB[] = { 10, 11, 12, 13};
char str1[]={"Hello & welcome"};
char str2[]={"to our demo!"};
char str3[]={"ELEC 291-20C"};
char str4[]={"Team L2C-3C "};


void LCD_Command_Write(int command)
{
 int i,temp;
 digitalWrite( LCD1602_RS,LOW);
 digitalWrite( LCD1602_EN,LOW);
 //to write the state from d4-d7
 temp=command & 0xf0;   
 for (i=DB[0]; i < 14; i++)
 {
   digitalWrite(i,temp & 0x80);
   temp <<= 1; //left shift one bit
 }
 
 digitalWrite( LCD1602_EN,HIGH);
 delayMicroseconds(20);
 digitalWrite( LCD1602_EN,LOW);
 
 temp=(command & 0x0f)<<4;
 for (i=DB[0]; i <14; i++)
 {
   digitalWrite(i,temp & 0x80);
   temp <<= 1;
 }
 
 digitalWrite( LCD1602_EN,HIGH);
 delayMicroseconds(20); 
 digitalWrite( LCD1602_EN,LOW);
}
 
void LCD_Data_Write(int dat)
{
 int i=0,temp;
 digitalWrite( LCD1602_RS,HIGH);
 digitalWrite( LCD1602_EN,LOW);
 
 temp=dat & 0xf0;//send the upper four bits
 for (i=DB[0]; i <14; i++)
 {
   digitalWrite(i,temp & 0x80);
   temp <<= 1;//left shift
 }
 
 digitalWrite( LCD1602_EN,HIGH);
 delayMicroseconds(20);
 digitalWrite( LCD1602_EN,LOW);
 
 temp=(dat & 0x0f)<<4;//send the lower four bits
 for (i=DB[0]; i < 14; i++)
 {
   digitalWrite(i,temp & 0x80);
   temp <<= 1;//left shift
 }
 
 digitalWrite( LCD1602_EN,HIGH);
 delayMicroseconds(20); 
 digitalWrite( LCD1602_EN,LOW);
}


 
void LCD_SET_XY( int x, int y)
{
  int address;
  if (y ==0)    address = 0x80 + x;//first row ,base address+position 
  else          address = 0xC0 + x;//second row 
  LCD_Command_Write(address); 
}
 
void LCD_Write_Char( int x,int y,int dat)
{
  LCD_SET_XY( x, y );   //set the cursor 
  LCD_Data_Write(dat);
}
 
void LCD_Write_String(int X,int Y,char *s)
{
    LCD_SET_XY( X, Y );    //set address 
    while (*s)             //write it on the screen 
    {
      LCD_Data_Write(*s);   
      s++;
    }
}


 
void setup (void) 
{
     Serial.begin(9600);
     pinMode(8,OUTPUT);
     pinMode(9,OUTPUT);
     pinMode(10,OUTPUT);
     pinMode(11,OUTPUT);
     pinMode(12,OUTPUT);     
     pinMode(13,OUTPUT);
   

 delay(100);
 LCD_Command_Write(0x28);//set 4 bits mode
 delay(100);
 LCD_Command_Write(0x28);//repeat this process to make sure screen initialize
delay(100);
 LCD_Command_Write(0x28);
 delay(100);
  LCD_Command_Write(0x28);
 delay(100); 
 LCD_Command_Write(0x01);//clean the screen
 delay(50); 
  LCD_Command_Write(0x06);//cursor move to the right 
 delay(50); 
 LCD_Command_Write(0x0c);//the second position of second row 
 delay(50); 
 LCD_Command_Write(0x80); //the frist position of frist row:base address
delay(50); 



 }
 
void loop (void)
{
  
   LCD_Command_Write(0x01);  //clean the screen 
   delay(1000);
   LCD_Write_String(0,1,str1);  //write on the frist row, second col
   delay(50);
   LCD_Write_String(1,2,str2);//write on the second row, start at third col
   delay(50);
   LCD_Command_Write(0x01);  
   delay(50);
   LCD_Write_String(0,1,str3);//first row, second col
   delay(50);
   LCD_Write_String(1,2,str4);//second row, third col
   delay(1000);
 
}
