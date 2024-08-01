
#ifndef KALMAN_ELECTRONICS_MASTER_V3_QUEUES_H
#define KALMAN_ELECTRONICS_MASTER_V3_QUEUES_H

#include "FreeRTOS.h"
#include "queue.h"
#include "uart/uart_packet.h"
#include "can/can_packet.h"

extern QueueHandle_t uart_handler_incoming_packet_queue;
extern QueueHandle_t uart_handler_outgoing_packet_queue;

extern QueueHandle_t can_handler_incoming_packet_queue;
extern QueueHandle_t can_handler_outgoing_packet_queue;

void Queues_Init();

BaseType_t Queues_SendCANFrame(can_packet_t* packet);
BaseType_t Queues_SendUARTFrame(uart_packet_t* packet);

#endif //KALMAN_ELECTRONICS_MASTER_V3_QUEUES_H
