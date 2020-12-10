#include <Arduino.h>

int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

byte leds = 0;

void setup() 
{
	Serial.begin(9600);
	pinMode(latchPin, OUTPUT);
  	pinMode(dataPin, OUTPUT);  
  	pinMode(clockPin, OUTPUT);
}

void UpdateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, leds);
   digitalWrite(latchPin, HIGH);
}

void loop()
{
	leds = 0;	
	UpdateShiftRegister();
	delay(500);
	for (int i = 0; i < 8; i++)	
	{
		bitSet(leds, i);		
		UpdateShiftRegister();
		delay(500);
	}
}