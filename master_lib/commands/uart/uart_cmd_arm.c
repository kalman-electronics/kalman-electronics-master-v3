//=====================================================================
//                      Arm Controller v2
//=====================================================================

#include <string.h>
#include "uart_cmd.h"
#include "../can/can_cmd.h"
#include "../../shared/logic.h"

/**
 * Ustawianie zadanej pozycji cz�on�w ramienia.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Arm_SetPos(uint8_t* data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_cyclic) {
            debug_printf("[%s] Arm SetPos: %d %d %d %d %d %d %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7], data[8], data[9], data[10], data[11]);
        //}

        for (uint8_t i=0; i<6; i++) {
            int16_t pos = (int16_t)((data[2*i]<<8) + data[2*i+1]);
            bus_arm.required_pos[i] = pos;
        }

        Timer_ResetTimeout(TIMER_ARM_TIMEOUT);

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Ustawianie zadanego stanu elektromagnesu.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Arm_SetMagnet(uint8_t* data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Arm SetMagnet: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            Cmd_Bus_Arm_SetMagnet(data[0]);
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zlecenie kalibracji rozregulowanego cz�onu.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Arm_Calibrate(uint8_t* data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Arm Calibrate: %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            static uint8_t buf[] = "do it";
            if (memcmp(data, buf, 5) == 0) {
                Cmd_Bus_Arm_Calibrate(data[5]);
            }
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * ��danie odczytania aktualnej warto�ci napi�cia na sondzie manipulatora.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Arm_GetVoltageRequest(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            //TODO:debug_sprintf("[%s] Arm GetVoltageRequest\r\n",
            //        (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"));
        //}

        Cmd_UART_Arm_GetVoltage(link_type);

        Cmd_UART_BlinkLed(link_type);
    }
}

/*
 *  TX Frames
 */

/**
 * Zwracanie aktualnych pozycji cz�on�w ramienia.
 */
void Cmd_UART_Arm_GetPos(void) {
    if ((logic.link_type == LINK_RF_UART) ||  (logic.link_type == LINK_AUTO_UART)) {
        uart_packet_t msg = {
            .cmd = UART_CMD_ARM_GET_POS,
            .arg_count = UART_ARG_ARM_GET_POS,
            .origin = logic.link_type,
        };

        for (uint8_t i=0; i<6; i++) {
            uint16_t pos = (uint16_t)(bus_arm.current_pos[i]);
            msg.args[2*i]   = (uint8_t)(pos >> 8);
            msg.args[2*i+1] = (uint8_t)(pos & 0xFF);
        }

        Queues_SendUARTFrame(&msg);
    }
}



/**
 * Zwracanie aktualnej warto�ci napi�cia zmierzonego na wej�ciu +-24V.
 */
void Cmd_UART_Arm_GetVoltage(uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        uart_packet_t msg = {
            .cmd = UART_CMD_ARM_GET_VOLTAGE,
            .arg_count = UART_ARG_ARM_GET_VOLTAGE,
            .origin = link_type,
            .args = {(uint8_t)(bus_arm.measured_voltage >> 8), (uint8_t)(bus_arm.measured_voltage & 0xFF)}
        };

        Queues_SendUARTFrame(&msg);
    }
}
