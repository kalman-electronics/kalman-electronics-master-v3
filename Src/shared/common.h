// A header file containing common global variables, macros and helpers
// Includes:
//     FreeRTOS task handles and queues
//     UART port definitions

#ifndef KALMAN_ELECTRONICS_MASTER_V3_COMMON_H
#define KALMAN_ELECTRONICS_MASTER_V3_COMMON_H

#include "FreeRTOS.h"
#include "task.h"

#include "uart_def.h"
#include "queues.h"
#include "TCAN114x/TCAN114x.h"
#include "gpio_expander.h"

#define UART_MESSAGE_MAX_SIZE 256 + 4
#define UART_RX_BUF_SIZE UART_MESSAGE_MAX_SIZE * 2

#define TIMER_COMM_TIMEOUT_BYPASS 0
#if TIMER_COMM_TIMEOUT_BYPASS != 0
    #warning "Arm & Motor timeouts disabled on master, if you don't know what are you doing change TIMER_COMM_TIMEOUT_BYPASS to 0!"
#endif

extern TaskHandle_t UARTParser_TaskHandle;
extern TCAN114x_Dev tcan;

#endif //KALMAN_ELECTRONICS_MASTER_V3_COMMON_H
