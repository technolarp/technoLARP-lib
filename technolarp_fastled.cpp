#include "technolarp_fastled.h"

M_fastled::M_fastled()
{
	// pour utiliser une led ws2811
  //FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, NB_LEDS_MAX);
  // pour utiliser une led adafruit neopixel
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NB_LEDS_MAX);
  FastLED.setBrightness(50);
  
  nbLeds=8;
  
  ledStatus=true;

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




/*


void M_fastled::setBrightness(uint8_t newBrightness)
{
	FastLED.setBrightness(newBrightness);
}

void M_fastled::setAnim(uint8_t anim)
{
	anim=anim;
}
	
bool M_fastled::Callback()
  {
    switch (anim) 
    {
      case ANIM_BLINK:
        animBlink();
      break;
	  
      case ANIM_SERPENT:
        animSerpent();
      break;
	  
	  case ANIM_SERRURE_BLOQUEE:
        animSerrureBloquee();
      break;
	  
	  case ANIM_SERRURE_ERREUR:
        animSerrureErreur();
      break;
	  
      default:
        // nothing to do
      break;
    }
    
    return true;
  }
    
    bool M_fastled::OnEnable()
    {
      // Serial.print("task neopixel ENABLE  ");
	  // Serial.print(millis());
      // Serial.println();
      allLedOff();
      return true;
     
    }
    
	void M_fastled::OnDisable()
    {
      //Serial.print("task neopixel DISABLE  ");
	  // Serial.print(millis());
      //Serial.println();
	  anim=ANIM_NONE;

      
    }
    
	
	void M_fastled::moveLed()
	{
		M_fastled::ledOn(indexLed,CRGB::Black);
		
		indexLed+=1;
		indexLed%=nbLeds;
		ledStatus=true;
		forceNextIteration();
	}

  void M_fastled::changeColor()
  {
    indexColor++;
    indexColor%=3;
    if (indexColor==0)
    {
      animBlinkColor=CRGB::Red;
    }
    else if (indexColor==1)
    {
      animBlinkColor=CRGB::Green;
    }
    else
    {
      animBlinkColor=CRGB::Blue;
    }    
  }
  
  void M_fastled::changeColor(CRGB cCouleur)
  {
    animBlinkColor=cCouleur;
  }
	
	void M_fastled::setIndexLed(uint8_t aLed)
	{
    indexLed=aLed%nbLeds;
  }
	
	uint8_t M_fastled::getIndexLed()
	{
    return(indexLed);
  }

  void M_fastled::startAnimBlink(uint16_t nbRun, uint16_t delaiBlink, CRGB color, uint8_t nbLed)
  {
    setInterval(delaiBlink);
    setIterations(nbRun);
	animBlinkColor=color;
	indexLed=nbLed;
    forceNextIteration();
    anim=ANIM_BLINK;
    
    enable();
  }
   
	void M_fastled::startAnimSerpent(uint8_t startLed, uint16_t nbRun, uint16_t delayLed, CRGB color)
	{
		setInterval(delayLed);
		setIterations(nbRun*nbLeds);
		forceNextIteration();
		anim=ANIM_SERPENT;
		animBlinkSerpent=color;
		animSerpentIndex=startLed;
		
		enable();
	}
  
	void M_fastled::startAnimSerrureBloquee(uint16_t nbRun, uint16_t delaiBlink)
	{
		setInterval(delaiBlink);
		setIterations(nbRun+1);
		
		anim=ANIM_SERRURE_BLOQUEE;
		
		enableIfNot();
		forceNextIteration();		
	}
	
	void M_fastled::startAnimSerrureErreur(uint16_t nbRun, uint16_t delaiBlink)
	{
		setInterval(delaiBlink);
		setIterations(nbRun+1);
		
		anim=ANIM_SERRURE_ERREUR;
		
		enableIfNot();
		forceNextIteration();		
	}

	void M_fastled::animBlink()
    {
		for (int i=0;i<indexLed;i++)
		{
			if (ledStatus)
			{
				setLed(i, animBlinkColor);
			}
			else
			{
				setLed(i, CRGB::Black);
			}
		}
		
		ledShow();
		ledStatus=!ledStatus;
    }
  
	void M_fastled::animSerpent()
    {
      ledOn(animSerpentIndex, CRGB::Black);
      animSerpentIndex++;
      animSerpentIndex%=nbLeds;
      ledOn(animSerpentIndex, animBlinkSerpent);
    }

	void M_fastled::animSerrureBloquee()
	{
		for (int i=0;i<nbLeds;i++)
		{
			if (ledStatus)
			{
				leds[i] = CRGB::Red;
			}
			else
			{
				leds[i] = CRGB::Green;
			}		
		  }
		  FastLED.show();

		ledStatus=!ledStatus;
    }
	
	

	void M_fastled::animSerrureErreur()
	{
		for (int i=0;i<nbLeds;i++)
		{
			if (ledStatus)
			{
				leds[i] = CRGB::Red;
			}
			else
			{
				leds[i] = CRGB::Black;
			}		
		}
		FastLED.show();
		
		ledStatus=!ledStatus;
	}
	
	
	bool M_fastled::isAnimActive()
	{
		if (anim==ANIM_NONE)
		{
			return(false);
		}
		else
		{
			return(true);
		}
	}
	*/