#include <Keypad_I2C.h>  // https://github.com/joeyoung/arduino_keypads.git
#include <Keypad.h>  // https://github.com/Chris--A/Keypad
#include <Wire.h>

#define I2CADDR 0x27





class M_keypad
{
  private:
	
	
	
	
  public:  
	M_keypad();
	
	char getChar();
};
