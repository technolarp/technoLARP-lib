#include <Arduino.h>
#include <Wire.h>
//#include <Adafruit_MCP23017.h> // https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library
#include <Adafruit_MCP23X17.h> // https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library

#define BOUTON_1 8
#define BOUTON_2 9
#define BOUTON_3 10
#define BOUTON_4 11
#define BOUTON_5 12
#define BOUTON_6 13
#define BOUTON_7 14
#define BOUTON_8 15
#define FIRST_BOUTON 8

class M_mcp23017
{
  private:
	//Adafruit_MCP23017 mcp;
	Adafruit_MCP23X17 mcp;
  
	// BUTTON STATE
	int buttonState[16] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
	int lastButtonState[16] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH,HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};

	unsigned long lastDebounceTime[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint16_t debounceDelay = 50;

      
  public:  
	M_mcp23017();
	
	void beginMcp23017(uint8_t mcpAddress);
	
	bool checkButton(uint8_t button);
	bool checkPin(uint8_t pin);
	bool readPin(uint8_t pin);
	
	uint16_t getDebounceDelay();
	void setDebounceDelay(uint16_t toSet);
};
