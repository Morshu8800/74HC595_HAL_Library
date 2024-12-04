/*
 * sn74hc595.h
 *
 *  	Created on: Dec 2, 2024
 *      Author: Morshu8800
 *      Version: 1.0
 *      Note: This library is in update progress, and maybe incomplete.
 */

#ifndef SN74HC595_SN74HC595_H_
#define SN74HC595_SN74HC595_H_

#ifdef __cplusplus
extern "C" {
#endif

//includes standard libraries
#include "main.h"

//define number of SPI
#define SN74HC595_SPI_HAL hspi1 //Change "hspi1" another if you need

#ifdef SN74HC595_SPI_HAL
extern SPI_HandleTypeDef SN74HC595_SPI_HAL;
#endif

//define CS pin
#if defined (CS_GPIO_Port)
#else
#define CS_GPIO_Port    GPIOA //Port CS
#define CS_Pin			GPIO_PIN_14 //Pin CS
#endif

//public function prototypes:
void HC595_Init(void); //connect to 74hc595
void HC595_Set_byte(uint8_t byte); //set reg pins ON
void HC595_Reset_all(void); //reset all reg pins OFF
void HC595_Set_all(void); //set all reg pins ON

#endif /* SN74HC595_SN74HC595_H_ */
