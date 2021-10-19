#include "technolarp_7segment.h"

// init display TM1637
TM1637Display display_7seg(CLK_PIN, DIO_PIN);

M_7segment::M_7segment()
{
  display_7seg.setBrightness(0x0b);
  display_7seg.clear();
  
  blinkDoublePoint = false;
  blinkAffichage = true;
  blinkMinutesOuSecondes = true;
}


void M_7segment::showDecimal(uint16_t aDecimal, bool leadingZero)
{
	display_7seg.showNumberDec(aDecimal, leadingZero);
}

void M_7segment::setDoublePoint(bool toSet)
{
	blinkDoublePoint = toSet;
}

bool M_7segment::getDoublePoint()
{
	return(blinkDoublePoint);
}
	
void M_7segment::setBlinkAffichage(bool toSet)
{
	blinkAffichage = toSet;
}

bool M_7segment::getBlinkAffichage()
{
	return(blinkAffichage);
}

void M_7segment::setBlinkMinutesOuSecondes(bool toSet)
{
	blinkMinutesOuSecondes = toSet;
}

bool M_7segment::getBlinkMinutesOuSecondes()
{
	return(blinkMinutesOuSecondes);
}

void M_7segment::showTempsRestant(int16_t tempsRestant)
{
  uint8_t data[] = { 0x00, 0x00, 0x00, 0x00 };
  uint8_t minutes=tempsRestant/60;
  uint8_t seconds=tempsRestant%60;

  data[0] = display_7seg.encodeDigit(minutes/10);
  data[1] = display_7seg.encodeDigit(minutes%10) | 0x80;
  data[2] = display_7seg.encodeDigit(seconds/10);
  data[3] = display_7seg.encodeDigit(seconds%10);
  
  
  if (blinkAffichage)
  {
    if(blinkMinutesOuSecondes)
    {
      data[0] = 0x00;
      data[1] = 0x80;
    }
    else
    {
      data[2] = 0x00;
      data[3] = 0x00;    
    }
  }
  
  if (blinkDoublePoint)
  {
	data[1] = display_7seg.encodeDigit(minutes%10);
  }
  
  display_7seg.setSegments(data);
}


void M_7segment::showExplosion()
{
  uint8_t SEG_VIDE[] = {0x00, 0x00, 0x00, 0x00};
  uint8_t SEG_BOOM[] = {0x7C, 0x5C, 0x5C, 0x54}; // b, o, o, n
	
  if (blinkAffichage)
  {
	display_7seg.setSegments(SEG_BOOM, 4, 0);
  }
  else
  {
	display_7seg.setSegments(SEG_VIDE, 4, 0);
  }
}

void M_7segment::showExplosee()
{
  // la bombe a deja explosee
  // afficher "- - - -" sur le 4*7segment
  uint8_t SEG_EXPLOSEE[] = {SEG_G, SEG_G, SEG_G, SEG_G};
  display_7seg.setSegments(SEG_EXPLOSEE);
}

void M_7segment::showSafe()
{
  // la bombe a deja explosee
  // afficher "S A F E" sur le 4*7segment
  uint8_t SEG_SAFE[] = {0x6D, 0x77, 0x71, 0x79};
  display_7seg.setSegments(SEG_SAFE);
}
