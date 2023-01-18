#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"
#include "commands/uart/uart_cmd.h"

/*
 *  RX Frames
 */

/**
 * Odczytywanie aktualnej pozycji pierwszych 4 cz�on�w ramienia.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Arm_GetPos1(uint8_t* data) {
    for (uint8_t ch = 0; ch < 4; ch++) {
        bus_arm.current_pos[ch] = (int16_t)((data[2*ch] << 8) + data[2*ch+1]);
    }

    GpioExpander_SetLed(LED_ARM, on, 20);
}

/**
 * Odczytywanie aktualnej pozycji ostatnich 2 cz�on�w ramienia.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Arm_GetPos2(uint8_t* data) {
    for (uint8_t ch = 0; ch < 2; ch++) {
        bus_arm.current_pos[ch+4] = (int16_t)((data[2*ch] << 8) + data[2*ch+1]);
    }

    GpioExpander_SetLed(LED_ARM, on, 20);
}

/**
 * Odczytywanie aktualnej warto�ci zmierzonego napi�cia na wej�ciu +-24V.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Arm_Get24V(uint8_t* data) {
    bus_arm.measured_voltage = (int16_t)((data[0] << 8) + data[1]);
    GpioExpander_SetLed(LED_ARM, on, 20);
}

/**
 * Odczytywanie aktualnych status�w podsystem�w i danych kontrolnych.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Arm_GetStatus(uint8_t* data) {
    bus_arm.limit_status = (data[0] << 8) | data[1];
    bus_arm.motor_status = data[2];
    bus_arm.status = data[3];
    bus_arm.supply_voltage = data[4];

    GpioExpander_SetLed(LED_ARM, on, 20);
}

/**
 * Ramka na potrzeby test�w i rozwoju oprogramowania. Przekazywana na �wiat transparentnie, bez ingerencji.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Arm_DebugRx(uint8_t *data) {
    Cmd_UART_Common_DebugRx(data, DEVICE_ARM);

    GpioExpander_SetLed(LED_ARM, on, 20);
}

/*
 *  TX Frames
 */

/**
 * Ustawianie zadanej pozycji pierwszych 4 cz�on�w ramienia.
 */
void Cmd_Bus_Arm_SetPos1() {
    can_packet_t msg = {
        .cmd = CAN_CMD_ARM_SET_POS1,
        .arg_count = CAN_ARG_ARM_SET_POS1,
    };

    for (uint8_t ch = 0; ch<4; ch++) {
        uint16_t value = (uint16_t)(bus_arm.required_pos[ch]);
        msg.args[2*ch] = value >> 8;
        msg.args[2*ch+1] = value & 0xFF;
    }

    Queues_SendCANFrame(&msg);
}



/**
 * Ustawianie zadanej pozycji ostatnich 2 cz�on�w ramienia.
 */
void Cmd_Bus_Arm_SetPos2() {
    can_packet_t msg = {
        .cmd = CAN_CMD_ARM_SET_POS2,
        .arg_count = CAN_ARG_ARM_SET_POS2,
    };

    for (uint8_t ch = 0; ch<2; ch++) {
        uint16_t value = (uint16_t)(bus_arm.required_pos[ch+4]);
        msg.args[2*ch] = value >> 8;
        msg.args[2*ch+1] = value & 0xFF;
    }

    Queues_SendCANFrame(&msg);
}



/**
 * Ustawianie zadanego stanu elektromagnesu.
 * @param state     0 wylacza magnes, wszystko inne wlacza
 */
void Cmd_Bus_Arm_SetMagnet(uint8_t state) {
    can_packet_t msg = {
        .cmd = CAN_CMD_ARM_SET_MAGNET,
        .arg_count = CAN_ARG_ARM_SET_MAGNET,
        .args = {state}
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Zlecenie kalibracji rozregulowanego cz�onu. Po ustawieniu cz�onu w pozycji kra�c�wki MIN, wys�anie ramki spowoduje nadpisanie warto�ci odniesienia, wzgl�dem kt�rej obliczana jest pozycja cz�onu.
 * @note  W przypadku cz�onu chwytaka, odebranie ramki spowoduje rozpocz�cie procedury autokalibracji - podjazd do kra�c�wki MIN i zapisanie tej pozycji jako odniesienie. Kalibracj� chwytaka nale�y wykona� przy ka�dym starcie kontrolera (patrz komenda ARM_GET_STATUS, bajt statusu kontrolera, flaga GNC), ze wzgl�du na enkoderowe sprz�enie zwrotne.
 * @param joint
 */
void Cmd_Bus_Arm_Calibrate(uint8_t joint) {
    can_packet_t msg = {
        .cmd = CAN_CMD_ARM_CALIBRATE,
        .arg_count = CAN_ARG_ARM_CALIBRATE,
        .args = {'d', 'o', ' ', 'i', 't', joint}
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Ramka na potrzeby test�w i rozwoju oprogramowania. Przekazywa� kontrolerowi transparentnie, bez ingerencji.
 * @param data      wskaznik na 8-bajtowy bufor danych
 */
void Cmd_Bus_Arm_DebugTx(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_ARM_DEBUG_TX,
            .arg_count = CAN_ARG_ARM_DEBUG_TX,
    };
    memcpy(msg.args, data, 8);

    Queues_SendCANFrame(&msg);
}
