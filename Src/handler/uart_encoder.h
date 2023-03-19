#ifndef KALMAN_ELECTRONICS_MASTER_V3_UART_ENCODER_H
#define KALMAN_ELECTRONICS_MASTER_V3_UART_ENCODER_H

#include <stdint.h>
#include "shared/common.h"

#define UART_ENCODER_DMA_BUF_SIZE 8192

typedef enum {
    UART_ENCODER_IDLE = 0,
    UART_ENCODER_TX   = 1
} uart_encoder_status_t;

typedef struct {
    uart_def_t* uart;

    // Separate DMA status to prevent race conditions
    // between task and interrupt
    uart_encoder_status_t status;

    uint8_t tx_dma_buf[UART_ENCODER_DMA_BUF_SIZE];
    uint16_t tx_dma_buf_head;
    uint16_t tx_dma_buf_tail;
} uart_encoder_t;

extern uart_encoder_t encoder_defs[UART_DEFS_COUNT];

void UARTEncoder_Task();

#endif //KALMAN_ELECTRONICS_MASTER_V3_UART_ENCODER_H
