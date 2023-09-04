#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"

void Cmd_Bus_Drill_A_Bridge_Set(uint8_t direction, uint8_t speed){
    can_packet_t msg = {
         .cmd = CAN_CMD_DRILL_A_BRIDGE_SET,
         .arg_count = CAN_ARG_DRILL_A_BRIDGE_SET,
         .args[0] = direction,
         .args[1] = speed
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_B_Bridge_Set(uint8_t direction, uint8_t speed){
    can_packet_t msg = {
            .cmd = CAN_CMD_DRILL_B_BRIDGE_SET,
            .arg_count = CAN_ARG_DRILL_B_BRIDGE_SET,
            .args[0] = direction,
            .args[1] = speed
    };

    Queues_SendCANFrame(&msg);
}
