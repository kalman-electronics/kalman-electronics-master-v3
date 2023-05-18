#ifndef KALMAN_ELECTRONICS_MASTER_V3_UART_PACKET_DEFS_H
#define KALMAN_ELECTRONICS_MASTER_V3_UART_PACKET_DEFS_H

#include "uart_packet.h"
#include "uart/uart_cmd.h"

#define UART_PACKET_DEFS_LEN (sizeof(uart_packet_defs)/sizeof(uart_packet_def_t))

static uart_packet_def_t uart_packet_defs[] = {
        // --- Common ---
        {
            .cmd = UART_CMD_COMMON_RESET_ALL,
            .arg_count = UART_ARG_COMMON_RESET_ALL,
            .execute = Cmd_UART_Common_ResetAll,
        },
        {
            .cmd = UART_CMD_COMMON_RESET_DEVICE,
            .arg_count = UART_ARG_COMMON_RESET_DEVICE,
            .execute = Cmd_UART_Common_ResetDevice,
        },
        {
            .cmd = UART_CMD_COMMON_SET_PID,
            .arg_count = UART_ARG_COMMON_SET_PID,
            .execute = Cmd_UART_Common_SetPid,
        },
        {
            .cmd = UART_CMD_COMMON_GET_PID_REQUEST,
            .arg_count = UART_ARG_COMMON_GET_PID_REQUEST,
            .execute = Cmd_UART_Common_GetPidRequest,
        },
        {
            .cmd = UART_CMD_COMMON_DEBUG_TX,
            .arg_count = UART_ARG_COMMON_DEBUG_TX,
            .execute = Cmd_UART_Common_DebugTx,
        },

        // --- Master ---
        {
            .cmd = UART_CMD_MASTER_SET_LINK,
            .arg_count = UART_ARG_MASTER_SET_LINK,
            .execute = Cmd_UART_Master_SetLink,
        },
        {
            .cmd = UART_CMD_MASTER_SET_STATUS_MODE,
            .arg_count = UART_ARG_MASTER_SET_STATUS_MODE,
            .execute = Cmd_UART_Master_SetStatusMode,
        },
        {
            .cmd = UART_CMD_MASTER_COMPUTER_POWER_ON,
            .arg_count = UART_ARG_MASTER_COMPUTER_POWER_ON,
            .execute = Cmd_UART_Master_ComputerPowerOn,
        },
        {
            .cmd = UART_CMD_MASTER_COMPUTER_RESET,
            .arg_count = UART_ARG_MASTER_COMPUTER_RESET,
            .execute = Cmd_UART_Master_ComputerReset,
        },
        {
            .cmd = UART_CMD_MASTER_SET_DEBUG_INFO,
            .arg_count = UART_ARG_MASTER_SET_DEBUG_INFO,
            .execute = Cmd_UART_Master_SetDebugInfo,
        },

        // --- Motor ---
        {
            .cmd = UART_CMD_MOTOR_SET_WHEELS,
            .arg_count = UART_ARG_MOTOR_SET_WHEELS,
            .execute = Cmd_UART_Motor_SetWheels,
        },
        {
            .cmd = UART_CMD_MOTOR_CALIBRATE,
            .arg_count = UART_ARG_MOTOR_CALIBRATE,
            .execute = Cmd_UART_Motor_Calibrate,
        },

        // --- Arm ---
        {
            .cmd = UART_CMD_ARM_SET_POS,
            .arg_count = UART_ARG_ARM_SET_POS,
            .execute = Cmd_UART_Arm_SetPos,
        },
        {
            .cmd = UART_CMD_ARM_SET_MAGNET,
            .arg_count = UART_ARG_ARM_SET_MAGNET,
            .execute = Cmd_UART_Arm_SetMagnet,
        },
        {
            .cmd = UART_CMD_ARM_CALIBRATE,
            .arg_count = UART_ARG_ARM_CALIBRATE,
            .execute = Cmd_UART_Arm_Calibrate,
        },
        {
            .cmd = UART_CMD_ARM_GET_VOLTAGE_REQUEST,
            .arg_count = UART_ARG_ARM_GET_VOLTAGE_REQUEST,
            .execute = Cmd_UART_Arm_GetVoltageRequest,
        },

        // --- Arm 6DoF ---
        {
            .cmd = UART_CMD_ARM_6DOF_SET_POS,
            .arg_count = UART_ARG_ARM_6DOF_SET_POS,
            .execute = Cmd_UART_Arm6DOF_SetPos,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_SET_VELOCITY,
            .arg_count = UART_ARG_ARM_6DOF_SET_VELOCITY,
            .execute = Cmd_UART_Arm6DOF_SetVelocity,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_SET_GRIPPER,
            .arg_count = UART_ARG_ARM_6DOF_SET_GRIPPER,
            .execute = Cmd_UART_Arm6DOF_SetGripper,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_GET_POS,
            .arg_count = UART_ARG_ARM_6DOF_GET_POS,
            .execute = Cmd_UART_Arm6DOF_GetPos,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_POSITIONING_START,
            .arg_count = UART_ARG_ARM_6DOF_POSITIONING_START,
            .execute = Cmd_UART_Arm6DOF_PositioningStart,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_POSITIONING_ABORT,
            .arg_count = UART_ARG_ARM_6DOF_POSITIONING_ABORT,
            .execute = Cmd_UART_Arm6DOF_PositioningAbort,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_SET_ACTUAL_POS,
            .arg_count = UART_ARG_ARM_6DOF_SET_ACTUAL_POS,
            .execute = Cmd_UART_Arm6DOF_SetActualPos,
        },
		{
			.cmd = UART_CMD_ARM_6DOF_KEYBOARD_CLICK,
			.arg_count = UART_ARG_ARM_6DOF_KEYBOARD_CLICK,
			.execute = Cmd_UART_Arm6DOF_KeyboardClick,
		},
		{
			.cmd = UART_CMD_ARM_6DOF_SOFT_RESET,
			.arg_count = UART_ARG_ARM_6DOF_SOFT_RESET,
			.execute = Cmd_UART_Arm6DOF_SoftReset,
		},
        {
            .cmd = UART_CMD_ARM_6DOF_GET_PROBE_REQUEST,
            .arg_count = UART_ARG_ARM_6DOF_GET_PROBE_REQUEST,
            .execute = Cmd_UART_Arm6DOF_GetProbeRequest,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_AUTOCLICK_SET_POS,
            .arg_count = UART_ARG_ARM_6DOF_AUTOCLICK_SET_POS,
            .execute = Cmd_UART_Arm6DOF_Autoclick_SetPos,
        },

        // --- UEUOS v2 ---
        {
            .cmd = UART_CMD_UEUOS_SET_STATE,
            .arg_count = UART_ARG_UEUOS_SET_STATE,
            .execute = Cmd_UART_Ueuos_SetState,
        },
        {
            .cmd = UART_CMD_UEUOS_SET_COLOR,
            .arg_count = UART_ARG_UEUOS_SET_COLOR,
            .execute = Cmd_UART_Ueuos_SetColor,
        },
        {
            .cmd = UART_CMD_UEUOS_SET_EFFECT,
            .arg_count = UART_ARG_UEUOS_SET_EFFECT,
            .execute = Cmd_UART_Ueuos_SetEffect,
        },

        // --- Universal ---
        {
            .cmd = UART_CMD_UNIVERSAL_SET_BRIDGE,
            .arg_count = UART_ARG_UNIVERSAL_SET_BRIDGE,
            .execute = Cmd_UART_Universal_SetBridge,
        },
        {
            .cmd = UART_CMD_UNIVERSAL_SET_SERVO,
            .arg_count = UART_ARG_UNIVERSAL_SET_SERVO,
            .execute = Cmd_UART_Universal_SetServo,
        },
        {
            .cmd = UART_CMD_UNIVERSAL_SET_PWM,
            .arg_count = UART_ARG_UNIVERSAL_SET_PWM,
            .execute = Cmd_UART_Universal_SetPwm,
        },
        {
            .cmd = UART_CMD_UNIVERSAL_SET_GPIO,
            .arg_count = UART_ARG_UNIVERSAL_SET_GPIO,
            .execute = Cmd_UART_Universal_SetGpio,
        },
        {
            .cmd = UART_CMD_UNIVERSAL_GET_WEIGHT_REQUEST,
            .arg_count = UART_ARG_UNIVERSAL_GET_WEIGHT_REQUEST,
            .execute = Cmd_UART_Universal_GetWeightRequest,
        },

        // --- Party ---
        {
            .cmd = UART_CMD_PARTY_SET_IGNITERS,
            .arg_count = UART_ARG_PARTY_SET_IGNITERS,
            .execute = Cmd_UART_Party_SetIgniters,
        },
        {
            .cmd = UART_CMD_PARTY_SET_LEDS,
            .arg_count = UART_ARG_PARTY_SET_LEDS,
            .execute = Cmd_UART_Party_SetLeds,
        },
        {
            .cmd = UART_CMD_PARTY_SET_POWER,
            .arg_count = UART_ARG_PARTY_SET_POWER,
            .execute = Cmd_UART_Party_SetPower,
        },
        {
            .cmd = UART_CMD_PARTY_SET_DETECTORS_MODE,
            .arg_count = UART_ARG_PARTY_SET_DETECTORS_MODE,
            .execute = Cmd_UART_Party_SetDetectorsMode,
        },

        // --- Science ---
        {
            .cmd = UART_CMD_SCIENCE_GET_SAMPLES_REQUEST,
            .arg_count = UART_ARG_SCIENCE_GET_SAMPLES_REQUEST,
            .execute = Cmd_UART_Science_GetSamplesRequest,
        },
        {
            .cmd = UART_CMD_SCIENCE_GET_WEIGHT_REQUEST,
            .arg_count = UART_ARG_SCIENCE_GET_WEIGHT_REQUEST,
            .execute = Cmd_UART_Science_GetWeightRequest,
        },
        {
            .cmd = UART_CMD_SCIENCE_GET_ATMOSPHERE_REQUEST,
            .arg_count = UART_ARG_SCIENCE_GET_ATMOSPHERE_REQUEST,
            .execute = Cmd_UART_Science_GetAtmosphereRequest,
        },

        // --- Mobilab v2 ---
        {
            .cmd = UART_CMD_MOBILAB_SET_PUMP,
            .arg_count = UART_ARG_MOBILAB_SET_PUMP,
            .execute = Cmd_UART_Mobilab_SetPump
        },
        {
            .cmd = UART_CMD_MOBILAB_SET_HEATER,
            .arg_count = UART_ARG_MOBILAB_SET_HEATER,
            .execute = Cmd_UART_Mobilab_SetHeater
        },
        {
            .cmd = UART_CMD_MOBILAB_SET_BACKLIGHT,
            .arg_count = UART_ARG_MOBILAB_SET_BACKLIGHT,
            .execute = Cmd_UART_Mobilab_SetBacklight
        },
        {
            .cmd = UART_CMD_MOBILAB_SET_AUX,
            .arg_count = UART_ARG_MOBILAB_SET_AUX,
            .execute = Cmd_UART_Mobilab_SetAux
        },
        {
            .cmd = UART_CMD_MOBILAB_SET_SERVO,
            .arg_count = UART_ARG_MOBILAB_SET_SERVO,
            .execute = Cmd_UART_Mobilab_SetServo
        },

        // --- Mux ---
        {
            .cmd = UART_CMD_MUX_SET_CAM,
            .arg_count = UART_ARG_MUX_SET_CAM,
            .execute = Cmd_UART_Mux_SetCam,
        },
        {
            .cmd = UART_CMD_MUX_SET_CHANNEL,
            .arg_count = UART_ARG_MUX_SET_CHANNEL,
            .execute = Cmd_UART_Mux_SetChannel,
        },
        {
            .cmd = UART_CMD_MUX_SET_POWER,
            .arg_count = UART_ARG_MUX_SET_POWER,
            .execute = Cmd_UART_Mux_SetPower,
        },

        // --- Custom ---
        {
            .cmd = UART_CMD_CUSTOM_TO_RF,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_CustomToRF,
        },
        {
            .cmd = UART_CMD_CUSTOM_TO_UART,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_CustomToUART,
        },
        {
            .cmd = UART_CMD_SUPERVISOR_TO_RF,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_SupervisorToRF,
        },
        {
            .cmd = UART_CMD_SUPERVISOR_TO_UART,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_SupervisorToUART,
        },
};

//TODO: add message traits / fields such as custom_frame or ack_required changing handler behaviour
#define UART_PACKET_IS_CUSTOM(cmd) ((       \
    (cmd == UART_CMD_CUSTOM_TO_RF)       || \
    (cmd == UART_CMD_CUSTOM_TO_UART)     || \
    (cmd == UART_CMD_SUPERVISOR_TO_RF)   || \
    (cmd == UART_CMD_SUPERVISOR_TO_UART)) ? 1 : 0)


#endif //KALMAN_ELECTRONICS_MASTER_V3_UART_PACKET_DEFS_H
