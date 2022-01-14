#include "technolarp_mcp23017.h"

M_mcp23017::M_mcp23017()
{
	
}

void M_mcp23017::beginMcp23017(uint8_t mcpAddress)
{
	if (mcpAddress==0)
	{
		mcp.begin_I2C();
	}
	else
	{
		mcp.begin_I2C(mcpAddress);
	}
  delay(100);
	
  for (int i=0;i<16;i++)
  {
    mcp.pinMode(i, INPUT_PULLUP);
  }
}

// inspired by https://learn.adafruit.com/make-it-switch/debouncing
bool M_mcp23017::checkButton(uint8_t button)
{
  // read the state of the switch into a local variable:
  int reading = mcp.digitalRead(button);
 
  // if the switch changed, due to noise or pressing:
  if (reading != lastButtonState[button-FIRST_BOUTON])
  {
    // reset the debouncing timer
    lastDebounceTime[button-FIRST_BOUTON] = millis();
  }
 
  if ((millis() - lastDebounceTime[button-FIRST_BOUTON]) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
 
    // if the button state has changed:
    if (reading != buttonState[button-FIRST_BOUTON]) 
    {
      buttonState[button-FIRST_BOUTON] = reading;
 
      // only toggle the LED if the new button state is HIGH
      if (buttonState[button-FIRST_BOUTON] == HIGH) 
      {
        return(true);
      }
    }
  } 
  
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState[button-FIRST_BOUTON] = reading;
  return(false);
}

// inspired by https://learn.adafruit.com/make-it-switch/debouncing
bool M_mcp23017::checkPin(uint8_t pin)
{
  // read the state of the switch into a local variable:
  int reading = mcp.digitalRead(pin);
 
  // if the switch changed, due to noise or pressing:
  if (reading != lastButtonState[pin])
  {
    // reset the debouncing timer
    lastDebounceTime[pin] = millis();
  }
 
  if ((millis() - lastDebounceTime[pin]) > debounceDelay)
  {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
 
    // if the button state has changed:
    if (reading != buttonState[pin]) 
    {
      buttonState[pin] = reading;
 
      if (buttonState[pin] == HIGH) 
      {
        return(true);
      }
    }
  } 
  
  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState[pin] = reading;
  return(false);
}

bool M_mcp23017::readPin(uint8_t pin)
{
	return(mcp.digitalRead(pin));
}

uint16_t M_mcp23017::getDebounceDelay()
{
	return(debounceDelay);
}

void M_mcp23017::setDebounceDelay(uint16_t toSet)
{
	debounceDelay=toSet;
}
