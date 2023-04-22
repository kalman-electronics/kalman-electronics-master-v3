#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"

//TODO: rename

/*
 *  RX Frames
 */

void Cmd_Bus_Arm6DOF_GetPos1(uint8_t *data) {
    memcpy((void*)&bus_arm_6dof.current.position, data, 8);

    GpioExpander_SetLed(LED_ARM, on, 20);
}

void Cmd_Bus_Arm6DOF_GetPos2(uint8_t *data) {
    memcpy((void*)&bus_arm_6dof.current.position+CAN_ARG_ARM_6DOF_SET_POS1, data, 8);
}

//TODO: size
void Cmd_Bus_Arm6DOF_GetGripper(uint8_t *data, uint8_t count) {
	memcpy((void*)&bus_arm_6dof.gripperActual, data, count);
}

void Cmd_Bus_Arm6DOF_GetSmartKutongData(uint8_t *data) {
    memcpy((void*) &(bus_arm_6dof.kutong), data, sizeof(bus_arm_6dof.kutong));
}

/*
 *  TX Frames
 */

void Cmd_Bus_Arm6DOF_SetPos() {
    can_packet_t msg = {
        .cmd = CAN_CMD_ARM_6DOF_SET_POS1,
        .arg_count = CAN_ARG_ARM_6DOF_SET_POS1,
    };

    memcpy(msg.args, (void*)&bus_arm_6dof.required.position, 8);
    Queues_SendCANFrame(&msg);

    msg.cmd = CAN_CMD_ARM_6DOF_SET_POS2;
    msg.arg_count = CAN_ARG_ARM_6DOF_SET_POS2;

    memcpy(msg.args, (void*)&bus_arm_6dof.required.position + 8, 8);
    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Arm6DOF_SetVelocity() {
    can_packet_t msg = {
        .cmd = CAN_CMD_ARM_6DOF_SET_VELOCITY1,
        .arg_count = CAN_ARG_ARM_6DOF_SET_VELOCITY1,
    };

    memcpy(msg.args, (void*)&bus_arm_6dof.required.velocity, 8);
    Queues_SendCANFrame(&msg);

    msg.cmd = CAN_CMD_ARM_6DOF_SET_VELOCITY2;
    msg.arg_count = CAN_ARG_ARM_6DOF_SET_VELOCITY2;

    memcpy(msg.args, (void*)&bus_arm_6dof.required.velocity + 8, 8);
    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Arm6DOF_SetGripper() {
	can_packet_t msg = {
		.cmd = CAN_CMD_ARM_6DOF_SET_GRIPPER,
		.arg_count = CAN_ARG_ARM_6DOF_SET_GRIPPER,
	};

	memcpy(msg.args, &bus_arm_6dof.gripper, CAN_ARG_ARM_6DOF_SET_GRIPPER);

	Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Arm6DOF_SetParams() {
    if (bus_arm_6dof.mode == ARM_6DOF_POSITION_MODE) {
        Cmd_Bus_Arm6DOF_SetPos();
    } else if (bus_arm_6dof.mode == ARM_6DOF_VELOCITY_MODE) {
        Cmd_Bus_Arm6DOF_SetVelocity();
    }

    Cmd_Bus_Arm6DOF_SetGripper();
}

void Cmd_Bus_Arm6DOF_PositioningStart(uint8_t ID) {
    can_packet_t msg = {
            .cmd = CAN_CMD_ARM_6DOF_POSITIONING_START,
            .arg_count = CAN_ARG_ARM_6DOF_POSITIONING_START,
            .args = {ID}
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Arm6DOF_PositioningAbort() {
    can_packet_t msg = {
        .cmd = CAN_CMD_ARM_6DOF_POSITIONING_ABORT,
        .arg_count = CAN_ARG_ARM_6DOF_POSITIONING_ABORT,
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Arm6DOF_SetActualPos(uint8_t ID, uint8_t MSB, uint8_t LSB) {
    can_packet_t msg = {
        .cmd = CAN_CMD_ARM_6DOF_SET_ACTUAL_POS,
        .arg_count = CAN_ARG_ARM_6DOF_SET_ACTUAL_POS,
        .args = {ID, MSB, LSB},
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Arm6DOF_KeyboardClick() {
	can_packet_t msg = {
		.cmd = CAN_CMD_ARM_6DOF_KEYBOARD_CLICK,
		.arg_count = CAN_ARG_ARM_6DOF_KEYBOARD_CLICK
	};

	Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Arm6DOF_SmartKutongToggle() {
    can_packet_t msg = {
        .cmd = CAN_CMD_ARM_6DOF_SMART_KUTONG_TOGGLE,
        .arg_count = CAN_ARG_ARM_6DOF_SMART_KUTONG_TOGGLE,
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Arm6DOF_SoftReset() {
	can_packet_t msg = {
		.cmd = CAN_CMD_ARM_6DOF_SOFT_RESET,
		.arg_count = CAN_ARG_ARM_6DOF_SOFT_RESET,
	};

	Queues_SendCANFrame(&msg);
}
