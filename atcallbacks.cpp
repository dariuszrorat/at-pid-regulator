#include "atcallbacks.h"
#include "strings.h"

#include <EEPROM.h>

String processATCommand(const String command, GeneralSettings & settings, ValueData &values)
{
  String param0 = getParam(command, ' ', 0);
  String param1 = getParam(command, ' ', 1);
  String param2 = getParam(command, ' ', 2);

  if (param0 == "I") return printIdGeneral(param1, param2, settings, values);
  if (param0 == "Z") return resetTerminal(param1, param2, settings, values);
  if (param0 == "D") return setDefaults(param1, param2, settings, values);
  if (param0 == "E0") return turnEchoOff(param1, param2, settings, values);
  if (param0 == "E1") return turnEchoOn(param1, param2, settings, values);
  if (param0 == "L0") return turnLinefeedOff(param1, param2, settings, values);
  if (param0 == "L1") return turnLinefeedOn(param1, param2, settings, values);
  if (param0 == "P0") return turnPIDOff(param1, param2, settings, values);
  if (param0 == "P1") return turnPIDOn(param1, param2, settings, values);
  if (param0 == "LS") return loadSettingsFromEEPROM(param1, param2, settings, values);
  if (param0 == "M0") return turnMemoryOff(param1, param2, settings, values);
  if (param0 == "M1") return turnMemoryOn(param1, param2, settings, values);
  if (param0 == "MA") return enableAnalogInputMonitoring(param1, param2, settings, values);
  if (param0 == "MD") return disableAnalogInputMonitoring(param1, param2, settings, values);
  if (param0 == "SMI") return setMonitorInterval(param1, param2, settings, values);
  if (param0 == "PS") return printSettings(param1, param2, settings, values);
  if (param0 == "SKP") return setKPValue(param1, param2, settings, values);
  if (param0 == "SKI") return setKIValue(param1, param2, settings, values);
  if (param0 == "SKD") return setKDValue(param1, param2, settings, values);
  if (param0 == "SPE") return setPonEValue(param1, param2, settings, values);
  if (param0 == "SPD") return setDirectionValue(param1, param2, settings, values);
  if (param0 == "SPM") return setPIDMode(param1, param2, settings, values);
  if (param0 == "SRH") return setRelayHigh(param1, param2, settings, values);
  if (param0 == "SRW") return setRelayWindow(param1, param2, settings, values);
  if (param0 == "SST") return setSampleTime(param1, param2, settings, values);
  if (param0 == "SPI") return setInputPin(param1, param2, settings, values);
  if (param0 == "SPS") return setSetpointPin(param1, param2, settings, values);
  if (param0 == "SPO") return setOutputPin(param1, param2, settings, values);
  if (param0 == "SIS") return setInputAsSetpoint(param1, param2, settings, values);
  if (param0 == "SP") return setDigitalPin(param1, param2, settings, values);
  if (param0 == "SD") return setDesiredInput(param1, param2, settings, values);
  if (param0 == "SS") return saveSettingsToEEPROM(param1, param2, settings, values);

  return "Unrecognized AT command";

}

// existing AT callbacks

String printIdGeneral(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  return ID_GENERAL;
}

String resetTerminal(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.echoMode = true;
  settings.linefeed = false;
  settings.memory = true;
  settings.monitorAll = false;
  settings.monitorInterval = 500;
  settings.pinInput = A0;
  settings.pinSetpoint = A1;
  settings.pinOutput = 9;
  settings.inputAsSetpoint = 0;
  settings.pidMode = 0;
  settings.windowSize = 5000;
  settings.sampleTime = 100;
  settings.relayHigh = 1;
  settings.Kp = 1.0;
  settings.Ki = 0.0;
  settings.Kd = 0.0;
  settings.pOnE = 1;
  settings.controllerDirection = 0;
  settings.pidEnabled = false;
  values.input = 0;
  values.setpoint = 0;
  values.output = 0;
  values.pidSettingsChanged = true;

  return "Terminal has been reset";
}

String setDefaults(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.echoMode = true;
  settings.linefeed = false;
  settings.memory = true;
  settings.monitorInterval = 500;
  settings.pinInput = A0;
  settings.pinSetpoint = A1;
  settings.pinOutput = 9;
  settings.inputAsSetpoint = 0;
  settings.pidMode = 0;
  settings.windowSize = 5000;
  settings.sampleTime = 100;
  settings.relayHigh = 1;
  settings.Kp = 1.0;
  settings.Ki = 0.0;
  settings.Kd = 0.0;
  settings.pOnE = 1;
  settings.controllerDirection = 0;
  values.pidSettingsChanged = true;

  return "OK";
}

String turnEchoOff(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.echoMode = false;
  return "OK";
}

String turnEchoOn(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.echoMode = true;
  return "OK";
}

