//=====================================================================
//                          MOBILAB v2 Module
//=====================================================================

#include <string.h>
#include "can_cmd.h"
#include "../../hw/hw.h"
#include "../uart/uart_cmd.h"

//=====================================================================
//           obsluga odebranych ramek CAN - mobilab 2.0
//=====================================================================

/**
 * Odbiera zwrotkę z tempertaturą mobilaba i zapisuje ją w structie mobilaba
 * @param id      id mobilaba od którego wysyłamy temperaturę
 */
void Cmd_Bus_Mobilab_GetTemperature(uint8_t* data){
    for (int i = 0; i < BUS_MOBILAB_COUNT; i++){
        if(bus_mobilab[i].id == data[0]) {
            memcpy((void *)&bus_mobilab[i].temperature, &data[1], sizeof(float));
            break;
        }
    }
}


//=====================================================================
//            generowanie wysylanych ramek - mobilab
//=====================================================================

/**
 * Ustawia PWM pompki w mobilabie 0-255
 * @param data      wskaznik na 8-bitowy bufor danych
 */
void Cmd_Bus_Mobilab_SetPump(const uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_MOBILAB_SET_PUMP,
            .arg_count = CAN_ARG_MOBILAB_SET_PUMP,
            .args[0] = data[0],
            .args[1] = data[1]
    };

    Queues_SendCANFrame(&msg);
}


/**
 * Ustawia PWM grzałki w mobilabie 0-255
 * @param data      wskaznik na 8-bitowy bufor danych
 */
void Cmd_Bus_Mobilab_SetHeater(const uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_MOBILAB_SET_HEATER,
            .arg_count = CAN_ARG_MOBILAB_SET_HEATER,
            .args[0] = data[0],
            .args[1] = data[1]
    };

    Queues_SendCANFrame(&msg);
}


/**
 * Ustawia PWM podświetlenia w mobilabie 0-255
 * @param data      wskaznik na 8-bitowy bufor danych
 */
void Cmd_Bus_Mobilab_SetBacklight(const uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_MOBILAB_SET_BACKLIGHT,
            .arg_count = CAN_ARG_MOBILAB_SET_BACKLIGHT,
            .args[0] = data[0],
            .args[1] = data[1]
    };
    Queues_SendCANFrame(&msg);
}


/**
 * Ustawia PWM wyjścia aux w mobilabie 0-255
 * @param data      wskaznik na 8-bitowy bufor danych
 */
void Cmd_Bus_Mobilab_SetAux(const uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_MOBILAB_SET_AUX,
            .arg_count = CAN_ARG_MOBILAB_SET_AUX,
            .args[0] = data[0],
            .args[1] = data[1]
    };

    Queues_SendCANFrame(&msg);
}


/**
 * Ustawia kąt serwa w mobilabie 0-145 stopni
 * @param data      wskaznik na 8-bitowy bufor danych
 */
void Cmd_Bus_Mobilab_SetServo(const uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_MOBILAB_SET_SERVO,
            .arg_count = CAN_ARG_MOBILAB_SET_SERVO,
            .args[0] = data[0],
            .args[1] = data[1]
    };

    Queues_SendCANFrame(&msg);
}