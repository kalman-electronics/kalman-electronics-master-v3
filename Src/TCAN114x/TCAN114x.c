/*
 * TCAN114x.c
 *
 *  Created on: Apr 3, 2022
 *      Author: Michal
 */
#include "stm32g4xx_hal.h"
#include "TCAN114x.h"
#include "TCAN114x_config.h"

//private functions declarations
void TCAN114x_getType(TCAN114x_Dev* tcan);
void TCAN114x_getRev(TCAN114x_Dev* tcan);

void TCAN114x_Init(TCAN114x_Dev* tcan, SPI_HandleTypeDef* spiHandle, GPIO_TypeDef* nCSHandle, uint16_t nCS)
{
	tcan->spi.spiHandle = spiHandle;
	tcan->spi.nCSHandle = nCSHandle;
	tcan->spi.nCS = nCS;
	TCAN114x_uploadInterruptsConfig(tcan);

}

void TCAN114x_writeRegister(TCAN114x_Dev* tcan, uint8_t regAddr, uint8_t data)
{
	uint8_t txBuff[2] = {0, 0};
	uint8_t rxBuff[2] = {0, 0};
	txBuff[0] = (regAddr<<1) | 0x01;
	txBuff[1] = data;

	HAL_GPIO_WritePin(tcan->spi.nCSHandle, tcan->spi.nCS, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(tcan->spi.spiHandle, txBuff, rxBuff, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(tcan->spi.nCSHandle, tcan->spi.nCS, GPIO_PIN_SET);
}

uint8_t TCAN114x_readRegister(TCAN114x_Dev* tcan, uint8_t regAddr)
{
	uint8_t txBuff[2] = {0, 0};
	uint8_t rxBuff[2] = {0, 0};
	txBuff[0] = regAddr<<1;

	HAL_GPIO_WritePin(tcan->spi.nCSHandle, tcan->spi.nCS, GPIO_PIN_RESET);
	HAL_SPI_TransmitReceive(tcan->spi.spiHandle, txBuff, rxBuff, 2, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(tcan->spi.nCSHandle, tcan->spi.nCS, GPIO_PIN_SET);

	return rxBuff[1];
}

void TCAN114x_getDeviceID(TCAN114x_Dev* tcan)
{
	TCAN114x_getType(tcan);
	TCAN114x_getRev(tcan);
}

void TCAN114x_setMode(TCAN114x_Dev* tcan, TCAN114x_Mode mode)
{
	uint8_t modeReg = 0;
	modeReg |= mode;
	modeReg |= TCAN114x_CAN_FAULT_DETECTION << 5;
	modeReg |= TCAN114x_DOMINANT_TIME_OUT_DISABLE << 6;
	modeReg |= TCAN114x_SELECTIVE_WAKE_EN << 7;
	TCAN114x_writeRegister(tcan, TCAN114x_MODE_CNTRL, modeReg);
}

void TCAN114x_getMode(TCAN114x_Dev* tcan)
{
	uint8_t modeReg = TCAN114x_readRegister(tcan, TCAN114x_MODE_CNTRL);
	modeReg &= 0x07;
	TCAN114x_Mode mode = (TCAN114x_Mode)modeReg;
	tcan->mode = mode;
}

void TCAN114x_uploadInterruptsConfig(TCAN114x_Dev* tcan)
{
	uint8_t int1_en = (TCAN114x_INT1_CANDOM_ENABLE & TCAN114x_CAN_STUCK_DOM_INT_ENABLE)| \
			(TCAN114x_INT1_CANINT_ENABLE & TCAN114x_CAN_BUS_WK_INT_ENABLE)| \
			(TCAN114x_INT1_CANSLNT_ENABLE & TCAN114x_CAN_SILENCE_INT_ENABLE)| \
			(TCAN114x_INT1_CANTO_ENABLE & TCAN114x_CAN_SILENCE_SW_SM_INT_ENABLE)| \
			(TCAN114x_INT1_FRAME_OVF_ENABLE & TCAN114x_FRAME_ERR_COUNTER_OVERFLOW_INT_ENABLE)| \
			(TCAN114x_INT1_LWU_ENABLE & TCAN114x_LOCAL_WAKEUP_INT_ENABLE)| \
			(TCAN114x_INT1_WD_ENABLE & TCAN114x_WATCHDOG_INT_ENABLE)| \
			(TCAN114x_INT1_WKERR_ENABLE & TCAN114x_WAKEUP_ERR_INT_ENABLE);

	uint8_t int2_en = (TCAN114x_INT2_TSDW_ENABLE & TCAN114x_THERMAL_SHUTDOWN_WARNING_INT_ENABLE)|\
			(TCAN114x_INT2_TSD_ENABLE & TCAN114x_THERMAL_SHUTDOWN_INT_ENABLE)|\
			(TCAN114x_INT2_UVCC_ENABLE & TCAN114x_VCC_UNDER_VOL_ENABLE)|\
			(TCAN114x_INT2_UVIO_ENABLE & TCAN114x_VIO_UNDER_VOL_ENABLE)|\
			(TCAN114x_INT2_UVSUP_ENABLE & TCAN114x_VSUP_UNDER_VOL_INT_ENABLE);

	uint8_t int3_en = (TCAN114x_INT3_FSM_ENABLE & TCAN114x_FAIL_SAVE_MODE_INT_ENABL)|\
			(TCAN114x_INT3_SPIERR_ENABLE & TCAN114x_SPI_ERR_INT_ENABLE)|\
			(TCAN114x_INT3_SWERR_ENABLE & TCAN114x_SELECTIVE_WAKE_ERR_INT_ENABLE);

	uint8_t intc_en = (TCAN114x_INTC_CANBUSBAT_ENABLE & TCAN114x_CAN_BUS_SHORTED_VBAT_INT_ENABLE)|\
			(TCAN114x_INTC_CANBUSGND_ENABLE & TCAN114x_CAN_BUS_SHORTED_GND_INT_ENABLE)|\
			(TCAN114x_INTC_CANBUSOPEN_ENABLE & TCAN114x_CAN_BUS_OPEN_INT_ENABLE)|\
			(TCAN114x_INTC_CANBUSTERMOPEN_ENABLE & TCAN114x_CAN_TERM_OPEN_INT_ENABLE)|\
			(TCAN114x_INTC_CANHBAT_ENABLE & TCAN114x_CAN_H_SHORTED_VBAT_INT_ENABLE)|\
			(TCAN114x_INTC_CANHCANL_ENABLE & TCAN114x_CAN_H_L_SHORT_INT_ENABLE)|\
			(TCAN114x_INTC_CANLGND_ENABLE & TCAN114x_CAN_L_SHORTED_GND_INT_ENABLE);

	TCAN114x_writeRegister(tcan, TCAN114x_INT_ENABLE_1, int1_en);
	TCAN114x_writeRegister(tcan, TCAN114x_INT_ENABLE_2, int2_en);
	TCAN114x_writeRegister(tcan, TCAN114x_INT_ENABLE_3, int3_en);
	TCAN114x_writeRegister(tcan, TCAN114x_INT_ENABLE_CANBUS, intc_en);
}

void TCAN114x_getInterrupts(TCAN114x_Dev* tcan)
{
	uint8_t globallInt = TCAN114x_readRegister(tcan, TCAN114x_INT_GLOBAL);

	if((globallInt & TCAN114x_INT1_GLOBAL_INT) != 0)
	{
		tcan->interrupts.int_1 = TCAN114x_readRegister(tcan, TCAN114x_INT_1);
	}else
	{
		tcan->interrupts.int_1 = 0x00;
	}

	if((globallInt & TCAN114x_INT2_GLOBAL_INT) != 0)
	{
		tcan->interrupts.int_2 = TCAN114x_readRegister(tcan, TCAN114x_INT_2);
	}else
	{
		tcan->interrupts.int_2 = 0x00;
	}

	if((globallInt & TCAN114x_INT3_GLOBAL_INT) != 0)
	{
		tcan->interrupts.int_3 = TCAN114x_readRegister(tcan, TCAN114x_INT_3);
	}else
	{
		tcan->interrupts.int_3 = 0x00;
	}

	if((globallInt & TCAN114x_INTC_GLOBAL_INT) != 0)
	{
		tcan->interrupts.int_canbus = TCAN114x_readRegister(tcan, TCAN114x_INT_CANBUS);
	}else
	{
		tcan->interrupts.int_canbus = 0x00;
	}
}

void TCAN114x_clearInterrupts(TCAN114x_Dev* tcan)
{
	uint8_t globallInt = TCAN114x_readRegister(tcan, TCAN114x_INT_GLOBAL);
		if(globallInt != 0)
		{
			if((globallInt & TCAN114x_INT1_GLOBAL_INT) != 0)
			{
				TCAN114x_writeRegister(tcan, TCAN114x_INT_1, 0xff);
			}

			if((globallInt & TCAN114x_INT2_GLOBAL_INT) != 0)
			{
				TCAN114x_writeRegister(tcan, TCAN114x_INT_2, 0xff);
			}

			if((globallInt & TCAN114x_INT3_GLOBAL_INT) != 0)
			{
				TCAN114x_writeRegister(tcan, TCAN114x_INT_3, 0xff);
			}

			if((globallInt & TCAN114x_INTC_GLOBAL_INT) != 0)
			{
				TCAN114x_writeRegister(tcan, TCAN114x_INT_CANBUS, 0xff);
			}
		}
}

void TCAN114x_softReset(TCAN114x_Dev* tcan)
{
	TCAN114x_writeRegister(tcan, TCAN114x_DEVICE_RST, TCAN114x_SOFT_RESET);
}

void TCAN114x_hardReset(TCAN114x_Dev* tcan)
{
	TCAN114x_writeRegister(tcan, TCAN114x_DEVICE_RST, TCAN114x_HARD_RESET);
}

//==========================================================================
void TCAN114x_getType(TCAN114x_Dev* tcan)
{
	for(uint8_t i = 0; i < 8; i++)
	{
		tcan->ID.type[i] = TCAN114x_readRegister(tcan, TCAN114x_DEVICE_ID_y + i);
	}
}

void TCAN114x_getRev(TCAN114x_Dev* tcan)
{
	tcan->ID.majorRev = TCAN114x_readRegister(tcan, TCAN114x_REV_ID_MAJOR);
	tcan->ID.minorRev = TCAN114x_readRegister(tcan, TCAN114x_REV_ID_MINOR);
}


