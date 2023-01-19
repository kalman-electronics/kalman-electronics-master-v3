#include "uart_packet_handler.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "shared/queues.h"
#include "commands/uart_packet.h"
#include "commands/uart_packet_defs.h"
#include "stdio.h"
#include "shared/uart_def.h"

void UARTHandler_ProcessPacket(uart_packet_t* msg);

void UARTHandler_Task() {
    uart_packet_t msg;

    while(1) {
        xQueueReceive(uart_handler_incoming_packet_queue, &msg, portMAX_DELAY);

        //TODO: packet filtering - active uart + switch - probably handled on message to message basis

        UARTHandler_ProcessPacket(&msg);
    }
}

void UARTHandler_ProcessPacket(uart_packet_t* msg) {
    // Custom frames support
    //TODO: ugly af, add len to callbacks and merge with other commands
    if (msg->cmd == UART_CMD_CUSTOM_TO_RF) {
        Cmd_UART_CustomToRF(msg->args, msg->arg_count);
        return;
    }

    if (msg->cmd == UART_CMD_CUSTOM_TO_UART) {
        Cmd_UART_CustomToUART(msg->args, msg->arg_count);
        return;
    }

    // Find and validate handler
    for (int i = 0; i < UART_PACKET_DEFS_LEN; i ++) {
        if (uart_packet_defs[i].cmd == msg->cmd) {
            if (uart_packet_defs[i].arg_count != msg->arg_count && (msg->cmd != UART_CMD_CUSTOM_TO_UART && msg->cmd != UART_CMD_CUSTOM_TO_RF)) {
                debug_printf("Invalid packet arg len\n");
                return;
            }

            // Execute packet handler function
            uart_packet_defs[i].execute(msg->args, msg->origin);
            return;
        }
    }

    // Handle unknown packets
    Cmd_UART_UnknownHandler(msg);
}
