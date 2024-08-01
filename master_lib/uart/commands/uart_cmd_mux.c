#include "uart_cmd.h"
#include "can/commands/can_cmd.h"

void Cmd_UART_Mux_SetChannel(uint8_t* data, uart_packet_link_t link_type)
{
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
		if (Logic_GetUptime() >= LOGIC_COMM_START_TIME){
			Cmd_Bus_Mux_SetChannel(data[0], data[1]);
		}

		Cmd_UART_BlinkLed(link_type);
	}
}

void Cmd_UART_Mux_SetCam(uint8_t* data, uart_packet_link_t link_type)
{
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
		if (Logic_GetUptime() >= LOGIC_COMM_START_TIME){
			Cmd_Bus_Mux_SetCam(data[0], data[1]);
		}

		Cmd_UART_BlinkLed(link_type);
	}
}

void Cmd_UART_Mux_SetPower(uint8_t* data, uart_packet_link_t link_type)
{
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
		if (Logic_GetUptime() >= LOGIC_COMM_START_TIME){
			Cmd_Bus_Mux_SetPower(data[0], data[1]);
		}

		Cmd_UART_BlinkLed(link_type);
	}
}

