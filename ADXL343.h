/*
 * ADXL343.h
 *
 * Created: 16/11/2023 1:58:58 PM
 *  Author: Tom
 */ 


#ifndef ADXL343_H_
#define ADXL343_H_

#define ADXL343_SPI_MODE 1 // 1 for SPI, 0 for I2C

#define READ		(1 << 7)
#define WRITE		(0 << 7)
#define MULTIBYTE	(1 << 6)
#define SINGLEBYTE	(0 << 6)

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

extern int32_t adxl_axis_readings[3];

void ADXL343_setup_axis_read();
void ADXL_343_get_axis_readings();

#endif /* ADXL343_H_ */