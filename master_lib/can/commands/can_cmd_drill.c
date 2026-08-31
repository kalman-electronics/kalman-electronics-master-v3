#include <string.h>
#include "can_cmd.h"
#include "uart/commands/uart_cmd.h"

void Cmd_Bus_Drill_Rack_Set(uint8_t direction, uint8_t speed){
    can_packet_t msg = {
         .cmd = CAN_CMD_DRILL_RACK_SET,
         .arg_count = CAN_ARG_DRILL_RACK_SET,
         .args[0] = direction,
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_Spindle_Set(uint8_t direction, uint8_t speed){
    can_packet_t msg = {
            .cmd = CAN_CMD_DRILL_SPINDLE_SET,
            .arg_count = CAN_ARG_DRILL_SPINDLE_SET,
            .args[0] = direction,
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_C_Bridge_Set(uint8_t channel, uint8_t angle_hi, uint8_t angle_lo){
	can_packet_t msg = {
			.cmd = CAN_CMD_DRILL_C_BRIDGE_SET,
			.arg_count = CAN_ARG_DRILL_C_BRIDGE_SET,
			.args[0] = channel,
			.args[1] = angle_hi,
	        .args[2] = angle_lo,
	};

	Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_Autonomy(uint8_t* data) {
    can_packet_t msg = {
        .cmd = CAN_CMD_DRILL_AUTONOMY,
        .arg_count = CAN_ARG_DRILL_AUTONOMY,
        .args = {data[0]}
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_SetGear(uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_DRILL_GET_WEIGHT,
            .arg_count = CAN_ARG_DRILL_SET_GEAR,
            .args = {data[0]}
	};

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_WeightResponse(uint8_t* data){
    Cmd_UART_Drill_WeightResponse(data);
}

void Cmd_Bus_Drill_Telemetry(uint8_t* data){
    int64_t telemetry;

    memcpy(&telemetry, data, sizeof(int64_t));

    Cmd_UART_Drill_Telemetry((uint8_t*)&telemetry);
}

