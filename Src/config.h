//
// Created by bubak on 20/03/24.
//

#ifndef KALMAN_ELECTRONICS_MASTER_V3_CONFG_H
#define KALMAN_ELECTRONICS_MASTER_V3_CONFG_H

#include "stm32g4xx_hal.h"
#include "i2c.h"
#include "spi.h"
#include "fdcan.h"
#include "usart.h"
#include "main.h"
#include <stdint.h>
#include <stdio.h>
#include "tcan114x-driver//TCAN114x.h"


typedef struct {
	GPIO_TypeDef *port;
	uint16_t pin;
} pin_t;

typedef struct {
	uint8_t id;
	I2C_HandleTypeDef *i2c_handle;
} i2c_def_t;

typedef struct {
	uint8_t id;
	SPI_HandleTypeDef *spi_handle;
} spi_def_t;

typedef struct {
	uint8_t id;
	TCAN114x_Dev tcan;
	pin_t cs;

} tcan_def_t;

typedef struct {
	uint8_t id;
	FDCAN_HandleTypeDef *fdcan_handle;
} fdcan_def_t;

typedef struct {
	uint8_t id;
	UART_HandleTypeDef *uart_handle;
} uart_def_t;

//#define OLD_MASTER
#define NEW_MASTER



#ifdef NEW_MASTER

/** I2C **/
#define I2C_DEFS_COUNT 1
#define GPIO_EXPANDER_I2C_ID 0

/** SPI **/
#define SPI_DEFS_COUNT 1
#define TCAN_SPI_ID 0

/** TCAN **/
#define TCAN_DEFS_COUNT 2
#define TCAN1_ID 0
#define TCAN2_ID 1

/** FDCAN **/
#define FDCAN_DEFS_COUNT 2
#define FDCAN1_ID 0
#define FDCAN2_ID 1

/** UART **/
#define UART_DEFS_COUNT 5
#define RF_UART_ID    0
#define AUTO_UART_ID  1
#define DEBUG_UART_ID 2
#define RS422_UART_ID 3
#define WIFI_UART_ID  4

// UART used for debug printf
#define PRINTF_UART     DEBUG_UART_ID
#define PRINTF_UART_DEF uart_defs[PRINTF_UART].uart_handle

//#define debug_printf(format, ...) printf(format, ##__VA_ARGS__)
#define debug_printf(format, ...)

#endif //NEW_MASTER

#ifdef OLD_MASTER

#endif //OLD_MASTER


extern i2c_def_t i2c_defs[I2C_DEFS_COUNT];
extern spi_def_t spi_defs[SPI_DEFS_COUNT];
extern tcan_def_t tcan_defs[TCAN_DEFS_COUNT];
extern fdcan_def_t fdcan_defs[FDCAN_DEFS_COUNT];
extern uart_def_t uart_defs[UART_DEFS_COUNT];

#endif //KALMAN_ELECTRONICS_MASTER_V3_CONFG_H