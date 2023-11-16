// need header
#include <avr/io.h>
#include "ADXL343.h"

#ifdef ADXL343_SPI_MODE
	#include "Atmega328p_SPI.h"
#else
	#include "i2cmaster.h"
#endif /* ADXL343_SPI_MODE */

int32_t adxl_axis_readings[3] = {0, 0, 0};
	
void ADXL343_setup_axis_read() {
	#ifdef ADXL343_SPI_MODE
		/* SPI Comms */
		A328p_SPI_transfer_data_to_reg(SPI_WRITE | SPI_SINGLEBYTE | BW_RATE, 0x0D);
		A328p_SPI_transfer_data_to_reg(SPI_WRITE | SPI_SINGLEBYTE | DATA_FORMAT, 0x07);
		A328p_SPI_transfer_data_to_reg(SPI_WRITE | SPI_SINGLEBYTE | POWER_CTL, 0x08);
		return;
	#else
		/* I2C Comms */
		i2c_start_wait(0xA6);
		i2c_write(BW_RATE);
		i2c_write(0x0B);
		i2c_stop();
		
		i2c_start_wait(0xA6);
		i2c_write(0x2D);
		i2c_write(0x08);
		i2c_stop();
		
		i2c_start_wait(0xA6);
		i2c_write(0x31);
		i2c_write(0x0B);
		i2c_stop();
		
		i2c_start_wait(0xA6);
		i2c_write(0x38);
		i2c_write(0x00);
		i2c_stop();
		return;
	#endif /* ADXL343_SPI_MODE */
}

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
