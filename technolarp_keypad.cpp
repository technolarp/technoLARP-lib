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
  customKeypad.begin( );
}

char M_keypad::getChar()
{
	return(customKeypad.getKey());
}

bool M_keypad::checkReset()
{
	bool charStar = false;
	bool charA = false;
	
	String msg;
	
	if (customKeypad.getKeys())
    {
        for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
        {
            Serial.print(i);
            Serial.print(": ");
			Serial.print(customKeypad.key[i].kchar);
			Serial.print("");
			
			
			
			if ( customKeypad.key[i].stateChanged )   // Only find keys that have changed state.
            {
                switch (customKeypad.key[i].kstate) {  // Report active key state : IDLE, PRESSED, HOLD, or RELEASED
                    case PRESSED:
                    msg = " PRESSED.";
                break;
                    case HOLD:
                    msg = " HOLD.";
                break;
                    case RELEASED:
                    msg = " RELEASED.";
                break;
                    case IDLE:
                    msg = " IDLE.";
                }
                Serial.print("Key ");
                Serial.print(customKeypad.key[i].kchar);
                Serial.print(msg);
            }
			
			Serial.println();
        }
    }
}


