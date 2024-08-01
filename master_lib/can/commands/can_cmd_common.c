#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"

/*
 *  RX Frames
 */

//TODO: ramki RESET_ALL i RESET_DEVICE obsluzone wewnatrz modulu CANlib_v2 - patrz CANlib_ResetAll i CANlib_ResetDevice

/**
 * Zwraca informacje o konfiguracji PID modułu. Jedna ramka dotyczy jednego silnika. Po odebraniu ramki typu GET_PID_REQUEST, kontroler musi wysłać po jednej ramce dla każdego użytego regulatora PID.
 * Kodowanie i wartości - zobacz SET_PID.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
 */
void Cmd_Bus_Common_GetPid(uint8_t *data) {
    debug_printf("[CAN] GetPid, args=");
    for (uint16_t i=0; i < CAN_ARG_GET_PID; i++) {
        debug_printf("%02x ", data[i]);
    }
    debug_printf("\r\n");

    uint16_t p = ((uint16_t)data[0] << 8) + data[1];
    uint8_t i = data[2],
            d = data[3],
            min = data[4],
            max = data[5];
    can_device_t id = data[6];
    uint8_t flags = data[7];
    //TODO:CMD Cmd_Common_GetPid(p, i, d, min, max, id, flags);

    if      (id == DEVICE_MOTOR)    { GpioExpander_SetLed(LED_MOTOR, on, 20);; }
    else if (id == DEVICE_ARM)      { GpioExpander_SetLed(LED_ARM, on, 20); }
}

/*
 *  TX Frames
 */

/**
 * Reset wszystkich urządzeń. Wykonany tylko jeśli argumenty przyjmują opisaną niżej wartość.
 */
void Cmd_Bus_Common_ResetAll() {
    can_packet_t msg = {
        .cmd = CAN_CMD_RESET_ALL,
        .arg_count = CAN_ARG_RESET_ALL,
        .args = {'d', 'o', ' ', 'i', 't'},
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Reset urządzenia o zadanym identyfikatorze. Wykonywany tylko jeśli argumenty przyjmują opisaną poniżej wartość.
 * @param id        identyfikator urządzenia do zresetowania
 */
void Cmd_Bus_Common_ResetDevice(can_device_t id) {
    can_packet_t msg = {
        .cmd = CAN_CMD_RESET_DEVICE,
        .arg_count = CAN_ARG_RESET_DEVICE,
        .args = {'d', 'o', ' ', 'i', 't', id},
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Zmiana nastaw PID dla wybranych silników. Ramka ma jednolitą strukturę dla wszystkich modułów, co znacznie ułatwia sterowanie i przekazywanie informacji.
 * @param p         współczynnik P
 * @param i         współczynnik I
 * @param d         współczynnik D
 * @param min       minimalne wypełnienie PWM (w %, zakres 0..100)
 * @param max       maksymalne wypełnienie PWM (w %, zakres 0..100)
 * @param id        identyfikator urządzenia, którego dotyczy ramka
 * @param flags     flagi silników kontrolera, których dotyczy zmiana (gdy 1, PID zostanie nadpisany)
 */
void Cmd_Bus_Common_SetPid(uint16_t p, uint8_t i, uint8_t d, uint8_t min, uint8_t max, can_device_t id, uint8_t flags) {
    can_packet_t msg = {
        .cmd = CAN_CMD_SET_PID,
        .arg_count = CAN_ARG_SET_PID,
        .args = {p >> 8, p & 0xFF, i, d, min, max, id, flags},
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Żądanie pobrania wszystkich konfiguracji PID dla wybranego modułu. W odpowiedzi kontroler przesyła serię ramek GET_PID, po jednej dla każdego silnika z konfiguracją PID.
 * @param id        identyfikator urządzenia, którego dotyczy ramka
 */
void Cmd_Bus_Common_GetPidRequest(can_device_t id) {
    can_packet_t msg = {
            .cmd = CAN_CMD_GET_PID_REQUEST,
            .arg_count = CAN_ARG_GET_PID_REQUEST,
            .args = {id},
    };

    Queues_SendCANFrame(&msg);
}
