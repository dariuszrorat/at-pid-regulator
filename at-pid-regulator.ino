/*
    AT Command interpreter for Arduino Uno R3

    AT commands:

    AT I                print ID general
    AT Z                reset terminal
    AT D                set all to defaults
    AT E0               turn echo off
    AT E1               turn echo on
    AT L0               linefeed off
    AT L1               linefeed on
    AT P0               PID off
    AT P1               PID on
    AT LS               load stored settings from EEPROM memory
    AT M0               memory off
    AT M1               memory on
    AT MA               monitor all
    AT MD               disable monitor
    AT SMI TTTT         set monitor interval ms
    AT PS               print settings
    AT SKP XXXX         set P divided by 100
    AT SKI XXXX         set I divided by 100
    AT SKD XXXX         set D divided by 100
    AT SPE X            set proportional measurement 0 or error 1
    AT SPD X            set PID direction, 0 = direct, 1 = reverse
    AT SPM X            set PID mode, 0 = PWM, 1 = PWM16, 2 = SSR
    AT SRH X            set relay high state 0 or 1
    AT SRW TTTT         set relay window size ms
    AT SST TTTT         set PID sample time ms
    AT SPI X            set input analog pin
    AT SPS X            set setpoint analog pin
    AT SPO X            set output analog pin
    AT SIS X            set use input as setpoint
    AT SP X             set digital pin to 0 or 1
    AT SD XXXX          set desired input value
    AT SS               store settings to EEPROM memory

    I/O commands:

    00 XX              read analog input (where XX is between 00..05 for Arduino Uno), example: 00 00 reads A0 analog input
    01 XX              read analog input voltage (where XX is between 00..05 for Uno), example: 01 00 reads A0 analog input voltage
    02 XX              read output value
*/

#include <PID_v1.h>

#include "typedefs.h"
#include "pwmio.h"
#include "atcallbacks.h"
#include "iocallbacks.h"

String inputString = "";
String outputString = "";
boolean stringComplete = false;
GeneralSettings settings;
ValueData values;

int setpointValue = 0;
unsigned long windowStartTime;

double Setpoint = 0, Input = 0, Output = 0;
double Kp = 1.0, Ki = 0.0, Kd = 0.0;

PID pid(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

unsigned int counter = 0;

void setup()
{
  Serial.begin(9600);
  inputString.reserve(200);
  Serial.print(">");

  //initialize general settings
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
  values.pidSettingsChanged = false;

  pid.SetTunings(settings.Kp, settings.Ki, settings.Kd, settings.pOnE);
  pid.SetControllerDirection(settings.controllerDirection);
  pid.SetSampleTime(settings.sampleTime);
  pid.SetMode(AUTOMATIC);

  windowStartTime = millis();
}

void loop()
{
  if (stringComplete)
  {
    inputString.trim();
    inputString.toUpperCase();
    doCommand(inputString);

    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  doPID();
  doMonitoring();
}

// private methods

void doCommand(String input)
{
  if (settings.echoMode)
  {
    Serial.println(input);
  }

  if (input.length() < 2)
  {
    Serial.println("Unrecognized command");
    Serial.print(">");
    return;
  }

  String id = input.substring(0, 2);
  String params;
  String answer;

  if (id == "AT")
  {
    params = input.substring(2);
    params.trim();
    answer = processATCommand(params, settings, values);
  }
  else
  {
    answer = processIOCommand(input, settings, values);
  }

  Serial.println(answer);
  Serial.print(">");
}

void doPID()
{
  if (values.pidSettingsChanged)
  {
    pid.SetTunings(settings.Kp, settings.Ki, settings.Kd, settings.pOnE);
    pid.SetControllerDirection(settings.controllerDirection);
    pid.SetSampleTime(settings.sampleTime);
    switch (settings.pidMode)
    {
      case 0: pid.SetOutputLimits(0, 255); break;
      case 1: {
          pid.SetOutputLimits(0, 65535);
          setupPWM16();
        } break;
      case 2: pid.SetOutputLimits(0, settings.windowSize); break;
    }
    windowStartTime = millis();
    values.pidSettingsChanged = false;
  }

  if (settings.pidEnabled)
  {

    Setpoint = values.setpoint;
    Input = analogRead(settings.pinInput);
    values.input = Input;
    pid.Compute();
    values.output = Output;

    switch (settings.pidMode)
    {
      case 0:
        {
          analogWrite(settings.pinOutput, Output);
        }
        break;
      case 1:
        {
          analogWrite16(settings.pinOutput, Output);
        }
        break;
      case 2:
        {
          if (millis() - windowStartTime > settings.windowSize)
          {
            windowStartTime += settings.windowSize;
          }
          if (Output < millis() - windowStartTime)
          {
            digitalWrite(settings.pinOutput, (1 - settings.relayHigh));
          }
          else
          {
            digitalWrite(settings.pinOutput, settings.relayHigh);
          }
        }
        break;
    }

  }
}

void doMonitoring()
{
  if (settings.monitorAll)
  {
    if ((counter % settings.monitorInterval) == 0)
    {
      Serial.println("Setpoint: " + String(values.setpoint) + " Input: " + String(values.input) + " Output: " + String(values.output));
    }
    delay(1);
    counter++;
  }
}

void serialEvent()
{
  char endChar = settings.linefeed ? '\n' : '\r';
  while (Serial.available())
  {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == endChar)
    {
      stringComplete = true;
    }
  }
}
