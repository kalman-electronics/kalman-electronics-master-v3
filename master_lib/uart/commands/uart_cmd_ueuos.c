//=====================================================================
//                          UEUOS v2 Module
//=====================================================================
#include "uart_cmd.h"
#include "can/commands/can_cmd.h"

/**
 * Ustawia jeden z 4 stanów UEUOSA
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Ueuos_SetState(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Ueuos_SetState(data);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Ustawia kolor UEUOSa na podaną wartość RGB
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Ueuos_SetColor(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Ueuos_SetColor(data);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Ustawia predefiniowany efekt UEUOSA
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Ueuos_SetEffect(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Ueuos_SetEffect(data);

        Cmd_UART_BlinkLed(link_type);
    }
}