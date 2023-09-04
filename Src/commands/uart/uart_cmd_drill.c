//=====================================================================
//         ramki uart dla modulu wiertla
//=====================================================================

#include <string.h>
#include "uart_cmd.h"
#include "commands/can/can_cmd.h"

void Cmd_UART_Drill_A_Bridge_Set(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_A_Bridge_Set(data[0], data[1]);

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Drill_B_Bridge_Set(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_B_Bridge_Set(data[0], data[1]);

        Cmd_UART_BlinkLed(link_type);
    }
}