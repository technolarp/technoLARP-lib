#include <Arduino.h>
#include <TM1637Display.h>

#define CLK_PIN D5
#define DIO_PIN D3

class M_7segment
{
  private:
	
  public:  
	M_7segment();
	
	void showDecimal(uint16_t aDecimal, bool leadingZero);
};
