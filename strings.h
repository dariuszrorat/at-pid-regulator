#ifndef STRINGS_H
#define STRINGS_H

#include <arduino.h>

String boolToString(bool b, String valueTrue, String valueFalse);
String floatToString(float val);
String trimAll(String s);
String getParam(String data, char separator, int index);

#endif



