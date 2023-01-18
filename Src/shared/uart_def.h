#ifndef KALMAN_ELECTRONICS_MASTER_V3_UART_DEF_H
#define KALMAN_ELECTRONICS_MASTER_V3_UART_DEF_H

#include "usart.h"
#include "stdio.h"

#define RF_UART_ID    0
#define AUTO_UART_ID  1
#define DEBUG_UART_ID 2

#define UART_DEFS_COUNT 3

// Uart used for debug printf
#define PRINTF_UART     DEBUG_UART_ID
#define PRINTF_UART_DEF uart_defs[PRINTF_UART].uart_handle

//#define debug_printf(format, ...) printf(format, ##__VA_ARGS__)
#define debug_printf(format, ...)

typedef struct {
    uint8_t id;
    UART_HandleTypeDef* uart_handle;
} uart_def_t;

extern uart_def_t uart_defs[UART_DEFS_COUNT];

#endif //KALMAN_ELECTRONICS_MASTER_V3_UART_DEF_H
