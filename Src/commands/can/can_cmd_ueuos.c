#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"
#include "commands/uart/uart_cmd.h"

/**
 * Ramka ustawia jeden z 4 podstawowych stanow ueuosa
 * @param data      wskaznik na 8-bajtowy bufor danych (1 argument stan UEUOSa)
 */
void Cmd_Bus_Ueuos_SetState(const uint8_t *data){
    can_packet_t msg = {
        .cmd = CAN_CMD_UEUOS_SET_STATE,
        .arg_count = CAN_ARG_UEUOS_SET_STATE,
        .args[0] = data[0],
    };

    Queues_SendCANFrame(&msg);
}

/**
 * Ramka ustawia kolor RGB UEUOSA
 * @param data      wskaznik na 8-bajtowy bufor danych (3 argumenty kolor RGB UEUOSa)
 */
void Cmd_Bus_Ueuos_SetColor(const uint8_t *data){
    can_packet_t msg = {
        .cmd = CAN_CMD_UEUOS_SET_COLOR,
        .arg_count = CAN_ARG_UEUOS_SET_COLOR,
        .args[0] = data[0],
        .args[1] = data[1],
        .args[2] = data[2]
    };

    Queues_SendCANFrame(&msg);
}
