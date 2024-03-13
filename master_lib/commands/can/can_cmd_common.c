#include <string.h>
#include "can_cmd.h"
#include "../../hw/hw.h"

/*
 *  RX Frames
 */

//TODO: ramki RESET_ALL i RESET_DEVICE obsluzone wewnatrz modulu CANlib_v2 - patrz CANlib_ResetAll i CANlib_ResetDevice

/**
 * Zwrot informacji o konfiguracji PID modu�u. Jedna ramka dotyczy jednego silnika. Po odebraniu ramki GET_PID_REQUEST, kontroler musi odes�a� po jednej ramce na ka�dy u�yty regulator PID.
 * Kodowanie i warto�ci - patrz SET_PID.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
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
 * Reset wszystkich urz�dze�. Wykonany tylko je�li argumenty przyjmuj� opisan� ni�ej warto��.
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
 * Reset urz�dzenia o zadanym identyfikatorze. Wykonany tylko je�li argumenty przyjmuj� opisan� ni�ej warto��.
 * @param id        identyfikator urzadzenia do zresetowania
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
 * Zmiana nastaw PID dla wybranych silnik�w. Ramka ma jednolit� struktur� dla wszystkich modu��w, co znacznie upro�ci sterowanie i przekazywanie informacji.
 * @param p         wspolczynnik P
 * @param i         wspolczynnik I
 * @param d         wspolczynnik D
 * @param min       minimalne wypelnienie PWM (w %, zakres 0..100)
 * @param max       maksymalne wypelnienie pWM (w %, zakres 0..100)
 * @param id        identyfikator urzadzenia, ktorego dotyczy ramka
 * @param flags     flagi silnikow kontrolera, ktorych dotyczy zmiana (gdy 1, PID zostanie nadpisany)
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
 * ��danie pobrania wszystkich konfiguracji PID dla wybranego modu�u. W odpowiedzi kontroler przesy�a seri� ramek GET_PID, po jednej dla ka�dego silnika z konfiguracj� PID.
 * @param id        identyfikator urzadzenia, ktorego dotyczy ramka
 */
void Cmd_Bus_Common_GetPidRequest(can_device_t id) {
    can_packet_t msg = {
            .cmd = CAN_CMD_GET_PID_REQUEST,
            .arg_count = CAN_ARG_GET_PID_REQUEST,
            .args = {id},
    };

    Queues_SendCANFrame(&msg);
}
