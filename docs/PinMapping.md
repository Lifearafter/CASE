# Pin Mappings for STM32F4 Custom Board

This file contains the pin mappings for the STM32F4 Custom Board.

## Pin Mappings

### CC1120: SPI1

MOSI: PA7 </br>
MISO: PA6 </br>
SCK: PA5 </br>
NSS/CS: PA4 </br>

### MAGNETOMETER: SPI2

MOSI: PB15 </br>
MISO: PB14 </br>
SCK: PB13 </br>
NSS/CS: PB12 </br>

### ACCELEROMETER (ADXL345): SPI3

MOSI: PC12 </br>
MISO: PC11 </br>
SCK: PC10 </br>
NSS/CS: PA15 (or any other GPIO pin configured as CS) </br>

### POWCUR (INA226): I2C1

SDA (Data line): PB7 </br>
SCL (Clock line): PB6 </br>

### TEMP (LM75A): I2C2

SDA: PB3 </br>
SCL: PB10 (29) </br>

### GYROSCOPE: I2C3

SDA: PC9 </br>
SCL: PA8 </br>

### GPS (NeoM8N): UART

TX (Transmit): PA9 </br>
RX (Receive): PA10 </br>

### STLINK V3: SWD

TX: PA2 </br>
RX: PA3 </br>

### STM32F4: Power

5v ON 1 </br>
3.3 V ON 3 </br>
GRND ON 2 </br>
