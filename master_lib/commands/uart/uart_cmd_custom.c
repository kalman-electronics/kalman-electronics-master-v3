//=====================================================================
// Implementation of custom commands with variable number of parameters
//=====================================================================

#include <string.h>
#include "uart_cmd.h"

void Cmd_UART_CustomToRF(uint8_t* data, uint8_t len) {
    uart_packet_t msg = {
        .cmd = UART_CMD_CUSTOM_TO_RF,
        .arg_count = len,
        .origin = LINK_RF_UART
    };
    memcpy(msg.args, data, len);

    Queues_SendUARTFrame(&msg);
}

void Cmd_UART_CustomToUART(uint8_t* data, uint8_t len) {
    uart_packet_t msg = {
        .cmd = UART_CMD_CUSTOM_TO_UART,
        .arg_count = len,
        .origin = LINK_AUTO_UART
    };
    memcpy(msg.args, data, len);

    Queues_SendUARTFrame(&msg);
}

void Cmd_UART_SupervisorToRF(uint8_t* data, uint8_t len) {
    uart_packet_t msg = {
        .cmd = UART_CMD_SUPERVISOR_TO_RF,
        .arg_count = len,
        .origin = LINK_RF_UART
    };
    memcpy(msg.args, data, len);

    Queues_SendUARTFrame(&msg);
}

void Cmd_UART_SupervisorToUART(uint8_t* data, uint8_t len) {
    uart_packet_t msg = {
        .cmd = UART_CMD_SUPERVISOR_TO_UART,
        .arg_count = len,
        .origin = LINK_AUTO_UART
    };
    memcpy(msg.args, data, len);

    Queues_SendUARTFrame(&msg);
}

void Cmd_UART_RF_To_ESP32(uint8_t* data, uint8_t len) {
    uart_packet_t msg = {
            .cmd = UART_CMD_RF_TO_ESP32,
            .arg_count = len,
            .origin = LINK_DEBUG_UART
    };
    memcpy(msg.args, data, len);

    Queues_SendUARTFrame(&msg);
}

void Cmd_UART_ESP32_To_RF(uint8_t* data, uint8_t len) {
    uart_packet_t msg = {
            .cmd = UART_CMD_ESP32_TO_RF,
            .arg_count = len,
            .origin = LINK_AUTO_UART | LINK_RF_UART
    };
    memcpy(msg.args, data, len);

    Queues_SendUARTFrame(&msg);
}