#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <arduino.h>

struct GeneralSettings
{
  bool echoMode;
  bool linefeed;
  bool monitorAll;
  bool memory;
  //monitoring
  unsigned int monitorInterval;
  //pid
  int pinInput;
  int pinOutput;
  int pinSetpoint;
  byte inputAsSetpoint;
  byte pidMode;
  int windowSize;
  int sampleTime;
  byte relayHigh;
  double Kp;
  double Ki;
  double Kd;
  byte pOnE;
  byte controllerDirection;
  bool pidEnabled;
};

struct ValueData
{
  double input;
  double setpoint;
  double output;
  bool pidSettingsChanged;
};

#endif
