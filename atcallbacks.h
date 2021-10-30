#ifndef ATCALLBACKS_H
#define ATCALLBACKS_H

#define ID_GENERAL "Arduino PID"

#include <PID_v1.h>
#include "typedefs.h"
#include "limits.h"
#include "pins.h"

String processATCommand(const String command, GeneralSettings & settings, ValueData &values);

// existing AT callbacks
String printIdGeneral(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String resetTerminal(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setDefaults(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String turnEchoOff(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String turnEchoOn(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String turnLinefeedOff(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String turnLinefeedOn(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String turnPIDOn(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String turnPIDOff(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String loadSettingsFromEEPROM(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String turnMemoryOff(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String turnMemoryOn(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String enableAnalogInputMonitoring(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String disableAnalogInputMonitoring(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setMonitorInterval(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setAnalogMonitorInterval(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String printSettings(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setKPValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setKIValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setKDValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setPonEValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setPIDMode(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setDirectionValue(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setRelayHigh(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setRelayWindow(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setSampleTime(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setInputPin(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setSetpointPin(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setOutputPin(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setInputAsSetpoint(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setDigitalPin(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String setDesiredInput(const String param1, const String param2, GeneralSettings & settings, ValueData &values);
String saveSettingsToEEPROM(const String param1, const String param2, GeneralSettings & settings, ValueData &values);

#endif
