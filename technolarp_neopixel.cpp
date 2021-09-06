#include "technolarp_neopixel.h"


M_neopixel::M_neopixel(Scheduler* aScheduler) : Task(TASK_MILLISECOND*100, TASK_FOREVER, aScheduler, false)
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


void M_neopixel::ledOn(int cLed, CRGB cCouleur)
{
  leds[cLed] = cCouleur;
  FastLED.show();
}

void M_neopixel::allLedOn(CRGB cCouleur)
{ 
  for (int i=0;i<nbLeds;i++)
  {
    leds[i] = cCouleur;
  }
  FastLED.show();
}

void M_neopixel::allLedOff()
{
  FastLED.clear();
  FastLED.show();
}

void M_neopixel::setLed(int cLed, CRGB cCouleur)
{
  leds[cLed] = cCouleur;
}

void M_neopixel::ledShow()
{
  FastLED.show();
}
  
void M_neopixel::setNbLed(uint8_t nbLedsInit)
{
	nbLeds = nbLedsInit;
}

uint8_t M_neopixel::getNbLed()
{
	return(nbLeds);
}

	
bool M_neopixel::Callback()
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
    
    bool M_neopixel::OnEnable()
    {
      // Serial.print("task neopixel ENABLE  ");
	  // Serial.print(millis());
      // Serial.println();
      allLedOff();
      return true;
     
    }
    
	void M_neopixel::OnDisable()
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
    
	
	void M_neopixel::moveLed()
	{
		M_neopixel::ledOn(indexLed,CRGB::Black);
		
		indexLed+=1;
		indexLed%=nbLeds;
		ledStatus=true;
		forceNextIteration();
	}

  void M_neopixel::changeColor()
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
  
  void M_neopixel::changeColor(CRGB cCouleur)
  {
    animBlinkColor=cCouleur;
  }
	
	void M_neopixel::setIndexLed(uint8_t aLed)
	{
    indexLed=aLed%nbLeds;
  }
	
	uint8_t M_neopixel::getIndexLed()
	{
    return(indexLed);
  }

  void M_neopixel::startAnimBlink()
  {
    setInterval(500);
    setIterations(TASK_FOREVER);
    forceNextIteration();
    anim=ANIM_BLINK;
    
    enable();
  }
   
	void M_neopixel::startAnimSerpent(uint8_t startLed, uint16_t nbRun, uint16_t delayLed, CRGB color)
	{
		setInterval(delayLed);
		setIterations(nbRun*nbLeds);
		forceNextIteration();
		anim=ANIM_SERPENT;
		animBlinkSerpent=color;
		animSerpentIndex=startLed;
		
		enable();
	}
  
	void M_neopixel::startAnimSerrureBloquee(uint16_t nbRun, uint16_t delaiBlink)
	{
		setInterval(delaiBlink);
		setIterations(nbRun+1);
		
		anim=ANIM_SERRURE_BLOQUEE;
		
		enableIfNot();
		forceNextIteration();		
	}
	
	void M_neopixel::startAnimSerrureErreur(uint16_t nbRun, uint16_t delaiBlink)
	{
		setInterval(delaiBlink);
		setIterations(nbRun+1);
		
		anim=ANIM_SERRURE_ERREUR;
		
		enableIfNot();
		forceNextIteration();		
	}

	void M_neopixel::animBlink()
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
  
	void M_neopixel::animSerpent()
    {
      ledOn(animSerpentIndex, CRGB::Black);
      animSerpentIndex++;
      animSerpentIndex%=nbLeds;
      ledOn(animSerpentIndex, animBlinkSerpent);
    }

	void M_neopixel::animSerrureBloquee()
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
	
	

	void M_neopixel::animSerrureErreur()
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
	
	
	bool M_neopixel::isAnimActive()
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