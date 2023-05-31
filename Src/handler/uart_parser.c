#include <stdlib.h>
#include "uart_parser.h"
#include "commands/uart_packet_defs.h"
#include "dma.h"
#include "usart.h"
#include "string.h"
#include "FreeRTOS.h"
#include "task.h"

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define PARSER_READ_BYTE() (parser->rx_parser_buf[parser->rx_parser_buf_tail++])

#define HEX2BYTE_ERROR 0xFFFF

uart_parser_t parser_defs[UART_DEFS_COUNT];

void UARTParser_ParseBuf(uart_parser_t* parser);

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size) {
	uart_parser_t* parser = NULL;

	// Find corresponding parser
	for (int i = 0; i < UART_DEFS_COUNT; i++) {
		if (parser_defs[i].uart->uart_handle == huart) {
			parser = &parser_defs[i];
			break;
		}
	}

	// Check if parser is valid
	if (parser == NULL) {
		debug_printf("Unknown UART ID\n");
		return;
	}

	// Calculate current transfer size
	uint16_t dataLen = Size - parser->rx_dma_buf_tail;

	while(dataLen) {
		// Calculate maximum bytes that can be copied in one continuous block
		uint16_t toCopy = MIN(
				MIN(UART_PARSER_PARSER_BUF_SIZE - parser->rx_parser_buf_head, dataLen),
				MIN(UART_PARSER_DMA_BUF_SIZE    - parser->rx_dma_buf_tail   , dataLen));

		// If it is possible, copy data block and increment pointers
		if (toCopy) {
			memcpy(parser->rx_parser_buf + parser->rx_parser_buf_head, parser->rx_dma_buf + parser->rx_dma_buf_tail, toCopy);

            parser->rx_parser_buf_head += toCopy;
            parser->rx_dma_buf_tail += toCopy;

			dataLen -= toCopy;
		}

		// Loop over
		if (parser->rx_parser_buf_head == UART_PARSER_PARSER_BUF_SIZE)
            parser->rx_parser_buf_head = 0;

		if (parser->rx_dma_buf_tail== UART_PARSER_DMA_BUF_SIZE)
            parser->rx_dma_buf_tail = 0;
	}

	// Notify parser about new data on specific UART channel to be processed and yield
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xTaskNotifyFromISR(UARTParser_TaskHandle, parser->uart->id + 1, eSetBits, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

uint8_t _decode_hex(uint8_t hex) {
    if ((hex >= '0') && (hex <= '9'))
        return hex-'0';
    else if ((hex >= 'a') && (hex <= 'f'))
        return 10+hex-'a';
    else if ((hex >= 'A') && (hex <= 'F'))
        return 10+hex-'A';
    else
        return 255;
}

uint16_t _hex2byte(uint8_t *buf) {
	uint8_t result, value;
	if ((value = _decode_hex(buf[0])) < 16) {
		result = value << 4;

		if ((value = _decode_hex(buf[1])) < 16) {
			result = result + value;
			return result;
		}
		return HEX2BYTE_ERROR;
	}
	return HEX2BYTE_ERROR;
}

void UARTParser_ParseRawData(uart_parser_t* parser, uint8_t* buf) {
	uint8_t crc = 0; //obliczone pole CRC
	uint8_t *p = buf; //pomocniczy wskaznik
	uint16_t conv; //zdekodowana wartosc z dwoch znakow ASCII

	//dekodowanie kodu komendy
	if ((conv = _hex2byte(p)) != HEX2BYTE_ERROR) {
		parser->packet.cmd = (uint8_t)conv;
		crc ^= (uint8_t)conv;
		p += 2;
	}
	else return;

	//dekodowanie ilosci argumentow - w zaleznosci od konfiguracji 1 lub 2 bajty
	uint16_t args_count = 0;
	if ((conv = _hex2byte(p)) != HEX2BYTE_ERROR) {
        args_count += conv;
        crc ^= (uint8_t)conv;
        p += 2;
    }
    else return;

	//dekodowanie argumentow
	for (uint16_t i=0; i<args_count; i++) {
		if ((conv = _hex2byte(p)) != HEX2BYTE_ERROR) {
			parser->packet.args[i] = (uint8_t)conv;
			crc ^= (uint8_t)conv;
			p += 2;
		}
		else return;
	}

	//porownanie CRC
	if ((conv = _hex2byte(p)) != HEX2BYTE_ERROR) {
		if (crc == (uint8_t)conv) {
			parser->packet.arg_count = args_count;

			//przekazywanie ramki do funkcji wykonawczej
			parser->packet.origin = UARTPacket_UARTIDToLink(parser->uart->id);

			if (!xQueueSend(uart_handler_incoming_packet_queue, &(parser->packet), 0))
				debug_printf("UART msg queue full\n");

		} else {
			debug_printf("CRC Error\n");
		}
	}
}

void UARTParser_ParseBufLegacy(uart_parser_t* parser) {
	static uint8_t buf[300];
	static uint16_t len = 0;
	static uint8_t isParsing = 0;

	while(parser->rx_parser_buf_head != parser->rx_parser_buf_tail) {
		uint8_t current_byte = PARSER_READ_BYTE();

		if (parser->rx_parser_buf_tail == UART_PARSER_PARSER_BUF_SIZE)
			parser->rx_parser_buf_tail = 0;

		if (current_byte == '<') {
			len = 0;
			isParsing = 1;
			continue;
		} else if (!isParsing) {
			continue;
		}

		if (current_byte == '>') {
			UARTParser_ParseRawData(parser, buf);
			isParsing = 0;
		} else {
			buf[len++] = current_byte;

			if (len == 300) {
				isParsing = 0;
				len = 0;
			}
		}
	}
}

void UARTParser_ParseBuf(uart_parser_t* parser) {
	uint8_t crc;

	while(parser->rx_parser_buf_head != parser->rx_parser_buf_tail) {
		switch (parser->state) {
            // Wait for packet start char
            case UART_PARSER_WAITING:
                if(PARSER_READ_BYTE() == UART_PARSER_KBX_START_CHAR)
                    parser->state = UART_PARSER_HEADER_CMD;
                break;

            // Parse header cmd
            case UART_PARSER_HEADER_CMD:
                parser->packet.cmd = PARSER_READ_BYTE();
                parser->state = UART_PARSER_HEADER_LEN;
                break;

            // Calculate data length / remaining data to read
            case UART_PARSER_HEADER_LEN:
                parser->packet.arg_count = PARSER_READ_BYTE();
				parser->state = UART_PARSER_HEADER_CRC;
                break;

			// Calculate CRC for the packet's header
			// TODO: Additional check - Deduce len from cmd field in message def
			case UART_PARSER_HEADER_CRC:
				crc = PARSER_READ_BYTE();

				if (crc != parser->packet.cmd + parser->packet.arg_count) {
					parser->state = UART_PARSER_WAITING;
					break;
				}

				// Drop regular packets over 16 bytes long as they SHOULD not appear
				#warning "Parser drops frames over 16 bytes long - URC hotfix"
                if (parser->packet.arg_count > 16 && !UART_PACKET_IS_CUSTOM(parser->packet.cmd)) {
                	parser->state = UART_PARSER_WAITING;
                	break;
                }

                // For packet without arguments skip data acq phase
                if (parser->packet.arg_count != 0) {
                    parser->state = UART_PARSER_DATA;
                } else {
                    parser->state = UART_PARSER_CRC;
                }
				break;

            case UART_PARSER_DATA:
                parser->packet.args[parser->data_writen++] = PARSER_READ_BYTE();

                if (parser->data_writen == parser->packet.arg_count) {
                	parser->data_writen = 0;
                    parser->state = UART_PARSER_CRC;
                }

                break;

            case UART_PARSER_CRC:
                // Calculate CRC for the received packet
            	crc = parser->packet.cmd ^ parser->packet.arg_count;
                for (uint8_t i = 0; i < parser->packet.arg_count; i++)
                    crc ^= parser->packet.args[i];

                // Compare calculated CRC with a received one
				if (crc != PARSER_READ_BYTE()) {
					parser->state = UART_PARSER_WAITING;
					debug_printf("CRC Error\n");
					break;
				}

                parser->state = UART_PARSER_ÜRC;
                break;

			case UART_PARSER_ÜRC:
				// Calculate ÜRC - additional "CRC" - for the received packet
				crc = 0;
                for (uint8_t i = 0; i < parser->packet.arg_count; i++)
                    crc += (parser->packet.args[i] + i) * ((i & 0b11) + 1);

                // Compare calculated ÜRC with a received one
                if (crc == PARSER_READ_BYTE()) {
                	parser->packet.origin = UARTPacket_UARTIDToLink(parser->uart->id);

					if (!xQueueSend(uart_handler_incoming_packet_queue, &(parser->packet), 0))
						debug_printf("UART msg queue full\n");


                } else {
					debug_printf("CRC Error\n");
                }

                parser->state = UART_PARSER_WAITING;
                break;
        }

        // Loop over
        if (parser->rx_parser_buf_tail == UART_PARSER_PARSER_BUF_SIZE)
            parser->rx_parser_buf_tail = 0;
	}
}

void UARTParser_Task() {
	// Start DMA reception and disable HT interrupt
	for (int i = 0; i < UART_DEFS_COUNT; i++) {
        parser_defs[i].uart = &uart_defs[i];

		HAL_UARTEx_ReceiveToIdle_DMA(uart_defs[i].uart_handle, parser_defs[i].rx_dma_buf, 32);
		__HAL_DMA_DISABLE_IT(uart_defs[i].uart_handle->hdmarx, DMA_IT_HT);
	}

	// Processing loop
	while(1) {
		// Wait for new data in the parser's buffer
		// UART id is encoded as a bit position (one's hot encoding)
		uint32_t uarts_to_process = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Do some parsing if there is data available
		uint8_t uart_id = 0;
		while(uarts_to_process) {
			// Check every bit until all are cleared
			if(uarts_to_process & (1 << uart_id)) {
				// Parse buffer
				#warning Using legacy parser
				UARTParser_ParseBufLegacy(&parser_defs[uart_id]);

				// Clear bit
				uarts_to_process &= ~(1 << uart_id);
			}

			uart_id++;
		}
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	uint8_t uart_id = 255;

	for (int i = 0; i < UART_DEFS_COUNT; i++) {
		if (uart_defs[i].uart_handle == huart) {
			uart_id = i;
			break;
		}

	}

	if (uart_id == 255) {
		__asm__ volatile ("BKPT");
		while(1) {}
	}

	if (huart->RxState == 32 && huart->ErrorCode & HAL_UART_ERROR_FE) {
		HAL_UARTEx_ReceiveToIdle_DMA(huart, parser_defs[uart_id].rx_dma_buf, 32);
		__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
	}
	else {

	}
}
