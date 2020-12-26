#include <Arduino.h>

const int ActiveBuzzerPin = 12;

void setup() 
{
	pinMode(ActiveBuzzerPin, OUTPUT);
	Serial.begin(9600);
}

void loop() 
{
	while(true)
	{
		for (auto i = 0; i < 80; ++i)
		{
			digitalWrite(ActiveBuzzerPin, HIGH);
			delay(1);
			digitalWrite(ActiveBuzzerPin, LOW);
			delay(1);
		}

		for (auto i = 0; i < 100; ++i)
		{
			digitalWrite(ActiveBuzzerPin, HIGH);
			delay(2);
			digitalWrite(ActiveBuzzerPin, LOW);
			delay(2);
		}
	}
}