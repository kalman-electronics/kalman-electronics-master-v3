//=====================================================================
//                          Arm 6 DOF
//=====================================================================

#include <string.h>
#include "uart_cmd.h"
#include "commands/can/can_cmd.h"
#include "shared/logic.h"

/*
 *  RX Frames
 */

void Arm_6DOF_SetRequiredByMode(uint8_t *data, arm_6dof_mode_t mode) {
    uint16_t nbytes;

    switch(mode) {
        case ARM_6DOF_POSITION_MODE:
            nbytes = sizeof(bus_arm_6dof.required.position);
            break;
        case ARM_6DOF_VELOCITY_MODE:
            nbytes = sizeof(bus_arm_6dof.required.velocity);
            break;
        default:
            return;
    }

    memcpy((void*)&bus_arm_6dof.required, data, nbytes);
    memcpy((void*)&bus_arm_6dof.mode, &mode, sizeof(mode));
}

void Cmd_UART_Arm6DOF_SetPos(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {

        Arm_6DOF_SetRequiredByMode(data, ARM_6DOF_POSITION_MODE);

        Cmd_UART_BlinkLed(link_type);
    }

    GpioExpander_SetLed(LED_DEBUG1, on, 50);
}

void Cmd_UART_Arm6DOF_SetVelocity(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {

        Arm_6DOF_SetRequiredByMode(data, ARM_6DOF_VELOCITY_MODE);

        Cmd_UART_BlinkLed(link_type);
    }

    GpioExpander_SetLed(LED_DEBUG2, on, 50);
}

void Cmd_UART_Arm6DOF_SetGripper(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {

        memcpy((void*)&bus_arm_6dof.gripper, data, sizeof(bus_arm_6dof.gripper));

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Arm6DOF_GetPos(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            //debug_printf("[%s] Arm GetVoltageRequest\r\n",
                    //(link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"));
        //}

        Cmd_UART_Arm6DOF_GetPos_helper(link_type);

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Arm6DOF_PositioningStart(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {

    	if (Logic_GetUptime() >= LOGIC_COMM_START_TIME)
    	{
    		Cmd_Bus_Arm6DOF_PositioningStart(data[0]);
    	}

        Cmd_UART_BlinkLed(link_type);
    }

    GpioExpander_SetLed(LED_DEBUG1, on, 50);
}

void Cmd_UART_Arm6DOF_PositioningAbort(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {

    	if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
    		Cmd_Bus_Arm6DOF_PositioningAbort();
    	}


        Cmd_UART_BlinkLed(link_type);
    }

    GpioExpander_SetLed(LED_DEBUG1, on, 50);
}

void Cmd_UART_Arm6DOF_SetActualPos(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {

    	if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
    		Cmd_Bus_Arm6DOF_SetActualPos(data[0], data[1], data[2]);
    	}

        Cmd_UART_BlinkLed(link_type);
    }

    GpioExpander_SetLed(LED_DEBUG1, on, 50);
}

/*
 *  TX Frames
 */

void Cmd_UART_Arm6DOF_GetPos_helper(uart_packet_link_t link_type) {
    if ((logic.link_type == LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)) {
        uart_packet_t msg = {
                .cmd = UART_CMD_ARM_6DOF_GET_POS,
                .arg_count = UART_ARG_ARM_6DOF_GET_POS,
                .origin = link_type,
        };

        memcpy(msg.args, (void*)&bus_arm_6dof.current.position, UART_ARG_ARM_6DOF_GET_POS);

        Queues_SendUARTFrame(&msg);
    }
}
