#include <LiquidCrystal.h>


#include <DHT.h>


#define DHTPIN 2
#define DHTTYPE DHT11
int tempSensorPin=A2;
int switchPin= 4;
int lightPin=A1  ;
//int humSensor=3;

DHT dht(DHTPIN, DHTTYPE);
//LiquidCrystal lcd(10,11,12,13,5,6);
  
void setup(void) {
    Serial.begin(9600);
    pinMode(tempSensorPin,INPUT);
    //pinMode(humSensor,INPUT);
    pinMode(switchPin,INPUT);
    pinMode(lightPin,INPUT);
    //lcd.begin(16,2);
    
}

void loop() {
     int switchState=digitalRead(switchPin);
     if(switchState==LOW){

    /*
     * For analog temperature sensor
     * 
     * This part will work after the switch off
     */
    int readTemSensor = analogRead(tempSensorPin);
    //convert the value we read into voltage
    Serial.println("Start calculating the voltage!");
    float voltage=readTemSensor* 5.0;
    voltage=voltage/1024.0;
    Serial.print(voltage);
    Serial.println(" volts");
    //converts it into degrees Celsius and print out the temperature 
    Serial.println("Start calculating the degrees Celsius!");
    float tempC=voltage*100.0;
    Serial.print(tempC);
    Serial.println(" C");
    //and convert it into Fahrenheit
    Serial.println("Start calculating the degrees Celsius!");
    float tempF=(tempC*9.0/5.0)+32.0;
    Serial.print(tempF);
    Serial.println(" F");
    delay(1000);
    /**
     * 
     * read from humidity
     */
    float humidity;
    humidity=dht.readHumidity();
    //for serial monitor 
    Serial.print("H:");
    Serial.print(humidity);
    Serial.println("%");

    delay(1000);
    /**
     * For light :photocell
     * 
     * This part will work after the switch off
     */
    int lightReading=analogRead(lightPin);
    Serial.print("The light level: ");
    Serial.println(lightReading); 

    delay(1000);
    Serial.println("Weather broadcast ends!");
    Serial.println("Again?");
    while(Serial.available()==0){}
    String string =Serial.readString();
    while(string=="NO"||string=="no")
    delay(2000);
     } 
     //if switch is on
     else {
    
    /**
     * Read from DHT11
     * 
     */
   
    //lcd.clear();
    delay(2000);
    //read from DHT
    float temp,humidity;
    humidity=dht.readHumidity();
    temp=dht.readTemperature();
    //for serial monitor 
    Serial.print("T:");
    Serial.print(temp);
    Serial.println("C");
    
    Serial.print("H:");
    Serial.print(humidity);
    Serial.println("%");
    
    //for displaying data on LCD
//    lcd.setCursor(0,0);
//    lcd.print("T:");
//    lcd.print(temp);
//    lcd.print("C");
//    lcd.setCursor(0,1);
//    lcd.print("H:");
//    lcd.print(humidity);
//    lcd.print("%");

    delay(1000);
    /**
     * read from photocell
     */
    int lightReading=analogRead(lightPin);
    Serial.print("The light level: ");
    Serial.println(lightReading); 

//    lcd.clear();
//    lcd.setCursor(0,0);
//    lcd.print("Light level: ");
//    lcd.print(lightReading);

    delay(1000);
     }
    
    
}
