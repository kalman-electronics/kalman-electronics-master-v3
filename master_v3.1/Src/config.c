//
// Created by bubak on 20/03/24.
//

#include "config.h"

/** I2C **/
i2c_def_t i2c_defs[I2C_DEFS_COUNT] = {
		{.id = GPIO_EXPANDER_I2C_ID, .i2c_handle = &hi2c4},
};

/** SPI **/
spi_def_t spi_defs[SPI_DEFS_COUNT] = {
		{.id = TCAN_SPI_ID, .spi_handle = &hspi1},
};

/** TCAN **/
tcan_def_t tcan_defs[TCAN_DEFS_COUNT] = {
		{.id = TCAN1_ID, .cs = {.port = TCAN_CS_GPIO_Port, .pin = TCAN_CS_Pin}},
		{.id = TCAN2_ID, .cs = {.port = TCAN2_CS_GPIO_Port, .pin = TCAN2_CS_Pin}},
};

/** FDCAN **/
fdcan_def_t fdcan_defs[FDCAN_DEFS_COUNT] = {
		{.id = FDCAN1_ID, .fdcan_handle = &hfdcan1},
		{.id = FDCAN2_ID, .fdcan_handle = &hfdcan2},
};

/** UART **/
uart_def_t uart_defs[UART_DEFS_COUNT] = {
		{.id = RF_UART_ID,    .uart_handle = &huart1,},
		{.id = AUTO_UART_ID,  .uart_handle = &huart3,},
		{.id = DEBUG_UART_ID, .uart_handle = &huart2,},
		{.id = RS422_UART_ID, .uart_handle = &hlpuart1}
};