#ifndef IOCALLBACKS_H
#define IOCALLBACKS_H

#include "typedefs.h"
#include "strings.h"

String processIOCommand(const String command, GeneralSettings settings, ValueData &values);

// existing IO callbacks
String analogReadInput(const String param1, const String param2, const String param3, GeneralSettings settings, ValueData &values);
String analogReadInputVoltage(const String param1, const String param2, const String param3, GeneralSettings settings, ValueData &values);
String analogReadOutput(const String param1, const String param2, const String param3, GeneralSettings settings, ValueData &values);

#endif

