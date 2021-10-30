#include "iocallbacks.h"

String processIOCommand(const String command, GeneralSettings settings, ValueData &values)
{
  String param0 = getParam(command, ' ', 0);
  String param1 = getParam(command, ' ', 1);
  String param2 = getParam(command, ' ', 2);
  String param3 = getParam(command, ' ', 3);

  if (param0 == "00") return analogReadInput(param1, param2, param3, settings, values);
  if (param0 == "01") return analogReadInputVoltage(param1, param2, param3, settings, values);
  if (param0 == "02") return analogReadOutput(param1, param2, param3, settings, values);

  return "Unrecognized I/O command";
}

// existing IO callbacks
String analogReadInput(const String param1, const String param2, const String param3, GeneralSettings settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  byte pin;
  unsigned int input;
  String stringVal = "";

  pin = (byte) param1.toInt();
  input = analogRead(pin);
  stringVal = String(input);

  return stringVal;
}

String analogReadInputVoltage(const String param1, const String param2, const String param3, GeneralSettings settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  byte pin;
  unsigned int input;
  String stringVal = "";
  float voltage = 0;

  pin = (byte) param1.toInt();
  voltage = (float) analogRead(pin) * 5.0 / 1023.0  ;
  stringVal = floatToString(voltage);
  return stringVal;
}

String analogReadOutput(const String param1, const String param2, const String param3, GeneralSettings settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  String stringVal = String(values.output);

  return stringVal;
}
