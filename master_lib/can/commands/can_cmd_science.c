#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"
#include "uart/commands/uart_cmd.h"

/*
 *  RX Frames
 */

/**
 * Zwracanie aktualnych temperatur próbek z kanałów 1 i 2.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
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
 * Zwracanie aktualnych temperatur próbek z kanałów 3 i 4.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
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
 * Zwracanie aktualnych wilgotności próbek ze wszystkich kanałów.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
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
 * Zwracanie aktualnych odczytów pomiarów atmosferycznych.
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
 * Zwracanie aktualnej surowej wartości odczytu z belki tensometrycznej. Jedna ramka dotyczy tylko jednej belki.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
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
 * Odczytywanie aktualnych statusów podsystemów i danych kontrolnych.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
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

/*
 *  TX Frames
 */
