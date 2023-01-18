#include "can_cmd.h"

void Cmd_Bus_UnknownHandler(can_packet_t* msg) {
    debug_printf("\t[CAN  ] Nieobsluzona komenda komunikacji (cmd = %d; data = ", msg->cmd);
    for (uint8_t i = 0; i < msg->arg_count; i++) {
        debug_printf("%2x", msg->args[i]);
    }
    debug_printf(")\r\n");
}

void Cmd_Bus_EmptyHandler(uint8_t* data) {

}