#include <Arduino.h>

// OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>       // https://github.com/adafruit/Adafruit-GFX-Library
#include <Adafruit_SSD1306.h>   // https://github.com/adafruit/Adafruit_SSD1306

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1



class M_oled
{
  private:
	
	
	bool screenDirty = true;
	
  public:  
	M_oled();
	
	void showDecimal();
	void displayText(String texteAAfficher, int taillePolice, bool videEcran, bool changementEcran, bool centered, bool crlf);
};
