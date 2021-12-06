#include "technolarp_fastled.h"

M_fastled::M_fastled()
{
	// pour utiliser une led ws2811
	//FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, NB_LEDS_MAX);
	// pour utiliser une led adafruit neopixel
	FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NB_LEDS_MAX);
	FastLED.setBrightness(50);
	
	nbLeds=8;
	
	animationActive=false;
	ledStatus=true;
	iterations = 0;
	
	interval = 100;
	previousMillis = 0;
	
	indexLed = 0;
	
	for (uint8_t i=0;i<NB_COULEURS_MAX;i++)
	{
		couleurs[i]=CRGB::Green;
	}
	
	animActuelle = ANIM_NONE;
}

void M_fastled::ledOn(uint8_t ledToSet, CRGB colorToSet, bool change)
{
	leds[ledToSet]=colorToSet;

	if (change)
	{
		FastLED.show();
	}
}

void M_fastled::allLedOn(CRGB colorToSet, bool change)
{
	for (uint8_t i=0;i<nbLeds;i++)
	{
		ledOn(i, colorToSet, false);
	}
	if (change)
	{
		FastLED.show();
	}
}

void M_fastled::ledOff(uint8_t ledToSet, bool change)
{
	ledOn(ledToSet, CRGB::Black, change);
}

void M_fastled::allLedOff()
{
	allLedOff(true);
}

void M_fastled::allLedOff(bool change)
{
	FastLED.clear();
	
	if (change)
	{
		FastLED.show();
	}
}


void M_fastled::setNbLed(uint8_t nbLedsInit)
{
	nbLeds=nbLedsInit;
}

uint8_t M_fastled::getNbLed()
{
	return(nbLeds);
}

void M_fastled::setBrightness(uint8_t newBrightness)
{
	FastLED.setBrightness(newBrightness);
}

void M_fastled::ledShow()
{
	FastLED.show();
}

void M_fastled::updateAnimation()
{
	if (animationActive)
	{
		if(millis() - previousMillis > interval)
		{
			previousMillis = millis();
			ledStatus = !ledStatus;
			
			switchAnim(animActuelle);
			
			if (iterations>0)
			{
				iterations-=1;
			}
			
			if (iterations==0)
			{
				animationActive = false;
				switchAnimEnd(animActuelle);
				animActuelle = ANIM_NONE;
			}
		}
	}
}

void M_fastled::animationDepart(uint16_t intervalToSet, uint16_t iterationToSet, CRGB colorToSet1)
{
	indexLed = 0;
	interval = intervalToSet;
	couleurs[0] = colorToSet1;
	
	for (uint8_t i = 0; i < iterationToSet; i++)
	{
		ledOn(i, couleurs[0], true);
		delay(intervalToSet);
		ledOff(i, true);
	}
	allLedOff();
}

void M_fastled::animationBlinkEnd()
{
	allLedOff();
}

void M_fastled::animationBlink()
{
	if (ledStatus)
	{
		allLedOn(couleurs[0], true);
	}
	else
	{
		allLedOn(couleurs[1], true);
	}
}

void M_fastled::animationBlink01Start(uint16_t intervalToSet, uint16_t iterationToSet, CRGB colorToSet1, CRGB colorToSet2)
{
	animActuelle = ANIM_BLINK;
	animationActive=true;
	ledStatus=true;
	iterations = iterationToSet;
	
	interval = intervalToSet;
	couleurs[0] = colorToSet1;
	couleurs[1] = colorToSet2;
	previousMillis = millis();
}

void M_fastled::animationBlink02Start(uint16_t intervalToSet, uint16_t dureeToSet, CRGB colorToSet1, CRGB colorToSet2)
{
	animActuelle = ANIM_BLINK;
	animationActive=true;
	ledStatus=true;
	
	iterations = dureeToSet/intervalToSet;
	
	interval = intervalToSet;
	couleurs[0] = colorToSet1;
	couleurs[1] = colorToSet2;
	previousMillis = millis();
}

void M_fastled::animationSerpentEnd()
{
	allLedOff();
}

void M_fastled::animationSerpent()
{
	ledOn(indexLed, couleurs[1], false);
	indexLed+=1;
	indexLed%=nbLeds;
	ledOn(indexLed, couleurs[0], true);
}

void M_fastled::animationSerpent01Start(uint16_t intervalToSet, uint16_t iterationToSet, CRGB colorToSet1, CRGB colorToSet2)
{
	animActuelle = ANIM_SERPENT;
	animationActive=true;
	indexLed = 0;
	
	iterations = iterationToSet;
	
	interval = intervalToSet;
	couleurs[0] = colorToSet1;
	couleurs[1] = colorToSet2;
	allLedOn(couleurs[1], true);
	previousMillis = millis();
}

void M_fastled::animationSerpent02Start(uint16_t intervalToSet, uint16_t dureeToSet, CRGB colorToSet1, CRGB colorToSet2)
{
	animActuelle = ANIM_SERPENT;
	animationActive=true;
	indexLed = 0;
	
	iterations = dureeToSet/intervalToSet;
	
	interval = intervalToSet;
	couleurs[0] = colorToSet1;
	couleurs[1] = colorToSet2;
	allLedOn(couleurs[1], true);
	previousMillis = millis();
}


bool M_fastled::isAnimActive()
{
	if (animActuelle == ANIM_NONE)
	{
		return(false);
	}
	else
	{
		return(true);
	}
}

void M_fastled::setAnimation(uint8_t toSet)
{
	animActuelle = toSet;
}

void M_fastled::switchAnim(uint8_t anim)
{
	switch (anim) 
    {
      case ANIM_BLINK:
        animationBlink();
      break;
	  
	  case ANIM_SERPENT:
        animationSerpent();
      break;
	  
      default:
        // nothing to do
      break;
    }
}

void M_fastled::switchAnimEnd(uint8_t anim)
{
	switch (anim) 
    {
      case ANIM_BLINK:
        animationBlinkEnd();
      break;
	  
	  case ANIM_SERPENT:
        animationSerpentEnd();
      break;
	  
      default:
        // nothing to do
      break;
    }
}
