#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
const int Slave3 = 10;

char ssid[] = "Fnce259";      //  your network SSID (name)
char pass[] = "paris149";   // your network password
int keyIndex = 1;    // your network key Index number (needed only for WEP)
 
IPAddress ip( 192, 168, 1, 12 );    // ipaddress obtained from access point
IPAddress gateway( 192, 168, 1, 1 );
IPAddress subnet( 255, 255, 255, 0 );

char server[] = "mail.yourmailserver.com";  // smtp mail server  (mine.com)
int status = WL_IDLE_STATUS;
 
WiFiClient client;

void setup() {
Serial.begin(9600);
Wire.begin(Slave3);
Wire.onReceive(receiveEvent);
}

void loop() {
 byte inChar;
   inChar = Serial.read();
 
  if(inChar == 'e')
   {
       if(sendEmail()) Serial.println("Email sent");    
       else Serial.println("Email failed");
   }      

}


byte sendEmail()
 {
   byte thisByte = 0;
   byte respCode;
 
  if(client.connect(server,25)) {
     Serial.println("connected");
   } else {
     Serial.println("connection failed");
     return 0;
   }
 
  if(!eRcv()) return 0;
   Serial.println("Sending helo");
 
// change to your public ip
   client.write("helo 1.2.3.4\r\n");
 
  if(!eRcv()) return 0;
   Serial.println("Sending From");
 
// change to your email address (sender)
   client.write("MAIL From: <me@mine.com>\r\n");
 
  if(!eRcv()) return 0;
 
// change to recipient address
   Serial.println("Sending To");
   client.write("RCPT To: <you@mine.com>\r\n");
 
  if(!eRcv()) return 0;
 
  Serial.println("Sending DATA");
   client.write("DATA\r\n");
 
  if(!eRcv()) return 0;
 
  Serial.println("Sending email");
 
// change to recipient address
   client.write("To: You <you@mine.com>\r\n");
 
// change to your address
   client.write("From: Me <me@mine.com>\r\n");
 
  client.write("Subject: Arduino email test\r\n");
  client.write("This is from my Arduino WiFi shield!\r\n");
  client.write(".\r\n");
 
  if(!eRcv()) return 0;
 
  Serial.println("Sending QUIT");
  client.write("QUIT\r\n");
 
  if(!eRcv()) return 0;
 
  client.stop();
 
  Serial.println("disconnected");
 
  return 1;
 }
 
byte eRcv()
{
  byte respCode;
  byte thisByte;
  int loopCount = 0;
 
  while(!client.available()) {
    delay(1);
    loopCount++;
 
    // if nothing received for 10 seconds, timeout
    if(loopCount > 10000) {
      client.stop();
      Serial.println("\r\nTimeout");
      return 0;
    }
  }
 
  respCode = client.peek();
 
  while(client.available())
   {  
     thisByte = client.read();    
     Serial.write(thisByte);
   }
 
  if(respCode >= '4')
   {
     efail();
     return 0;  
   }
 
  return 1;
 }
 
void efail()
{
  byte thisByte = 0;
  int loopCount = 0;
 
  client.write("QUIT\r\n");
 
  while(!client.available()) {
    delay(1);
    loopCount++;
 
    // if nothing received for 10 seconds, timeout
    if(loopCount > 10000) {
      client.stop();
      Serial.println("\r\nTimeout");
      return;
    }
  }
 
  while(client.available())
  {  
    thisByte = client.read();    
    Serial.write(thisByte);
  }
 
  client.stop();
 
  Serial.println("disconnected");
}


void receiveEvent(int howMany) {
while (Wire.available() > 0) { // loop through all but the last
    int receivedData  = Wire.read(); // receive byte as an int
    Serial.println(receivedData);
    if(receivedData==1){
      sendEmail();
    }
   }

}


