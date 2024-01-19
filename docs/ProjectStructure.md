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
│   └── ...
├── Middlewares/
│   └── FreeRTOS/
├── Application/
│   ├── Inc/
│   ├── Src/
│   ├── Tasks/
│   │   ├── GPS_Task/
│   │   ├── LM75A_Task/
│   │   ├── INA225_Task/
│   │   ├── ADXL345_Task/
│   │   └── ...
│   └── main.c
├── BSP/
├── Libraries/
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

## BSP

The BSP directory contains the header and source files for the board support package. Include files for pin mappings, clock configurations, and other board-specific settings.

## Libraries

The Libraries directory contains the header and source files for thrid party libraries.
