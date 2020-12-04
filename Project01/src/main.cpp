#include <Arduino.h>
#include <IRremote.h>
#include <DHT.h>
#include <Ticker.h>
#include "main.h"

template <typename T, size_t n>
constexpr size_t ArrayCount(const T (&)[n]) { return n; }

static char KeyBuf[][13] =
	{
		"POWER",
		"FUNC/STOP",
		"VOL+",
		"FAST BACK",
		"PAUSE",
		"FAST FORWARD",
		"DOWN",
		"VOL-",
		"UP",
		"EQ",
		"ST/REPT",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9"
	};

static unsigned long KeyValue[] =
	{
		KEY_POWER,
		KEY_FUNC_STOP,
		KEY_VOL_ADD,
		KEY_FAST_BACK,
		KEY_PAUSE,
		KEY_FAST_FORWARD,
		KEY_DOWN,
		KEY_VOL_DE,
		KEY_UP,
		KEY_EQ,
		KEY_ST_REPT,
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_REPEAT
	};

#define DHT_PIN 2
#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6
#define DHT_TYPE DHT11
#define TEMP_HIGH 25.0f
#define TEMP_LOW 17.0f


IRrecv irrecv(RECEIVER);
decode_results results;
DHT dht(DHT_PIN, DHT_TYPE);

void UpdateTemperatureSensor();
void UpdateRemoteControl();

Ticker temperatureTimer(UpdateTemperatureSensor, 2000);
Ticker remoteControlTimer(UpdateRemoteControl, 0);

bool running;

void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn();
	dht.begin();

	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BLUE_PIN, OUTPUT);

	temperatureTimer.start();
	remoteControlTimer.start();

	running = true;
}

void loop()
{
	if (running)
	{
		temperatureTimer.update();
	}
	remoteControlTimer.update();
}

void UpdateTemperatureSensor()
{
	float temperatureInCelsius = dht.readTemperature();
	float red, green, blue = 0;

	if (temperatureInCelsius <= TEMP_LOW)
	{
		blue = 64;
	}
	else if (temperatureInCelsius >= TEMP_HIGH)
	{
		red = 64;
	}
	else
	{
		green = 64;
	}

	analogWrite(RED_PIN, red);
	analogWrite(GREEN_PIN, green);
	analogWrite(BLUE_PIN, blue);
}

void UpdateRemoteControl()
{
	int tmpValue;
	if (irrecv.decode(&results))
	{
		for (size_t i = 0; i < ArrayCount(KeyValue); i++)
		{
			const unsigned long key = KeyValue[i];
			if (key == results.value && i < KEY_NUM)
			{
				if (key == KEY_POWER)
				{
					running = !running;
					analogWrite(RED_PIN, 0);
					analogWrite(GREEN_PIN, 0);
					analogWrite(BLUE_PIN, 0);
				}
				Serial.println(KeyBuf[i]);
				Serial.println(running);
				tmpValue = results.value;
			}
			else if (REPEAT == i)
			{
				results.value = tmpValue;
			}
		}

		irrecv.resume();
	}
}