String turnLinefeedOff(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.linefeed = false;
  return "OK";
}

String turnLinefeedOn(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.linefeed = true;
  return "OK";
}

String turnPIDOff(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.pidEnabled = false;
  values.output = 0;

  return "OK";
}

String turnPIDOn(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.pidEnabled = true;
  return "OK";
}


String loadSettingsFromEEPROM(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (!settings.memory)
  {
    return "EEPROM is off";
  }
  //load settings
  EEPROM.get(0, settings);
  values.pidSettingsChanged = true;

  return "OK";
}

String turnMemoryOff(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.memory = false;
  return "OK";
}

String turnMemoryOn(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.memory = true;
  return "OK";
}

String enableAnalogInputMonitoring(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.monitorAll = true;
  return "OK";
}

String disableAnalogInputMonitoring(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  settings.monitorAll = false;
  return "OK";
}

String printSettings(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  String result = "";
  result += "KP            : " + String(settings.Kp) + "\n";
  result += "KI            : " + String(settings.Ki) + "\n";
  result += "KD            : " + String(settings.Kd) + "\n";
  switch (settings.pidMode)
  {
    case 0: result += "MODE          : PWM"; break;
    case 1: result += "MODE          : PWM16"; break;
    case 2: result += "MODE          : SSR"; break;
  }
  return result;
}

String setMonitorInterval(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.monitorInterval = (unsigned int) param1.toInt();
  if (settings.monitorInterval == 0)
  {
    settings.monitorInterval = 1;
    return "Illegal monitor interval";
  }
  return "OK";
}

String setKPValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.Kp = (double) limitValue(param1.toInt(), 0, 2147483647) / 100.00;
  values.pidSettingsChanged = true;
  return "OK";
}

String setKIValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.Ki = (double) limitValue(param1.toInt(), 0, 2147483647) / 100.00;
  values.pidSettingsChanged = true;
  return "OK";
}

String setKDValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.Kd = (double) limitValue(param1.toInt(), 0, 2147483647) / 100.00;
  values.pidSettingsChanged = true;
  return "OK";
}

String setPonEValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.pOnE = limitValue(param1.toInt(), 0, 1);
  values.pidSettingsChanged = true;
  return "OK";
}

String setDirectionValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.controllerDirection = limitValue(param1.toInt(), 0, 1);
  values.pidSettingsChanged = true;

  return "OK";
}

String setPIDMode(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.pidMode = limitValue(param1.toInt(), 0, 2);
  values.pidSettingsChanged = true;

  return "OK";
}

String setRelayHigh(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.relayHigh = limitValue(param1.toInt(), 0, 1);
  return "OK";
}

String setRelayWindow(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.windowSize = limitValue(param1.toInt(), 50, 32767);
  values.pidSettingsChanged = true;

  return "OK";
}

String setSampleTime(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.sampleTime = limitValue(param1.toInt(), 50, 32767);
  values.pidSettingsChanged = true;
  return "OK";
}

String setInputPin(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  int pin = param1.toInt();
  if (!checkAnalogPin(pin))
  {
    return "Invalid analog pin";
  }

  settings.pinInput = pin;
  return "OK";
}

String setSetpointPin(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  int pin = param1.toInt();
  if (!checkAnalogPin(pin))
  {
    return "Invalid analog pin";
  }

  settings.pinSetpoint = pin;
  return "OK";
}

String setOutputPin(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  int pin = param1.toInt();
  switch (settings.pidMode)
  {
    case 0:
      if (!checkPWMPin(pin))
      {
        return "Invalid PWM pin";
      }
      break;
    case 1:
      if (!checkPWM16Pin(pin))
      {
        return "Invalid PWM16 pin";
      }
      break;
    case 2:
      if (!checkDigitalPin(pin))
      {
        return "Invalid digital pin";
      }
      break;
  }
  settings.pinOutput = pin;
  return "OK";
}

String setInputAsSetpoint(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  settings.inputAsSetpoint = limitValue(param1.toInt(), 0, 1);
  return "OK";
}

String setDigitalPin(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  int pin = param1.toInt();
  if (!checkDigitalPin(pin))
  {
    return "Invalid digital pin";
  }
  int value = param2.toInt();
  pinMode(pin, OUTPUT);
  digitalWrite(pin, value);
  return "OK";
}

String setDesiredInput(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (param1.length() == 0)
  {
    return "Empty or Invalid param value";
  }

  values.setpoint = (double) limitValue(param1.toInt(), 0, 1023);
  return "OK";
}


String saveSettingsToEEPROM(const String param1, const String param2, GeneralSettings & settings, ValueData &values)
{
  if (!settings.memory)
  {
    return "EEPROM is off";
  }
  EEPROM.put(0, settings);
  return "OK";
}
