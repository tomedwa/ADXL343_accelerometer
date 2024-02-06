# ADXL343_accelerometer
Simple library for the ADXL343 sensor using the Atmega328p MCU. So far the only functionality 
supported is to read the x, y and z axis registers on the 343. This library is configured to 
use either SPI or I2C communication depending on the configuration of the defines in the header
file.

## SPI or I2C
Use of the SPI or I2C communication protocol can be configured in the ADXL343.h file. Near the top of
the file there is this line of code:
```
/* defined = SPI, undefined = I2C */
#define ADXL343_SPI_MODE
```
Leaving this line means the SPI protocol will be used. If this line is commented out, then the I2C
protocol will be used.

Header files required for this library to work.
| Protocol | Include | Link |
|---|---|---|
| SPI | Atmega328p_SPI.h | https://github.com/tomedwa/Atmega328p_SPI |
| I2C | i2cmaster.h | https://github.com/damadmai/pfleury |

## Getting Started
Basic example of reading the axis data from the adxl343 sensor using SPI:
```
A328p_SPI_init();
ADXL343_setup_axis_read();
while (1) {
  ADXL343_get_axis_readings();
}
```
Pretty much the same for I2C except do `i2c_init()` instead.
