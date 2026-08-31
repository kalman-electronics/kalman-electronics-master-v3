#include <string.h>
#include "uart_cmd.h"
#include "can/commands/can_cmd.h"

void Cmd_UART_Drill_Rack_Set(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_Rack_Set(data[0], data[1]);

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Drill_Spindle_Set(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_Spindle_Set(data[0], data[1]);

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Drill_Servo_Set(uint8_t* data, uart_packet_link_t link_type){
	if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
		Cmd_Bus_Drill_C_Bridge_Set(data[0], data[1], data[2]);

		Cmd_UART_BlinkLed(link_type);
	}
}



void Cmd_UART_Drill_Weight_Request(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_SetGear(data);

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Drill_Autonomy(uint8_t* data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_Autonomy(data);

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Drill_WeightResponse(uint8_t* data) {
    uart_packet_t msg = {
        .cmd = UART_CMD_DRILL_WEIGHT_RESPONSE,
        .arg_count = UART_ARG_DRILL_WEIGHT_RESPONSE,
        .origin = LINK_RF_UART,
    };

    memcpy(&msg.args, data, UART_ARG_DRILL_WEIGHT_RESPONSE);

    Queues_SendUARTFrame(&msg);
}


void Cmd_UART_Drill_Telemetry(uint8_t* data) {
    uart_packet_t msg = {
            .cmd = UART_CMD_DRILL_TELEMETRY,
            .arg_count = UART_ARG_DRILL_TELEMETRY,
            .origin = LINK_RF_UART
    };

    memcpy(&msg.args, data, UART_ARG_DRILL_TELEMETRY);

    Queues_SendUARTFrame(&msg);
}