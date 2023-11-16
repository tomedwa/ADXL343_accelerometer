//NEED HEADER

#ifndef ADXL343_H_
#define ADXL343_H_


//#define ADXL343_SPI_MODE // defined = SPI, undefined = I2C

#define I2C_ADDR	0x53 // Alt address pin low.
#define I2C_READ_ADDR	(I2C_ADDR << 1) | 1
#define I2C_WRITE_ADDR	(I2C_ADDR << 1) | 0

#define SPI_READ		(1 << 7)
#define SPI_WRITE		(0 << 7)
#define SPI_MULTIBYTE	(1 << 6)
#define SPI_SINGLEBYTE	(0 << 6)

// define register addresses
#define X_DATA_0	0x32
#define X_DATA_1	0x33
#define Y_DATA_0	0x34
#define Y_DATA_1	0x35
#define Z_DATA_0	0x36
#define Z_DATA_1	0x36
#define BW_RATE		0x2C
#define DATA_FORMAT	0x31
#define POWER_CTL	0x2D
#define FIFO_CTL	0x38

extern int32_t adxl_axis_readings[3];

void ADXL343_setup_axis_read();
void ADXL_343_get_axis_readings();

#endif /* ADXL343_H_ */