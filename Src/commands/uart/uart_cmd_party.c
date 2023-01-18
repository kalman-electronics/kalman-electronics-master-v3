//=====================================================================
//                          Party Module
//=====================================================================


#include "uart_cmd.h"
#include "commands/can/can_cmd.h"

/**
 * Sterowanie zapalnikami. Po aktywacji zapalnik jest zasilany przez 2s.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Party_SetIgniters(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type))  {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Party SetIgniters: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        Cmd_Bus_Party_SetIgniters(data[0]);

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zmiana animacji diod RGB. Diody zmieniaj� swoj� jasno�� w rytm muzyki, ale animacja kolor�w zale�y od wybranego trybu. Domy�lnie diody s� wy��czone.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Party_SetLeds(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type))  {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Party SetLeds: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        Cmd_Bus_Party_SetRgb(data[0]);

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Sterowanie zasilaniem blok�w mocy.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Party_SetPower(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type))  {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Party SetPower: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        //obecnie nieuzywane

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * W��czenie lub wy��czenie zwracania stanu detektor�w (Cmd_Party_GetDetectors).
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Party_SetDetectorsMode(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type))  {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Party SetDetectorsMode: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        //todo Party SetDetectorsMode

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zwracanie aktualnych stan�w detektor�w zapalnik�w modu�u imprezowego.
 * @note Detektor nr 8 jest nieobs�ugiwany, ze wzgl�du na wykorzystanie go jako wej�cie muzyczne.
 */
void Cmd_UART_Party_GetDetectors(void) {
    if ((logic.link_type == LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)) {
        //static uint8_t args[ARG_PARTY_GET_DETECTORS];

        //todo Party GetDetectors

        //Uarts_SendFrame(link, CMD_PARTY_GET_DETECTORS, ARG_PARTY_GET_DETECTORS, args);
    }
}


