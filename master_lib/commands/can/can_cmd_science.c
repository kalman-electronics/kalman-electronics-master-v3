#include <string.h>
#include "can_cmd.h"
#include "../../hw/hw.h"
#include "../uart/uart_cmd.h"

//TODO: PL caption fix

/*
 *  RX Frames
 */

/**
 * Zwracanie aktualnych temperatur pr�bek z kana��w 1 i 2.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Science_GetTemperature1(uint8_t* data) {
    for (uint16_t index = 0; index < BUS_SCIENCE_COUNT; index++) {
        if (data[0] == bus_science[index].id) {
            //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki
            bus_science[index].sample_temperature[0] = (data[1]<<8) | data[2];
            bus_science[index].sample_temperature[1] = (data[3]<<8) | data[4];
            break;
        }
    }

    GpioExpander_SetLed(LED_UNIVERSAL1, on, 20);
}

/**
 * Zwracanie aktualnych temperatur pr�bek z kana��w 3 i 4.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Science_GetTemperature2(uint8_t* data) {
    for (uint16_t index = 0; index < BUS_SCIENCE_COUNT; index++) {
        if (data[0] == bus_science[index].id) {
            //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki
            bus_science[index].sample_temperature[2] = (data[1]<<8) | data[2];
            bus_science[index].sample_temperature[3] = (data[3]<<8) | data[4];
            break;
        }
    }

    GpioExpander_SetLed(LED_UNIVERSAL1, on, 20);
}

/**
 * Zwracanie aktualnych wilgotno�ci pr�bek ze wszystkich kana��w.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Science_GetHumidity(uint8_t* data) {
    for (uint16_t index = 0; index < BUS_SCIENCE_COUNT; index++) {
        if (data[0] == bus_science[index].id) {
            //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki
            for (uint8_t i=0; i<4; i++) {
                bus_science[index].sample_humidity[i] = data[i+1];
            }
            break;
        }
    }

    GpioExpander_SetLed(LED_UNIVERSAL1, on, 20);
}

/**
 * Zwracanie aktualnych odczyt�w pomiar�w atmosferycznych.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Science_GetAtmosphere(uint8_t* data) {
    for (uint16_t index = 0; index < BUS_SCIENCE_COUNT; index++) {
        if (data[0] == bus_science[index].id) {
            //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki
            bus_science[index].air_temperature = (data[1]<<8) | data[2];
            bus_science[index].air_humidity    = data[3];
            bus_science[index].air_pressure    = ((uint32_t)data[4] << 24UL) | ((uint32_t)data[5] << 16UL) | ((uint32_t)data[6] << 8UL) | ((uint32_t)data[7]);
            break;
        }
    }

    GpioExpander_SetLed(LED_UNIVERSAL1, on, 20);
}

/**
 * Zwracanie aktualnej surowej warto�ci odczytu z belki tensometrycznej. Jedna ramka dotyczy tylko jednej belki.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Science_GetWeight(uint8_t* data) {
    for (uint16_t index = 0; index < BUS_SCIENCE_COUNT; index++) {
        if (data[0] == bus_science[index].id) {
            //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki
            uint8_t loadcell_index = data[1];
            if (loadcell_index < 4) {
                bus_science[index].loadcell_raw[loadcell_index] = (int32_t)(((uint32_t)data[2] << 24UL) | ((uint32_t)data[3] << 16UL) | ((uint32_t)data[4] << 8UL) | ((uint32_t)data[5]));
            }
            break;
        }
    }

    GpioExpander_SetLed(LED_UNIVERSAL1, on, 20);
}

/**
 * Odczytywanie aktualnych status�w podsystem�w i danych kontrolnych.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Science_GetStatus(uint8_t* data) {
    for (uint16_t index = 0; index < BUS_SCIENCE_COUNT; index++) {
        if (data[0] == bus_science[index].id) {
            //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki
            bus_science[index].status = data[1];
            break;
        }
    }

    GpioExpander_SetLed(LED_UNIVERSAL1, on, 20);
}

/**
 * Ramka na potrzeby test�w i rozwoju oprogramowania. Przekazywana na �wiat transparentnie, bez ingerencji.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Science_DebugRx(uint8_t* data) {
    Cmd_UART_Common_DebugRx(data, DEVICE_SCIENCE);

    GpioExpander_SetLed(LED_UNIVERSAL1, on, 20);
}

/*
 *  TX Frames
 */

/**
 * Ramka testowa, u�ywana do sprawdzania poprawno�ci komunikacji Mastera z modu�em.
 * @param id        bajt identyfikacji urzadzenia odbiorczego
 */
void Cmd_Bus_Science_Poll(uint8_t id) {
    can_packet_t msg = {
        .cmd = CAN_CMD_SCIENCE_POLL,
        .arg_count = CAN_ARG_SCIENCE_POLL,
        .args = {id},
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Ramka na potrzeby test�w i rozwoju oprogramowania. Przekazywa� kontrolerowi transparentnie, bez ingerencji.
 * @param data      wskaznik na 8-bajtowy bufor danych
 */
void Cmd_Bus_Science_DebugTx(uint8_t* data) {
    can_packet_t msg = {
        .cmd = CAN_CMD_SCIENCE_DEBUG_TX,
        .arg_count = CAN_ARG_SCIENCE_DEBUG_TX,
    };
    memcpy(msg.args, data, 8);

    Queues_SendCANFrame(&msg);
}
