#include <Arduino.h>
#include <TM1637Display.h>

#define CLK_PIN D5
#define DIO_PIN D3

class M_7segment
{
  private:
	bool blinkDoublePoint;
	bool blinkAffichage;
	bool blinkMinutesOuSecondes;
	
  public:  
	M_7segment();
	
	void showDecimal(uint16_t aDecimal, bool leadingZero);
	void setDoublePoint(bool toSet);
	bool getDoublePoint();
	
	void showTempsRestant(int16_t tempsRestant);
	
	void showExplosion();
	void showExplosee();
	void showSafe();
	
	void setBlinkAffichage(bool toSet);
	bool getBlinkAffichage();
	void setBlinkMinutesOuSecondes(bool toSet);
	bool getBlinkMinutesOuSecondes();
};
