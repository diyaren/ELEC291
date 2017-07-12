
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif 

#define DataPort  PORTC // Using PortC as our Dataport
#define DataDDR   DDRC
const byte adcPin = 0;
int pin = 2 ;
//int probe = A2;
volatile int switchState;
//volatile int  readData;
volatile float  convertData;
volatile float voltage;
void setup() {
Serial.begin(9600);
pinMode(pin,INPUT);
pinMode(adcPin,OUTPUT);

PORTD = 1<<PD2;   // Enable PD2 pull-up resistor
 
EIMSK |= _BV(INT0);         // Enable INT0
MCUCR = 1<<ISC01 | 1<<ISC00;  // Trigger INT0 on rising edge

ADCSRA =  bit (ADEN);                      // turn ADC on
ADCSRA |= bit (ADPS0) | bit (ADPS2); // Prescaler of 4 307692 per sec
ADMUX = bit (REFS0) | bit (REFS1)  | 0x08;//choose the pin for anolog read 

delay(20);
}

void loop()  {
switchState=adcPin & 0b00000100;//check the 

}

ISR (INT0_vect) {
bitSet (ADCSRA,ADSC); //start a conversion

while(bit_is_set(ADCSRA,ADSC)){  }
int readData= analogRead(adcPin);
float voltage= readData * (5.0 / 1023.0);

//Serial.println("voltage:");
Serial.println(voltage);
}

