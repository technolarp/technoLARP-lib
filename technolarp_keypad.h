#include <Keypad_I2C.h>  // https://github.com/joeyoung/arduino_keypads.git
#include <Keypad.h>  // https://github.com/Chris--A/Keypad
#include <Wire.h>

#define I2CADDR 0x27


class M_keypad
{
  private:
	bool uneFoisFlag[4];
	
	
	
  public:  
	M_keypad();
	
	char getChar();
	bool checkReset(char toCheck);
	bool checkCombo(char touche1, char touche2, uint8_t flagIndex);
	bool getUneFoisFlag(uint8_t index);
};
