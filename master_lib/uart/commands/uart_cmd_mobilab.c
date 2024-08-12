#include <string.h>
#include "uart_cmd.h"
#include "can/commands/can_cmd.h"

/**
 * Ustawia PWM pompki w mobilabie 0-255
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Mobilab_SetPump(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Mobilab_SetPump(data);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Ustawia PWM grzałki w mobilabie 0-255
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Mobilab_SetHeater(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Mobilab_SetHeater(data);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Ustawia PWM podświetlenia w mobilabie 0-255
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Mobilab_SetBacklight(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Mobilab_SetBacklight(data);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Ustawia PWM wyjścia aux w mobilabie 0-255
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Mobilab_SetAux(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Mobilab_SetAux(data);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Ustawia kąt serwa w mobilabie 0-145 stopni
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Mobilab_SetServo(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Mobilab_SetServo(data);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Wysyła zwrotkę temperatury od mobilaba o danym id, wywoływana co 1s
 * @param id      id mobilaba od którego wysyłamy temperaturę
 */
void Cmd_UART_Mobilab_GetTemperature(uint8_t id){
    uart_packet_t msg = {
            .cmd = UART_CMD_MOBILAB_GET_TEMPERATURE,
            .arg_count = UART_ARG_MOBILAB_GET_TEMPERATURE,
            .origin = logic.link_type
    };

    for (int i = 0; i < BUS_MOBILAB_COUNT; i++){
        if(bus_mobilab[i].id == id){
            msg.args[0] = id;

            memcpy(&msg.args[1], (void*)&bus_mobilab[i].temperature, sizeof(float));

            Queues_SendUARTFrame(&msg);
        }
    }
}
