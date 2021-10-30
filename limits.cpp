#include "limits.h"

long limitValue(long value, long lo, long hi)
{
  return (value > hi) ? hi : ((value < lo) ? lo : value);
}

unsigned long limitUintValue(unsigned long value, unsigned long lo, unsigned long hi)
{
  return (value > hi) ? hi : ((value < lo) ? lo : value);
}
