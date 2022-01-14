#include "technolarp_buzzer.h"

M_buzzer::M_buzzer(uint8_t buzzerPinSet)
{
	buzzerPin = buzzerPinSet;
	buzzerActif = false;
    statutBuzzer = false;
	iterations = 0;
	interval = 0;
  
	frequency = 1000;
	previousMillis = 0;
	
	pinMode(buzzerPin, OUTPUT);
	digitalWrite(buzzerPin, LOW);
}


void M_buzzer::update()
{
	if (buzzerActif)
	{
		if(millis() - previousMillis > interval)
		{
			previousMillis = millis();
			statutBuzzer = !statutBuzzer;
			
			if (statutBuzzer)
			{
				buzzerOn();
			}
			else
			{
				buzzerOff();
			}
			
			if (iterations>0)
			{
				iterations-=1;
			}
			
			if (iterations==0)
			{
				buzzerActif = false;
			}
		}
	}
}

void M_buzzer::buzzerOn(uint16_t newFrequency)
{
	frequency = newFrequency;
	analogWrite(buzzerPin, frequency);
	previousMillis = millis();
}

void M_buzzer::buzzerOn()
{
	analogWrite(buzzerPin, frequency);
	previousMillis = millis();
}

void M_buzzer::buzzerOff()
{
	analogWrite(buzzerPin, 0);
	pinMode(buzzerPin, OUTPUT);
	digitalWrite(buzzerPin, LOW);
}

void M_buzzer::shortBeep()
{
	statutBuzzer = true;
	buzzerActif = true;
	
	frequency = 1000;
	iterations = 1;
	interval = 50;
	
	buzzerOn();
}

void M_buzzer::doubleBeep()
{
	statutBuzzer = true;
	buzzerActif = true;
	
	frequency = 1000;
	iterations = 3;
	interval = 50;
	
	buzzerOn();
}

void M_buzzer::tripleBeep()
{
	statutBuzzer = true;
	buzzerActif = true;
	
	frequency = 1000;
	iterations = 5;
	interval = 100;
	
	buzzerOn();
}

void M_buzzer::longBeep()
{
	statutBuzzer = true;
	buzzerActif = true;
	
	frequency = 500;
	iterations = 1;
	interval = 400;
	
	buzzerOn();
}

void M_buzzer::explosionBeep(uint16_t intervalToSet)
{
	statutBuzzer = true;
	buzzerActif = true;
	
	frequency = 500;
	iterations = 1;
	interval = intervalToSet;
	
	buzzerOn();
}

void M_buzzer::setBuzzerActif(bool toSet)
{
	buzzerActif = toSet;
}

bool M_buzzer::getBuzzerActif()
{
	return(buzzerActif);
}
