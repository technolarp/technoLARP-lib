#include <FastLED.h>  // https://github.com/FastLED/FastLED  // VERSION 3.4.0

#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ALLOW_INTERRUPTS 0

#define NB_LEDS_MAX 50
#define LED_DATA_PIN D0

#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

class M_fastled : public Task
{
  private:
	uint8_t nbLeds;
	
	
	
	bool ledStatus;
	uint8_t indexLed;

	uint8_t indexColor;
  
	enum {ANIM_NONE, ANIM_BLINK, ANIM_SERPENT, ANIM_SERRURE_BLOQUEE, ANIM_SERRURE_ERREUR};
	uint8_t anim;
	
	CRGB animBlinkColor;
	CRGB animBlinkSerpent;  

	uint8_t animSerpentIndex;
      
  public:  
	M_fastled(Scheduler* aScheduler);
	
	// tableau de leds neopixel
	CRGB leds[NB_LEDS_MAX];

	bool Callback();
	bool OnEnable();
	void OnDisable();
	
	void ledOn(int cLed, CRGB cCouleur);
	void allLedOn(CRGB cCouleur);
	void allLedOff();
	
	void setNbLed(uint8_t nbLedsInit);
	uint8_t getNbLed();
	uint8_t getNbMaxLed();
	void setBrightness(uint8_t newBrightness);
	
	void setLed(int cLed, CRGB cCouleur);
	void ledShow();
	
	void setAnim(uint8_t anim);
			
	void moveLed();
	void changeColor();
	void changeColor(CRGB cCouleur);
 
	void setIndexLed(uint8_t aLed);
	uint8_t getIndexLed();

	void startAnimBlink(uint16_t nbRun, uint16_t delaiBlink, CRGB color, uint8_t nbLed);
	void startAnimSerpent(uint8_t startLed, uint16_t nbRun, uint16_t delayLed, CRGB color);
	void startAnimSerrureBloquee(uint16_t nbRun, uint16_t delaiBlink);
	void startAnimSerrureErreur(uint16_t nbRun, uint16_t delaiBlink);

	void animBlink();
	void animSerpent();
	void animSerrureBloquee();
	void animSerrureErreur();
	
	bool isAnimActive();

};
