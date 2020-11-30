#include <Arduino.h>
#include <IRremote.h>
#include <DHT.h>
#include <Ticker.h>
#include "main.h"

#define DHTPIN 2 
#define DHTTYPE DHT11

template <typename T, size_t n> constexpr size_t ArrayCount(const T (&)[n]) { return n; }

static unsigned long KeyValue[]={KEY_POWER,KEY_FUNC_STOP,KEY_VOL_ADD,KEY_FAST_BACK,KEY_PAUSE,KEY_FAST_FORWARD,
                KEY_DOWN,KEY_VOL_DE,KEY_UP,KEY_EQ,KEY_ST_REPT,KEY_0,KEY_1,KEY_2,KEY_3,KEY_4,KEY_5,
                KEY_6,KEY_7,KEY_8,KEY_9,KEY_REPEAT};

static char KeyBuf[][13]={"POWER","FUNC/STOP","VOL+","FAST BACK","PAUSE","FAST FORWARD","DOWN","VOL-",
                  "UP","EQ","ST/REPT","0","1","2","3","4","5","6","7","8","9"};

IRrecv irrecv(RECEIVER); 
decode_results results;	 
DHT dht(DHTPIN, DHTTYPE);

void UpdateTemperatureSensor();
void UpdateInfrared();
void ResetLeds();

Ticker temperatureTimer(UpdateTemperatureSensor, 2000);
Ticker infraredTimer(UpdateInfrared, 0);

void setup()
{
	Serial.begin(9600);
	irrecv.enableIRIn();	
	dht.begin();
	pinMode(4, OUTPUT);    
	pinMode(6, OUTPUT);    

	temperatureTimer.start();
	infraredTimer.start();
}

void loop()
{
	temperatureTimer.update();
	infraredTimer.update();
}

void UpdateTemperatureSensor()
{
	float t = dht.readTemperature();
	if (t > 25.0f)
	{
		digitalWrite(6, HIGH);
	}
	else if (t < 17.0f)
	{
		digitalWrite(4, HIGH);
	}
	else
	{
		digitalWrite(4, LOW);
		digitalWrite(6, LOW);
	}
	Serial.println(t);
}

void UpdateInfrared()
{
	int tmpValue;
	if (irrecv.decode(&results))
	{
		for (size_t i = 0; i < ArrayCount(KeyValue); i++)
		{
			if ((KeyValue[i] == results.value) && (i < KEY_NUM))
			{
				Serial.println(KeyBuf[i]);
				digitalWrite(4, HIGH);
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