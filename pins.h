#ifndef PINS_H
#define PINS_H

bool checkDigitalPin(int pin);
bool checkAnalogPin(int pin);
bool checkPWMPin(int pin);
bool checkPWM16Pin(int pin);
bool checkNotBusyPin(int pin, int sp, int in, int out);

#endif
