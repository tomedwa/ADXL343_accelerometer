/*
 **************************************************************
 * ADXL343.c
 * Author: Tom
 * Date: 16/11/2023
 * AVR Library for the ADXL343 Accelerometer. Communication can
 * be done using I2C or SPI. For I2C use the i2cmaster.h
 * library by Peter Fleury. For SPI use Atmega328p_SPI.h by me.
 **************************************************************
 * EXTERNAL FUNCTIONS
 **************************************************************
 * ADXL343_setup_axis_read() - Init for x, y, z axis reading.
 * ADXL_343_get_axis_readings() - Read data in x, y, z data and
 * store the result in the adxl_axis_readings array.
 **************************************************************
*/

#include <avr/io.h>
#include "ADXL343.h"

#ifdef ADXL343_SPI_MODE
	#include "Atmega328p_SPI.h"
#else
	#include "i2cmaster.h"
#endif /* ADXL343_SPI_MODE */

int32_t adxl_axis_readings[3] = {0, 0, 0};

/*
 * ADXL343_setup_axis_read()
 * -------------------------
 * Initialise the ADXL343 sensor to read data from the x, y, z - axis. The specific
 * initialisation steps depend on the communication protocol defined in the header (SPI or I2C).
*/	
void ADXL343_setup_axis_read() {
	#ifdef ADXL343_SPI_MODE
		/* SPI Comms */
		A328p_SPI_transfer_data_to_reg(SPI_WRITE | SPI_SINGLEBYTE | BW_RATE,	 0x0D);
		A328p_SPI_transfer_data_to_reg(SPI_WRITE | SPI_SINGLEBYTE | DATA_FORMAT, 0x07);
		A328p_SPI_transfer_data_to_reg(SPI_WRITE | SPI_SINGLEBYTE | POWER_CTL,	 0x08);
		return;
	#else
		/* I2C Comms */
		i2c_start_wait(I2C_WRITE_ADDR);
		i2c_write(BW_RATE);
		i2c_write(0x0D);
		i2c_stop();
		
		i2c_start_wait(I2C_WRITE_ADDR);
		i2c_write(POWER_CTL);
		i2c_write(0x08);
		i2c_stop();
		
		i2c_start_wait(I2C_WRITE_ADDR);
		i2c_write(DATA_FORMAT);
		i2c_write(0x07);
		i2c_stop();
		
		i2c_start_wait(I2C_WRITE_ADDR);
		i2c_write(FIFO_CTL);
		i2c_write(0x00);
		i2c_stop();
		return;
	#endif /* ADXL343_SPI_MODE */
}

/*
 * ADXL_343_get_axis_readings()
 * -----------------------------
 * Reads the x, y, and z axis data from the ADXL343 registers and stores the results
 * in the adxl_axis_readings array. The specific read procedure depends on the
 * communication protocol defined in the header file (SPI or I2C).
 */
void ADXL_343_get_axis_readings() {
	uint8_t z0, z1;
	uint8_t x0, x1;
	uint8_t y0, y1;
	int32_t x, y, z;
	
	#ifdef ADXL343_SPI_MODE
		/* SPI Comms */
		SS_LOW;
		A328p_SPI_send_reg_only(SPI_READ | SPI_MULTIBYTE | X_DATA_0);
		x0 = A328p_SPI_receive_data_only();
		x1 = A328p_SPI_receive_data_only();
		y0 = A328p_SPI_receive_data_only();
		y1 = A328p_SPI_receive_data_only();
		z0 = A328p_SPI_receive_data_only();
		z1 = A328p_SPI_receive_data_only();
		SS_HIGH;
	
		// Combine all accelerometer data into integers
		x = (x1 << 8) | x0;
		y = (y1 << 8) | y0;
		z = (z1 << 8) | z0;
	
		adxl_axis_readings[0] = x;
		adxl_axis_readings[1] = y;
		adxl_axis_readings[2] = z;
	
		return;
	#else
		/* I2C Comms */
		i2c_start_wait(0xA6);
		i2c_write(X_DATA_0);
		i2c_rep_start(0xA7);
		x0 = i2c_readAck();
		x1 = i2c_readAck();
		y0 = i2c_readAck();
		y1 = i2c_readAck();
		z0 = i2c_readAck();
		z1 = i2c_readNak();
		i2c_stop();
		
		// Combine all accelerometer data into integers
 		x = (x1 << 8) | x0;
 		y = (y1 << 8) | y0;
 		z = (z1 << 8) | z0;
		
		adxl_axis_readings[0] = x;
 		adxl_axis_readings[1] = y;
 		adxl_axis_readings[2] = z;
		return;
	#endif /* ADXL343_SPI_MODE */
}
