#include "Stepper.h"
#include "Arduino.h"

const int StepperSpeed = 500;
const int StepCount = 32;
const int SwitchPin = 7; 
const int XPin = 0;  
const int YPin = 1;  
const int JoystickThresholdLow = 400;
const int JoystickThresholdHigh = 600;

Stepper stepper(StepCount, 8, 10, 9, 11);

void setup()
{
	pinMode(SwitchPin, INPUT);
	digitalWrite(SwitchPin, HIGH);
	Serial.begin(9600);
}

void loop()
{
	auto horizontal = analogRead(XPin);
	auto vertical = analogRead(YPin);

	if (vertical > JoystickThresholdHigh)
	{
		stepper.setSpeed(StepperSpeed);
		stepper.step(StepCount);
	}
	else if (vertical < JoystickThresholdLow)
	{
		stepper.setSpeed(StepperSpeed);
		stepper.step(-StepCount);
	}
}