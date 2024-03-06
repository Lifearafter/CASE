# Project Structure

## Overview

The project is structured as follows:

```
Project_Root/
├── Core/
│   ├── Inc/
│   ├── Src/
│   └── Startup/
├── Drivers/
│   ├── STM32xxxx_HAL_Driver/
│   ├── Peripherals/
│   │   ├── GPS_Driver/
│   │   ├── LM75A_Driver/
│   │   ├── INA225_Driver/
│   │   ├── ADXL345_Driver/
│   └── ...
├── Middlewares/
│   └── FreeRTOS/
├── Application/
│   ├── Inc/
│   ├── Src/
│   ├── Tasks/
│   │   ├── vReadGPS/
│   │   ├── vTelemetry/
│   │   └── ...
│   └── main.c
├── Docs/
├── Build/
├── Debug/
└── ...

```

## Core

The Core directory contains the main function files, startup file, and the header and source files for the core peripherals. The startup file is the same for all STM32F4xx devices, and the header and source files for the core peripherals are device specific.

## Drivers

The Drivers directory contains the header and source files for the device specific peripherals. The header files are device specific, but the source files are the same for all STM32F4xx devices.

## Middlewares

The Middlewares directory contains the header and source files for the middleware libraries. The header files are device specific, but the source files are the same for all STM32F4xx devices.

## Application

The Application directory contains the header and source files for the application. The header files are device specific, but the source files are the same for all STM32F4xx devices. The Tasks directory contains the header and source files for the tasks. The header files are device specific, but the source files are the same for all STM32F4xx devices.
