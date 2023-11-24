# Security System Using LPC 1768 Microcontroller and a PIR Sensor

This repository contains the code and documentation for a security system implemented using an LPC 1768 microcontroller, incorporating a PIR sensor (HC-SR501 PIR Sensor), 4x4 keyboard interface, 16 x 2 LCD display interface, stepper motor, and buzzer for access control.

## Overview

This project focuses on creating a robust security mechanism that detects motion using the PIR sensor. Upon motion detection, the system prompts the user to input a password through the 4x4 keyboard. Correct authentication triggers the stepper motor to rotate in clockwise direction, indicating authorized access, while incorrect attempts activate the buzzer.

## Features

- Motion detection using Passive Infrared (PIR) sensor
- Password-based access control via keyboard interface
- Stepper motor activation for authorized access
- LCD Display for better user experience
- Buzzer alert for unauthorized attempts
- Developed on the Keil µVision IDE and debugger using C/C++ programming language
- Downloaded the code into the LPC 1768 Microcontroller using Flash Magic.

## Setup

The block diagram of the circuit showing the particular pins of LPC 1768 microcontroller that each device is connected to is given in the report that has been uploaded in the same repository.

## Usage
Refer to the video that has been uploaded in the same repository.
