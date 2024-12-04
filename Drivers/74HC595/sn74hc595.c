/*
 * sn74hc595.c
 *
 *  	Created on: Dec 2, 2024
 *      Author: Morshu8800
 *      Version: 1.0
 *      Note: This library is in update progress, and maybe incomplete.
 */

//This is a little HAL library for xx74HC595.
//MAX SPI clock for all temperature and voltage ranges = 4.0 Mbits/s or 4.0 MHz (maybe more).


//include header
#include "sn74hc595.h"

//seting transmit buffer, because HAL_SPI_Transmit() not working without massive...
uint8_t tx_buffer[1]={0};

//private functions:
static void HC595_CS_reset(void) {								//CS pin output OFF or LOW
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

static void HC595_CS_set(void) {								//CS pin output ON or HIGH
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
}

static void HC595_CS_strobe(void) {								//CS pin strobe for latch closing
	HC595_CS_reset();
	HC595_CS_set();

}

static void HC595_Write_data(uint8_t bt){ 						//sending data and latch closing
	tx_buffer[0]=bt;											//sending data into buffer
	HAL_SPI_Transmit(&SN74HC595_SPI_HAL, (uint8_t*)tx_buffer, 1, HAL_MAX_DELAY);	//sending data into xx74hc595
	HC595_CS_strobe(); 											//latch closing
}

//public functions:
void HC595_Reset_all(void){										//resetting all pins
	HC595_Write_data(0b00000000);								//sending to zero!
}

void HC595_Set_all(void){										//setting all pins
		HC595_Write_data(0b11111111);							//sending to byte
}

void HC595_Init(void){											//"Start with this function ;)"
	HC595_CS_set();
	HC595_Reset_all();
}

void HC595_Set_byte(uint8_t byte){								//setting full output byte, e.g: HC595_Set_byte(0xFF)-16, HC595_Set_byte(255)-10, HC595_Set_byte(0377)-8, HC595_Set_byte(0b11111111)-2; recommended for write
	HC595_Write_data(byte);
}
