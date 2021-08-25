#include "technolarp_7segment.h"

// init display TM1637
TM1637Display display_7seg(CLK_PIN, DIO_PIN);

M_7segment::M_7segment()
{
  display_7seg.setBrightness(0x0b);
  display_7seg.clear();
}


void M_7segment::showDecimal(uint16_t aDecimal, bool leadingZero)
{
	display_7seg.showNumberDec(aDecimal, leadingZero);
}
