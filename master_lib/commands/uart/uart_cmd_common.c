//=====================================================================
//         komendy wspolne dla modulow systemu elektroniki
//=====================================================================

#include <string.h>
#include "uart_cmd.h"
#include "../can/can_cmd.h"

/*
 *  RX Frames
 */

/**
 * Reset wszystkich urzadzen na magistrali CAN, wlacznie z modulem Master.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Common_ResetAll(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Common ResetAll\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"));
        //}

        Cmd_Bus_Common_ResetAll();
        //BSP_Reset(100);

        Cmd_UART_BlinkLed(link_type);
        HAL_Delay(100);
        NVIC_SystemReset();
    }
}



/**
 * Reset urz�dzenia o zadanym identyfikatorze.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Common_ResetDevice(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Common ResetDevice: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        if (data[0] == DEVICE_MASTER) {
            //BSP_Reset(20);
        	HAL_Delay(20);
        	NVIC_SystemReset();
        }
        else {
            Cmd_Bus_Common_ResetDevice(data[0]);
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zmiana nastaw PID dla wybranych silnik�w.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Common_SetPid(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Common SetPid: %d %d %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
        //}

        uint16_t p = ((uint16_t)data[0] << 8) + data[1];
        uint8_t i = data[2],
                d = data[3],
                min = data[4],
                max = data[5];
        can_device_t id = data[6];
        uint8_t flags = data[7];
        Cmd_Bus_Common_SetPid(p, i, d, min, max, id, flags);

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * ��danie pobrania wszystkich konfiguracji PID dla wybranego modu�u.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Common_GetPidRequest(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Common GetPidRequest: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        Cmd_Bus_Common_GetPidRequest(data[0]);

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Ramka na potrzeby test�w i rozwoju oprogramowania wybranego modu�u.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Common_DebugTx(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Common DebugTx: %d %d %d %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            switch (data[8]) {
                case DEVICE_MASTER:     { break; }
                case DEVICE_MOTOR:      { Cmd_Bus_Motor_DebugTx(data);     break; }
                case DEVICE_ARM:        { Cmd_Bus_Arm_DebugTx(data);       break; }
                case DEVICE_UNIVERSAL:  { Cmd_Bus_Universal_DebugTx(data);          break; }
                case DEVICE_PARTY:      { Cmd_Bus_Party_DebugTx(data);              break; }
                case DEVICE_SCIENCE:    { Cmd_Bus_Science_DebugTx(data);            break; }
                default: break;
            }
        }

        Cmd_UART_BlinkLed(link_type);
    }
}

/*
 *  TX Frames
 */

/**
 * Zwrot informacji o konfiguracji PID modu�u. Jedna ramka dotyczy jednego silnika.
 * @param p         wspolczynnik P
 * @param i         wspolczynnik I
 * @param d         wspolczynnik D
 * @param min       minimalne wypelnienie PWM (w %, zakres 0..100)
 * @param max       maksymalne wypelnienie pWM (w %, zakres 0..100)
 * @param id        identyfikator urzadzenia, ktorego dotyczy ramka
 * @param flags     flagi silnikow kontrolera, ktorych dotyczy zmiana (ustawiony jeden konkretny bit reprezentujacy dany silnik)
 */
void Cmd_UART_Common_GetPid(uint16_t p, uint8_t i, uint8_t d, uint8_t min, uint8_t max, can_device_t id, uint8_t flags) {
    if ((logic.link_type == LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)){
        uart_packet_t msg = {
                .cmd = UART_CMD_COMMON_GET_PID,
                .arg_count = UART_ARG_COMMON_GET_PID,
                .origin = logic.link_type,
        };

        msg.args[0] = p >> 8;
        msg.args[1] = p & 0xFF;
        msg.args[2] = i;
        msg.args[3] = d;
        msg.args[4] = min;
        msg.args[5] = max;
        msg.args[6] = id;
        msg.args[7] = flags;

        Queues_SendUARTFrame(&msg);
    }
}



/**
 * Ramka na potrzeby test�w i rozwoju oprogramowania wybranego modu�u. Po odebraniu ramki na magistrali CAN/RS485, modu� Master przekazuje dane do stacji naziemnej (bez ingerencji).
 * @param data      wskaznik na bufor odebranych danych (8 bajtow)
 * @param id        identyfikator urzadzenia, ktorego dotyczy ramka
 */
void Cmd_UART_Common_DebugRx(uint8_t *data, can_device_t id) {
    if ((logic.link_type == LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)) {
        uart_packet_t msg = {
                .cmd = UART_CMD_COMMON_DEBUG_RX,
                .arg_count = UART_ARG_COMMON_DEBUG_RX,
                .origin = logic.link_type,
                .args = {(uint8_t)(bus_arm.measured_voltage >> 8), (uint8_t)(bus_arm.measured_voltage & 0xFF)}
        };

        memcpy(msg.args, data, 8);
        msg.args[8] = id;

        Queues_SendUARTFrame(&msg);
    }
}
