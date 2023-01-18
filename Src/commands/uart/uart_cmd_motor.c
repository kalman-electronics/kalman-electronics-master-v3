//=====================================================================
//                      Motor Controller v2
//=====================================================================

#include <string.h>
#include "uart_cmd.h"
#include "commands/can/can_cmd.h"


/**
 * Ustawianie zadanej pr�dko�ci obrotu k� oraz wychylenia modu��w skr�tu.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Motor_SetWheels(uint8_t *data, uart_packet_link_t link_type) {
    if (link_type == logic.link_type) {
        //if (logic_flash.debug_info & debug_comm_cyclic) {
            debug_printf("[%s] Motor SetWheels: %d %d %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
        //}

        for (uint8_t i=0; i<4; i++) {
            bus_motor.required_speed[i] = data[i];
            bus_motor.required_angle[i] = data[i+4];
        }
        Timer_ResetTimeout(TIMER_MOTOR_TIMEOUT);

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zlecenie kalibracji rozregulowanego modu�u skr�tu.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Motor_Calibrate(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Motor Calibrate: %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            static uint8_t buf[] = "do it";
            if (memcmp(data, buf, 5) == 0) {
                Cmd_Bus_Motor_Calibrate(data[5]);
            }
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zwracanie aktualnej pr�dko�ci obrotu k� oraz wychylenia modu��w skr�tu.
 */
void Cmd_UART_Motor_GetWheels(void) {
    uart_packet_t msg = {
        .cmd = UART_CMD_MOTOR_GET_WHEELS,
        .arg_count = UART_ARG_MOTOR_GET_WHEELS,
        .origin = logic.link_type | LINK_RF_UART, // When using autonomy mode, send a frame onto rf channel as well
    };

    for (uint8_t i=0; i<4; i++) {
        uint16_t speed = (uint16_t)(bus_motor.current_speed[i]);
        msg.args[2*i]   = (uint8_t)(speed >> 8);
        msg.args[2*i+1] = (uint8_t)(speed & 0xFF);
        msg.args[8+i]   = (uint8_t)(bus_motor.current_angle[i]);

        bus_motor.current_speed[i] = 0;
    }

    Queues_SendUARTFrame(&msg);
}
