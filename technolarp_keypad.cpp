#include "technolarp_keypad.h"



const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {4, 5, 6, 7}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {0, 1, 2, 3}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad_I2C customKeypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS, I2CADDR); 


M_keypad::M_keypad()
{
  Wire.begin();
  customKeypad.begin();
  
  customKeypad.setHoldTime(2000);
  
  for (int i=0;i<4;i++)
  {
	  uneFoisFlag[i] = true;
  }
  
}

char M_keypad::getChar()
{
	return(customKeypad.getKey());
}

bool M_keypad::checkReset(char toCheck)
{
	bool checkFlag = false;
	
	customKeypad.getKeys();
    
    int indexStar = customKeypad.findInList(toCheck);
	
	if (indexStar>=0)
	{
		if ( 	(customKeypad.key[indexStar].kstate==PRESSED) || 
				(customKeypad.key[indexStar].kstate==HOLD) )
		{
			checkFlag = true;
		}
	}
	
	return(checkFlag);
}

bool M_keypad::checkCombo(char touche1, char touche2, uint8_t flagIndex)
{
	bool checkFlag = false;
	
	//customKeypad.getKeys();
    
    int indexTouche1 = customKeypad.findInList(touche1);
	int indexTouche2 = customKeypad.findInList(touche2);
	
	if ( (indexTouche1>=0) && (indexTouche2>=0) )
	{
		if ( 	(customKeypad.key[indexTouche1].kstate==HOLD) && 
				(customKeypad.key[indexTouche2].kstate==HOLD) &&
				uneFoisFlag[flagIndex] )
		{
			checkFlag = true;
			uneFoisFlag[flagIndex] = false;
		}
	}
	else
	{
		uneFoisFlag[flagIndex] = true;
	}	
	
	return(checkFlag);
}

bool M_keypad::getUneFoisFlag(uint8_t index)
{
	return(uneFoisFlag[index]);
}