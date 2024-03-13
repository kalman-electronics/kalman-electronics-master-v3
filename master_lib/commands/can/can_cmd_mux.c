#include "can_cmd.h"

void Cmd_Bus_Mux_SetChannel(uint8_t vtx, uint8_t channel) {
    can_packet_t msg = {
        .cmd = CAN_CMD_MUX_SET_CHANNEL,
        .arg_count = CAN_ARG_MUX_SET_CHANNEL,
        .args = {vtx, channel},
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Mux_SetCam(uint8_t vtx, uint8_t cam) {
    can_packet_t msg = {
        .cmd = CAN_CMD_MUX_SET_CAM,
        .arg_count = CAN_ARG_MUX_SET_CAM,
        .args = {vtx, cam},
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Mux_SetPower(uint8_t vtx, uint8_t power) {
    can_packet_t msg = {
        .cmd = CAN_CMD_MUX_SET_POWER,
        .arg_count = CAN_ARG_MUX_SET_POWER,
        .args = {vtx, power},
    };

    Queues_SendCANFrame(&msg);
}
