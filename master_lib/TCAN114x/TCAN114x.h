/*
 * TCAN114x.h
 *
 *  Created on: Apr 3, 2022
 *      Author: Michal
 */

#ifndef SRC_CAN_TCAN114X_TCAN114X_TCAN114X_H_
#define SRC_CAN_TCAN114X_TCAN114X_TCAN114X_H_

#include <stdint.h>
#include "TCAN114x_defs.h"

typedef struct
{
	TCAN114x_SPI spi;
	TCAN114x_interrupts interrupts;
	TCAN114x_Mode mode;
	TCAN114x_ID ID;
}TCAN114x_Dev;

void TCAN114x_Init(TCAN114x_Dev* tcan, SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* nCSHandle, uint16_t nCS);
void TCAN114x_writeRegister(TCAN114x_Dev* tcan, uint8_t regAddr, uint8_t data);
uint8_t TCAN114x_readRegister(TCAN114x_Dev* tcan, uint8_t regAddr);
void TCAN114x_getDeviceID(TCAN114x_Dev* tcan);
void TCAN114x_setMode(TCAN114x_Dev* tcan, TCAN114x_Mode mode);
void TCAN114x_getMode(TCAN114x_Dev* tcan);
void TCAN114x_uploadInterruptsConfig(TCAN114x_Dev* tcan);
void TCAN114x_getInterrupts(TCAN114x_Dev* tcan);
void TCAN114x_clearInterrupts(TCAN114x_Dev* tcan);
void TCAN114x_softReset(TCAN114x_Dev* tcan);
void TCAN114x_hardReset(TCAN114x_Dev* tcan);


#endif /* SRC_CAN_TCAN114X_TCAN114X_TCAN114X_H_ */
