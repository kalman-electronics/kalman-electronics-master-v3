//=====================================================================
//                          Universal Module
//=====================================================================

#include "uart_cmd.h"
#include "../can/can_cmd.h"

/**
 * Ustawianie zadanych kierunk�w i pr�dko�ci mostk�w H.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Universal_SetBridge(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal SetBridge: %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            Cmd_Bus_Universal_SetBridge(data[0], data[1], &(data[2]));
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Ustawienie zadanych warto�ci wychylenia serw.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Universal_SetServo(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal SetServo: %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            Cmd_Bus_Universal_SetServo(data[0], data[1], &(data[2]));
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Ustawienie zadanych warto�ci wype�nienia PWM�w mocy.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Universal_SetPwm(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal SetPwm: %d %d %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            Cmd_Bus_Universal_SetPwm(data[0], data[1], &(data[2]));
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Komenda dodana na przysz�o��, aktualnie nie jest u�ywana.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Universal_SetGpio(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal SetGpio: %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            Cmd_Bus_Universal_SetGpio(data[0], data[1], data[2], data[3], data[4]);
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * ��danie odczytania aktualnych warto�ci belek tensometrycznych. W odpowiedzi Master zwraca seri� ramek UNIVERSAL_GET_WEIGHT, po jednej na ka�d� belk� danego modu�u uniwersalnego.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Universal_GetWeightRequest(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal GetWeightRequest: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        uint8_t id = data[0];
        for (uint8_t index=0; index<BUS_UNIVERSAL_COUNT; index++) {
            if (id == bus_universal[index].id) {
                //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki
                Cmd_UART_Universal_GetWeight(id, 0);
            }
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zwraca surow� warto�� odczytan� z zadanej belki tensometrycznej modu�u uniwersalnego o konkretnym ID.
 * @param id                bajt identyfikacji urzadzenia odbiorczego
 * @param loadcell_index    numer belki tensometrycznej (na przyszlosc, aktualnie niewspierane)
 */
void Cmd_UART_Universal_GetWeight(uint8_t id, uint8_t loadcell_index) {
    if ((logic.link_type == LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)) {
        uart_packet_t msg = {
            .cmd = UART_CMD_UNIVERSAL_GET_WEIGHT,
            .arg_count = UART_ARG_UNIVERSAL_GET_WEIGHT,
            .origin = logic.link_type,
        };

        for (uint8_t index=0; index<BUS_UNIVERSAL_COUNT; index++) {
            if (id == bus_universal[index].id) {
                //znaleziono strukture odpowiadajaca modulowi o podanym ID
                msg.args[0] = id;
                msg.args[1] = loadcell_index;

                uint32_t tmp = (uint32_t)bus_universal[index].loadcell_value;
                msg.args[2] = (uint8_t)((tmp >> 24) & 0xFF);
                msg.args[3] = (uint8_t)((tmp >> 16) & 0xFF);
                msg.args[4] = (uint8_t)((tmp >> 8) & 0xFF);
                msg.args[5] = (uint8_t)((tmp) & 0xFF);
                Queues_SendUARTFrame(&msg);
            }
        }
    }
}



