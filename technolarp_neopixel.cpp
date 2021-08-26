#include "technolarp_neopixel.h"


M_neopixel::M_neopixel(Scheduler* aScheduler) : Task(TASK_MILLISECOND*100, TASK_FOREVER, aScheduler, false)
{
  // pour utiliser une led ws2811
  //FastLED.addLeds<WS2811, LED_DATA_PIN>(leds, NB_LEDS);
  // pour utiliser une led adafruit neopixel
  FastLED.addLeds<NEOPIXEL, LED_DATA_PIN>(leds, NB_LEDS);
  FastLED.setBrightness(50);
  
  ledStatus=true;
  indexLed=0;

  indexColor=0;
  
  animBlinkColor=CRGB::Blue;
  animBlinkSerpent=CRGB::Red;

  animSerpentIndex=0;
  
  anim=ANIM_BLINK;
}


void M_neopixel::ledOn(int cLed, CRGB cCouleur)
{
  leds[cLed] = cCouleur;
  FastLED.show();
}

void M_neopixel::allLedOn(CRGB cCouleur)
{ 
  for (int i=0;i<NB_LEDS;i++)
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
      //Serial.println("task neopixel ENABLE");
      allLedOff();
      return true;
     
    }
    
	void M_neopixel::OnDisable()
    {
      //Serial.println("task neopixel DISABLE");

      switch (anim) 
      {
        case ANIM_BLINK:
          // nothing to do
        break;
		
        case ANIM_SERPENT:
          //startAnimBlink();
        break;
		
		case ANIM_SERRURE_BLOQUEE:
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
		indexLed%=NB_LEDS;
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
    indexLed=aLed%NB_LEDS;
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
   
	void M_neopixel::startAnimSerpent(uint8_t startLed, uint8_t nbRun, uint8_t delayLed, CRGB color)
	{
		setInterval(delayLed);
		setIterations(nbRun*NB_LEDS);
		forceNextIteration();
		anim=ANIM_SERPENT;
		animBlinkSerpent=color;
		animSerpentIndex=startLed;
		
		enable();
	}
  
	void M_neopixel::startAnimSerrureBloquee(uint8_t delaiBloquage)
	{
		setInterval(200);
		setIterations(delaiBloquage*1000/getInterval());
		//setIterations(30);
		forceNextIteration();
		anim=ANIM_SERRURE_BLOQUEE;
		
		enableIfNot();
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
      animSerpentIndex%=NB_LEDS;
      ledOn(animSerpentIndex, animBlinkSerpent);
    }

	

	void M_neopixel::animSerrureBloquee()
	{
      for (int i=0;i<NB_LEDS;i++)
	  {
		if (i%2==0)
		{
			if (ledStatus)
			{
				ledOn(i, CRGB::Black);
			}
			else
			{
				ledOn(i, CRGB::Red);
			}
		}
		else
		{
		  if (ledStatus)
			{
				ledOn(i, CRGB::Green);
			}
			else
			{
				ledOn(i, CRGB::Black);
			}
		}
	  }

      ledStatus=!ledStatus;
    }
	
	void M_neopixel::startAnimSerrureErreur(uint8_t nbRun)
	{
		setInterval(200);
		setIterations(nbRun);
		forceNextIteration();
		anim=ANIM_SERRURE_ERREUR;
		
		enableIfNot();
	}

	void M_neopixel::animSerrureErreur()
	{
		for (int i=0;i<NB_LEDS;i++)
		{
			if (i%2==0)
			{
				if (ledStatus)
				{
					ledOn(i, CRGB::Black);
				}
				else
				{
					ledOn(i, CRGB::Red);
				}
			}
		}
		ledStatus=!ledStatus;
	}