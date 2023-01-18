#include <string.h>
#include "can_cmd.h"

/*
 *  RX Frames
 */

/**
 * Odczytywanie aktualnych status�w podsystem�w i danych kontrolnych.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 *
void Bus_Party_GetStatus(uint8_t *data, uint8_t count) {
    if (count == CAN_ARG_PARTY_GET_STATUS) {
        //todo party status

        GpioExpander_SetLed(led_party, on, 20);
    }
}
*/


/**
 * Ramka na potrzeby test�w i rozwoju oprogramowania. Przekazywana na �wiat transparentnie, bez ingerencji.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 *
void Bus_Party_DebugRx(uint8_t *data, uint8_t count) {
    if (count == CAN_ARG_PARTY_DEBUG_RX) {
        Cmd_Common_DebugRx(data, DEVICE_PARTY);

        GpioExpander_SetLed(led_party, on, 20);
    }
}
*/

/*
 *  TX Frames
 */

/**
 * Sterowanie zapalnikami. Po aktywacji zapalnik jest zasilany przez 2s.
 * @note  Zapalnik nr 8 jest nieobs�ugiwany, ze wzgl�du na wykorzystanie jego detektora jako wej�cie muzyczne.
 * @param flags     flagi aktywacji zapalnikow (bit 0 = I1 ... bit 6 = I7)
 */
void Cmd_Bus_Party_SetIgniters(uint8_t flags) {
    can_packet_t msg = {
        .cmd = CAN_CMD_PARTY_SET_IGNITERS,
        .arg_count = CAN_ARG_PARTY_SET_IGNITERS,
        .args = {flags},
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Sterowanie wska�nikami pracy autonomicznej - lamp� ostrzegawcz� i syren�.
 * @param light     gdy 1, lampa zostaje aktywowana
 * @param buzzer    gdy 1, syrena zostaje aktywowana
 */
void Cmd_Bus_Party_SetAuto(uint8_t light, uint8_t buzzer) {
    can_packet_t msg = {
        .cmd = CAN_CMD_PARTY_SET_AUTO,
        .arg_count = CAN_ARG_PARTY_SET_AUTO,
        .args = {(light << 0) | (buzzer << 1)},
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Zmiana animacji diod RGB. Diody zmieniaj� swoj� jasno�� w rytm muzyki, ale animacja kolor�w zale�y od wybranego trybu. Domy�lnie diody s� wy��czone.
 * @param anim  zadany typ animacji
 */
void Cmd_Bus_Party_SetRgb(uint8_t anim) {
    can_packet_t msg = {
        .cmd = CAN_CMD_PARTY_SET_RGB,
        .arg_count = CAN_ARG_PARTY_SET_RGB,
        .args = {anim},
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Sterowanie zasilaniem blok�w mocy
 * @param flags     flagi dezaktywacji blokow mocy
 */
void Cmd_Bus_Party_SetPower(uint8_t flags) {
    can_packet_t msg = {
        .cmd = CAN_CMD_PARTY_SET_POWER,
        .arg_count = CAN_ARG_PARTY_SET_POWER,
        .args = {flags},
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Ramka na potrzeby test�w i rozwoju oprogramowania. Przekazywa� kontrolerowi transparentnie, bez ingerencji.
 * @param data      wskaznik na 8-bajtowy bufor danych
 */
void Cmd_Bus_Party_DebugTx(uint8_t* data) {
    can_packet_t msg = {
        .cmd = CAN_CMD_PARTY_DEBUG_TX,
        .arg_count = CAN_ARG_PARTY_DEBUG_TX,
    };
    memcpy(msg.args, data, 8);

    Queues_SendCANFrame(&msg);
}

