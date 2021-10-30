# AT PID regulator

This directory contains simple AT and I/O command configured PID regulator.

### Features

  - control devices with a computer via USB

### AT commands

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

### I/O commands

    00 XX              read analog input (where XX is between 00..05 for Arduino Uno), example: 00 00 reads A0 analog input
    01 XX              read analog input voltage (where XX is between 00..05 for Uno), example: 01 00 reads A0 analog input voltage
    02 XX              read output value

### Defaults

  - echo is enabled by default
  - linefeed is off (Carriage Return as ending char)
  - EEPROM memory is on
  - monitor is off
  - PID mode is PWM
  - KP = 1.0, KI = 0.0, KD = 0.0
  - PID sample time is 100ms