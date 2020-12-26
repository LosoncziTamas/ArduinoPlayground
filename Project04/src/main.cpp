#include <Arduino.h>
#include "pitches.h"

#define ArrayCount(x) (sizeof(x)/sizeof(x[0]))

struct Note
{
	int note;
	int duration;
	int delay;
};

struct ProgramState
{
	bool running;
	int lastSwitchRead;
	int currentLed;
};

const int DurationInMilis = 500;
const int Delay1InMilis = 200;
const int Delay2InMilis = 533;

const int RedLedPin = 4;
const int BlueLedPin = 5;
const int GreenLedPin = 6;
const int YellowLedPin = 7;
const int PassiveBuzzerPin = 8;
const int SwitchPin = 9;

const Note Melody[] = 
{
	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},

	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis},

	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},

	{NOTE_G3, DurationInMilis, Delay2InMilis},
	{NOTE_FS3, DurationInMilis, Delay2InMilis},
	{NOTE_G3, DurationInMilis, Delay2InMilis},

	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},

	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis},

	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A3, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis},

	{NOTE_G3, DurationInMilis, Delay2InMilis},
	{NOTE_FS3, DurationInMilis, Delay2InMilis},
	{NOTE_G3, DurationInMilis, Delay2InMilis},

	{NOTE_G3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_D3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},

	{NOTE_C3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_D3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},

	{NOTE_G3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_D3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},

	{NOTE_FS3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},

	{NOTE_G3, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis},
	{NOTE_D3, DurationInMilis, Delay1InMilis},

	{NOTE_G3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_D3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},

	{NOTE_C3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_D3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},

	{NOTE_G3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_FS3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_G3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},

	{NOTE_FS3, DurationInMilis, Delay1InMilis}, 
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis},
	{NOTE_A2, DurationInMilis, Delay1InMilis}
};

ProgramState CreateDefaultProgramState()
{
	return ProgramState
	{
		.running = false,
		.lastSwitchRead = HIGH,
		.currentLed = RedLedPin
	};
}

ProgramState state = CreateDefaultProgramState();

void setup()
{
	pinMode(SwitchPin, INPUT_PULLUP);  
	pinMode(RedLedPin, OUTPUT);
	pinMode(GreenLedPin, OUTPUT);
	pinMode(BlueLedPin, OUTPUT);
	pinMode(YellowLedPin, OUTPUT);

	Serial.begin(9600);
}

bool CheckRunningState()
{
	auto currentRead = digitalRead(SwitchPin);

	if (currentRead != state.lastSwitchRead)
	{
		if (currentRead == HIGH)
		{
			state.running = !state.running;	
		}
		state.lastSwitchRead = currentRead;
	}

	return state.running;
}


inline int SelectRandomLed()
{
	return RedLedPin + (rand() % 4);
}

void SwitchLed()
{
	digitalWrite(state.currentLed, LOW);  

	int randomLed = SelectRandomLed();
	while (randomLed == state.currentLed)
	{
		randomLed = SelectRandomLed();
	}
	state.currentLed = randomLed;  

	digitalWrite(state.currentLed, HIGH);    
}

void loop()
{
	auto running = CheckRunningState();

	for (auto noteIndex = 0; running && noteIndex < ArrayCount(Melody); noteIndex++) 
	{
		auto note = Melody[noteIndex];
		tone(PassiveBuzzerPin, note.note, note.duration); 
		SwitchLed();    
		for (int milisec = 0; running && milisec < note.delay; milisec++)
		{
			delay(1);
			running = CheckRunningState();
		}
	}   

	digitalWrite(RedLedPin, LOW);
	digitalWrite(BlueLedPin, LOW);
	digitalWrite(GreenLedPin, LOW);
	digitalWrite(YellowLedPin, LOW);
}