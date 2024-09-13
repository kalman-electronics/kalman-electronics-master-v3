#include "can_packet_handler.h"
#include "can/can_packet.h"
#include "queue.h"
#include "shared/common.h"
#include "can/can_packet_defs.h"

StaticTask_t CANHandlerTaskBuffer;
StackType_t CANHandlerTaskStack[CAN_HANDLER_TASK_STACK_SIZE];

void CANHandler_ProcessPacket(can_packet_t* msg);

void CANHandler_Task(void *argument) {
    can_packet_t msg;

    while(1) {
        xQueueReceive(can_handler_incoming_packet_queue, &msg, portMAX_DELAY);

        CANHandler_ProcessPacket(&msg);
    }
}

void CANHandler_ProcessPacket(can_packet_t* msg) {
    // Find and validate handler
    for (uint32_t i = 0; i < CAN_PACKET_DEFS_LEN; i ++) {
        if (can_packet_defs[i].cmd == msg->cmd) {
            if ((can_packet_defs[i].arg_count != msg->arg_count)) {
                debug_printf("Invalid packet arg len\n");
                return;
            }

            // Execute packet handler function
            can_packet_defs[i].execute(msg->args);
            return;
        }
    }

    // Handle unknown packets
    Cmd_Bus_UnknownHandler(msg);
}