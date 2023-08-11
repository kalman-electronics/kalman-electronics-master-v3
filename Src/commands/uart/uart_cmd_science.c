//=====================================================================
//                          Sajens Module
//=====================================================================

#include "uart_cmd.h"
#include "commands/can/can_cmd.h"

/**
 * ��danie odczytania aktualnych warto�ci temperatur i wilgotno�ci pr�bek pomiarowych. W odpowiedzi Master zwraca seri� ramek SCIENCE_GET_SAMPLES,
 * po jednej na ka�d� pr�bk� pomiarow� modu�u science.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Science_GetSamplesRequest(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Science GetSamplesRequest: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        Cmd_UART_Science_GetSamples(data[0], 0);
        Cmd_UART_Science_GetSamples(data[0], 1);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * ��danie odczytania aktualnych warto�ci belek tensometrycznych. W odpowiedzi Master zwraca seri� ramek SCIENCE_GET_WEIGHT, po jednej na ka�d� belk� modu�u science.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Science_GetWeightRequest(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Science GetWeightRequest: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        Cmd_UART_Science_GetWeight(data[0], 0);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * ��danie odczytania aktualnych warto�ci pomiar�w atmosferycznych. W odpowiedzi Master zwraca ramk� SCIENCE_GET_ATMOSPHERE.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Science_GetAtmosphereRequest(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Science GetAtmosphereRequest: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        Cmd_UART_Science_GetAtmosphere(data[0]);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Zwraca aktualne warto�ci pomiar�w atmosferycznych modu�u science o konkretnym ID.
 * @param id                bajt identyfikacji urzadzenia odbiorczego
 */
void Cmd_UART_Science_GetAtmosphere(uint8_t id) {
    if ((logic.link_type == LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)) {
        uart_packet_t msg = {
            .cmd = UART_CMD_SCIENCE_GET_ATMOSPHERE,
            .arg_count = UART_ARG_SCIENCE_GET_ATMOSPHERE,
            .origin = logic.link_type,
        };

        for (uint8_t index=0; index<BUS_SCIENCE_COUNT; index++) {
            if (id == bus_science[index].id) {
                //znaleziono strukture odpowiadajaca modulowi o podanym ID

                uint16_t temp = bus_science[index].air_temperature;
                uint32_t pressure = bus_science[index].air_pressure;
                msg.args[0] = id;
                msg.args[1] = (uint8_t)((temp >> 8) & 0xFF);
                msg.args[2] = (uint8_t)((temp) & 0xFF);
                msg.args[3] = bus_science[index].air_humidity;
                msg.args[4] = (uint8_t)((pressure >> 24) & 0xFF);
                msg.args[5] = (uint8_t)((pressure >> 16) & 0xFF);
                msg.args[6] = (uint8_t)((pressure >> 8) & 0xFF);
                msg.args[7] = (uint8_t)((pressure) & 0xFF);

                Queues_SendUARTFrame(&msg);
            }
        }
    }
}

/**
 * Zwraca surow� warto�� odczytan� z zadanej belki tensometrycznej modu�u science o konkretnym ID.
 * @param id                bajt identyfikacji urzadzenia odbiorczego
 * @param loadcell_index    numer belki tensometrycznej (0..3)
 */
void Cmd_UART_Science_GetWeight(uint8_t id, uint8_t loadcell_index) {
    if ((logic.link_type == LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)) {
        uart_packet_t msg = {
            .cmd = UART_CMD_SCIENCE_GET_WEIGHT,
            .arg_count = UART_ARG_SCIENCE_GET_WEIGHT,
            .origin = logic.link_type,
        };

        for (uint8_t index=0; index<BUS_SCIENCE_COUNT; index++) {
            if (id == bus_science[index].id) {
                //znaleziono strukture odpowiadajaca modulowi o podanym ID

                if (loadcell_index < 4) {
                    msg.args[0] = id;
                    msg.args[1] = loadcell_index;

                    uint32_t tmp = (uint32_t)bus_science[index].loadcell_raw[loadcell_index];
                    msg.args[2] = (uint8_t)((tmp >> 24) & 0xFF);
                    msg.args[3] = (uint8_t)((tmp >> 16) & 0xFF);
                    msg.args[4] = (uint8_t)((tmp >> 8) & 0xFF);
                    msg.args[5] = (uint8_t)((tmp) & 0xFF);

                    Queues_SendUARTFrame(&msg);
                }
            }
        }
    }
}

/**
 * Zwraca aktualn� warto�� temperatury i wilgotno�ci zadanej pr�bki pomiarowej modu�u science o konkretnym ID.
 * @param id                bajt identyfikacji urzadzenia odbiorczego
 * @param sample_index      numer pr�bki (0..3)
 */
void Cmd_UART_Science_GetSamples(uint8_t id, uint8_t sample_index) {
    if ((logic.link_type == LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)) {
        uart_packet_t msg = {
            .cmd = UART_CMD_SCIENCE_GET_SAMPLES,
            .arg_count = UART_ARG_SCIENCE_GET_SAMPLES,
            .origin = logic.link_type,
        };

        for (uint8_t index=0; index<BUS_SCIENCE_COUNT; index++) {
            if (id == bus_science[index].id) {
                //znaleziono strukture odpowiadajaca modulowi o podanym ID

                if (sample_index < 4) {
                    msg.args[0] = id;
                    msg.args[1] = sample_index;

                    uint16_t temp = bus_science[index].sample_temperature[sample_index];
                    msg.args[2] = (uint8_t)((temp >> 8) & 0xFF);
                    msg.args[3] = (uint8_t)((temp) & 0xFF);
                    msg.args[4] = bus_science[index].sample_humidity[sample_index];

                    Queues_SendUARTFrame(&msg);
                }
            }
        }
    }
}
