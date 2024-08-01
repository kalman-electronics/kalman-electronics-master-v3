#ifndef KALMAN_ELECTRONICS_MASTER_V3_UART_PARSER_H
#define KALMAN_ELECTRONICS_MASTER_V3_UART_PARSER_H

#include "shared/common.h"
#include "uart/uart_packet.h"

#define UART_PARSER_KBX_START_CHAR '<'

#define UART_PARSER_DMA_BUF_SIZE    32
#define UART_PARSER_PARSER_BUF_SIZE 1024

typedef enum {
	UART_PARSER_WAITING,
	UART_PARSER_HEADER_CMD,
    UART_PARSER_HEADER_LEN,
	UART_PARSER_HEADER_CRC,
	UART_PARSER_DATA,
    UART_PARSER_CRC,
	UART_PARSER_ÜRC
} uart_parser_state_t;

typedef struct {
	uart_parser_state_t state;
    uart_packet_t packet;
    uint8_t data_writen;

	uart_def_t* uart;

	uint8_t rx_dma_buf[UART_PARSER_DMA_BUF_SIZE];
	uint16_t rx_dma_buf_tail;

	uint8_t rx_parser_buf[UART_PARSER_PARSER_BUF_SIZE];
	uint16_t rx_parser_buf_head;
	uint16_t rx_parser_buf_tail;
} uart_parser_t;

extern uart_parser_t parser_defs[UART_DEFS_COUNT];

void UARTParser_Task();

#endif //KALMAN_ELECTRONICS_MASTER_V3_UART_PARSER_H
