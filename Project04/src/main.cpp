#include <Arduino.h>
#include "pitches.h"

#define ArrayCount(x) (sizeof(x)/sizeof(x[0]))

const int ActiveBuzzerPin = 12;
const int PassiveBuzzerPin = 8;
const int DurationInMilis = 500;
const int Delay1InMilis = 200;
const int Delay2InMilis = 533;

struct Note
{
	int note;
	int duration;
	int delay;
};

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
	{NOTE_G3, DurationInMilis, Delay2InMilis}
};

void setup()
{

}

void loop()
{
	for (auto noteIndex = 0; noteIndex < ArrayCount(Melody); noteIndex++) 
	{
		auto note = Melody[noteIndex];
		tone(PassiveBuzzerPin, note.note, note.duration);     
		delay(note.delay);
	}   
}

void SetupActiveBuzzer()
{
	pinMode(ActiveBuzzerPin, OUTPUT);
}

void UpdateActiveBuzzer()
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