#include "uart_packet_handler.h"
#include "uart/uart_packet.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "shared/common.h"
#include "uart/uart_packet_defs.h"

void UARTHandler_ProcessPacket(uart_packet_t* msg);

void UARTHandler_Task() {
    uart_packet_t msg;

    while(1) {
        xQueueReceive(uart_handler_incoming_packet_queue, &msg, portMAX_DELAY);

        //TODO: packet filtering - active uart + switch - probably handled on message to message basis

        UARTHandler_ProcessPacket(&msg);
    }
}

//TODO: Fix different args in custom callback functions
void UARTHandler_ProcessPacket(uart_packet_t* msg) {
    // Find and validate packet handler
    for (int i = 0; i < UART_PACKET_DEFS_LEN; i ++) {
        if (uart_packet_defs[i].cmd == msg->cmd) {
            // Check packet arguments (skip on custom frame)
        	if (UART_PACKET_IS_CUSTOM(msg->cmd)) {
        		uart_packet_defs[i].execute(msg->args, msg->arg_count);
        		return;
        	}

            if (uart_packet_defs[i].arg_count != msg->arg_count) {
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
