#include "pins.h"

bool checkDigitalPin(int pin)
{
  const int pins[20] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
  int i;
  for (i = 0; i < 20; i++)
  {
    if (pin == pins[i])
    {
      return true;
    }
  }
  return false;
}

bool checkAnalogPin(int pin)
{
  const int pins[6] = {14, 15, 16, 17, 18, 19};
  int i;
  for (i = 0; i < 6; i++)
  {
    if (pin == pins[i])
    {
      return true;
    }
  }
  return false;
}

bool checkPWMPin(int pin)
{
  const int pins[6] = {3, 5, 6, 9, 10, 11};
  int i;
  for (i = 0; i < 6; i++)
  {
    if (pin == pins[i])
    {
      return true;
    }
  }
  return false;
}

bool checkPWM16Pin(int pin)
{
  const int pins[2] = {9, 10};
  int i;
  for (i = 0; i < 2; i++)
  {
    if (pin == pins[i])
    {
      return true;
    }
  }
  return false;
}

bool checkNotBusyPin(int pin, int sp, int in, int out)
{
  return ((pin != sp) && (pin != in) && (pin != out));
}
