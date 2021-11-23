#include "technolarp_oled.h"

// init oled display 128*64
Adafruit_SSD1306 display_oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

M_oled::M_oled()
{
  
}

void M_oled::beginOled()
{
  // OLED
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display_oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) // Address 0x3C for 128x32
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Clear the buffer
  display_oled.clearDisplay();

  // texte en blanc
  display_oled.setTextColor(SSD1306_WHITE);
}


void M_oled::showDecimal()
{
	
}

void M_oled::displayText(String texteAAfficher, int taillePolice, bool videEcran, bool changementEcran, bool centered, bool crlf)
{
  displayText(texteAAfficher, taillePolice, videEcran, changementEcran, centered, crlf, false);
}

void M_oled::displayText(String texteAAfficher, int taillePolice, bool videEcran, bool changementEcran, bool centered, bool crlf, bool inverted)
{
  if (inverted)
  {
	  display_oled.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
  }
  else
  {
	  display_oled.setTextColor(SSD1306_WHITE, SSD1306_BLACK);
  }
  
  if (videEcran)
  {
    display_oled.clearDisplay();
    display_oled.setCursor(0, 0);
  }

  display_oled.setTextSize(taillePolice);
  
  if (centered)
  {
    int16_t  x1, y1;
    uint16_t w, h;
    
    display_oled.getTextBounds(texteAAfficher, 0, 0, &x1, &y1, &w, &h);
  
    int newX = (SCREEN_WIDTH - w)/2;
    int newY = (SCREEN_HEIGHT - h)/2;
    
    display_oled.setCursor(newX, newY);
    display_oled.print(texteAAfficher);  
    display_oled.display();
  }
  else
  {
    display_oled.print(texteAAfficher);
  }
  
  if (crlf)
  {
    display_oled.println();
  }

  if(changementEcran)
  {
    display_oled.display();
  }
}


void M_oled::displayRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h)
{
	display_oled.drawRect(x0, y0, w, h, SSD1306_WHITE);
}

void M_oled::displayFillRect(uint16_t x0, uint16_t y0, uint16_t w, uint16_t h)
{
	display_oled.fillRect(x0, y0, w, h, SSD1306_WHITE);
}

void M_oled::display()
{
	display_oled.display();
}

void M_oled::clearDisplay()
{
	display_oled.clearDisplay();
    display_oled.setCursor(0, 0);
}

