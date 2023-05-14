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
    memcpy((void*)&bus_arm_6dof.mode, &mode, sizeof(mode));

    switch(mode) {
        case ARM_6DOF_POSITION_MODE:
            memcpy((void*)&bus_arm_6dof.required, data, sizeof(bus_arm_6dof.required.position));
            Cmd_Bus_Arm6DOF_SetPos();
            break;
        case ARM_6DOF_VELOCITY_MODE:
        	memcpy((void*)&bus_arm_6dof.required, data, sizeof(bus_arm_6dof.required.velocity));
            Cmd_Bus_Arm6DOF_SetVelocity();
            break;
        default:
            return;
    }
}

void Cmd_UART_Arm6DOF_SetPos(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {

        Arm_6DOF_SetRequiredByMode(data, ARM_6DOF_POSITION_MODE);

        // Reset periodical arm master timeout
        Timer_ResetTimeout(TIMER_CAN_TRAFFIC_SET_ARM);
        Timer_ResetTimeout(TIMER_ARM_TIMEOUT);

        Cmd_UART_BlinkLed(link_type);
    }

    GpioExpander_SetLed(LED_DEBUG1, on, 50);
}

void Cmd_UART_Arm6DOF_SetPosVel(uint8_t *data, uart_packet_link_t link_type){
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {

        memcpy((void*)bus_arm_6dof.per_joint_vel_pos.vel_01_radps, data, sizeof(bus_arm_6dof.per_joint_vel_pos));

        Cmd_UART_BlinkLed(link_type);
    }

    GpioExpander_SetLed(LED_DEBUG1, on, 50);
}

void Cmd_UART_Arm6DOF_SetVelocity(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {

        Arm_6DOF_SetRequiredByMode(data, ARM_6DOF_VELOCITY_MODE);

        // Reset periodical arm master timeout
        Timer_ResetTimeout(TIMER_CAN_TRAFFIC_SET_ARM);
        Timer_ResetTimeout(TIMER_ARM_TIMEOUT);

        Cmd_UART_BlinkLed(link_type);
    }

    GpioExpander_SetLed(LED_DEBUG2, on, 50);
}

void Cmd_UART_Arm6DOF_SetGripper(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART))
        && (link_type == logic.link_type)) {
        bus_arm_6dof.gripper = data[1] | (data[0] << 8);

        Cmd_Bus_Arm6DOF_SetGripper();

        // Reset arm master timeout
        Timer_ResetTimeout(TIMER_ARM_TIMEOUT);

        Cmd_UART_BlinkLed(link_type);
    }
}


void Cmd_UART_Arm6DOF_Autoclick_SetPos(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type))  {
        Cmd_Bus_Arm6DOF_Autoclick_SetPos(data[0]);

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

void Cmd_UART_Arm6DOF_KeyboardClick(uint8_t *data, uart_packet_link_t link_type) {
	if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type)) {
		if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
			Cmd_Bus_Arm6DOF_KeyboardClick();
		}

		Cmd_UART_BlinkLed(link_type);
	}
}

void Cmd_UART_Arm6DOF_SoftReset(uint8_t *data, uart_packet_link_t link_type) {
	if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type)) {
		if (Logic_GetUptime() >= LOGIC_COMM_START_TIME){
			Cmd_Bus_Arm6DOF_SoftReset();
		}

		Cmd_UART_BlinkLed(link_type);
	}
}

void Cmd_UART_Arm6DOF_GetProbeRequest(uint8_t* data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) {
        uart_packet_t msg = {
			.cmd = UART_CMD_ARM_6DOF_GET_PROBE,
			.arg_count = UART_ARG_ARM_6DOF_GET_PROBE,
			.origin = link_type,
        };

        memcpy(msg.args, (void*) &(bus_arm_6dof.kutong), sizeof(bus_arm_6dof.kutong));

        Queues_SendUARTFrame(&msg);
    }
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

void Cmd_UART_Arm6DOF_GetGripper() {
	if ((logic.link_type== LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)) {
		uart_packet_t msg = {
			.cmd = CAN_CMD_ARM_6DOF_GET_GRIPPER,
			.arg_count = CAN_ARG_ARM_6DOF_GET_GRIPPER,
			.origin = logic.link_type,
		};

		memcpy((void*)msg.args, (void*)&bus_arm_6dof.gripperActual, CAN_ARG_ARM_6DOF_GET_GRIPPER);

		Queues_SendUARTFrame(&msg);
	}
}
