#include "queues.h"

QueueHandle_t uart_handler_incoming_packet_queue;
QueueHandle_t uart_handler_outgoing_packet_queue;

QueueHandle_t can_handler_incoming_packet_queue;
QueueHandle_t can_handler_outgoing_packet_queue;

void Queues_Init() {
    uart_handler_incoming_packet_queue = xQueueCreate(24, sizeof(uart_packet_t));
    uart_handler_outgoing_packet_queue = xQueueCreate(8, sizeof(uart_packet_t));

    can_handler_incoming_packet_queue = xQueueCreate(24, sizeof(can_packet_t));
	can_handler_outgoing_packet_queue = xQueueCreate(8, sizeof(can_packet_t));
}

BaseType_t Queues_SendCANFrame(can_packet_t* packet) {
    return xQueueSend(can_handler_outgoing_packet_queue, packet, 0);
}
BaseType_t Queues_SendUARTFrame(uart_packet_t* packet) {
    return xQueueSend(uart_handler_outgoing_packet_queue, packet, 0);
}
