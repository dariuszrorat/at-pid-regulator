#include "pwmio.h"

void setupPWM16()
{
  TCCR1A = (TCCR1A & B00111100) | B10000010;
  TCCR1B = (TCCR1B & B11100000) | B00010001;
  ICR1 = 0xFFFF;
}

void analogWrite16(int pin, uint16_t value)
{
  switch (pin)
  {
    case 9: OCR1A = value; break;
    case 10: OCR1B = value; break;
  }
}