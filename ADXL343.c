// need header
#include <avr/io.h>
#include "ADXL343.h"

#if ADXL343_SPI_MODE
	#include "Atmega328p_SPI.h"
#else
	// some other i2c shit
#endif /* ADXL343_SPI_MODE */

int32_t adxl_axis_readings[3] = {0, 0, 0};
	
void ADXL343_setup_axis_read() {
	switch(ADXL343_SPI_MODE) {
		case 0:
			// I2C MODE
			return;
		case 1:
			// SPI MODE
			A328p_SPI_transfer_data_to_reg(WRITE | SINGLEBYTE | BW_RATE, 0x0D);
			A328p_SPI_transfer_data_to_reg(WRITE | SINGLEBYTE | DATA_FORMAT, 0x07);
			A328p_SPI_transfer_data_to_reg(WRITE | SINGLEBYTE | POWER_CTL, 0x08);
			return;
	}
}

void ADXL_343_get_axis_readings() {
	uint8_t z0, z1;
	uint8_t x0, x1;
	uint8_t y0, y1;
	int32_t x, y, z;
	
	switch(ADXL343_SPI_MODE) {
		case 0:
			// I2C MODE
			return;
		case 1:
			// SPI MODE
			SS_LOW;
			A328p_SPI_send_reg_only(READ | MULTIBYTE | X_DATA_0);
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
	}
}
