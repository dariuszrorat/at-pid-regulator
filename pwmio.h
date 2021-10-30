#ifndef PWMIO_H
#define PWMIO_H

#include <arduino.h>

void setupPWM16();
void analogWrite16(int pin, uint16_t value);

#endif
