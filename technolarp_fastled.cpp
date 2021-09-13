#include "technolarp_fastled.h"


M_fastled::M_fastled(Scheduler* aScheduler) : Task(TASK_MILLISECOND*100, TASK_FOREVER, aScheduler, false)
{
  // pour utiliser une led ws2811
  //FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, NB_LEDS_MAX);
  // pour utiliser une led adafruit neopixel
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NB_LEDS_MAX);
  FastLED.setBrightness(50);
  
  nbLeds=8;
  
  ledStatus=true;
  indexLed=0;

  indexColor=0;
  
  animBlinkColor=CRGB::Blue;
  animBlinkSerpent=CRGB::Red;

  animSerpentIndex=0;
  
  anim=ANIM_NONE;
}


void M_fastled::ledOn(int cLed, CRGB cCouleur)
{
  leds[cLed] = cCouleur;
  FastLED.show();
}

void M_fastled::allLedOn(CRGB cCouleur)
{ 
  for (int i=0;i<nbLeds;i++)
  {
    leds[i] = cCouleur;
  }
  FastLED.show();
}

void M_fastled::allLedOff()
{
  FastLED.clear();
  FastLED.show();
}

void M_fastled::setLed(int cLed, CRGB cCouleur)
{
  leds[cLed] = cCouleur;
}

void M_fastled::ledShow()
{
  FastLED.show();
}
  
void M_fastled::setNbLed(uint8_t nbLedsInit)
{
	nbLeds = nbLedsInit;
}

uint8_t M_fastled::getNbLed()
{
	return(nbLeds);
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
      // Serial.print("task neopixel DISABLE  ");
	  // Serial.print(millis());
      // Serial.println();
	  anim=ANIM_NONE;

      switch (anim) 
      {
        case ANIM_BLINK:
          // nothing to do
        break;
		
        default:
          // nothing to do
        break;
      }
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

  void M_fastled::startAnimBlink()
  {
    setInterval(500);
    setIterations(TASK_FOREVER);
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
      if (ledStatus)
      {
        ledOn(indexLed, animBlinkColor);
      }
      else
      {
        ledOn(indexLed, CRGB::Black);
      }

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