#ifndef KALMAN_ELECTRONICS_MASTER_V3_CAN_PACKET_DEFS_H
#define KALMAN_ELECTRONICS_MASTER_V3_CAN_PACKET_DEFS_H

#include "can_packet.h"
#include "can/can_cmd.h"

#define CAN_PACKET_DEFS_LEN (sizeof(can_packet_defs)/sizeof(can_packet_def_t))

// CAN RX packet callback registration
const can_packet_def_t can_packet_defs[] = {
    // --- Common ---
    {
        .cmd = CAN_CMD_GET_PID,
        .arg_count = CAN_ARG_GET_PID,
        .execute = Cmd_Bus_Common_GetPid,
    },

    // --- Motor ---
    {
        .cmd = CAN_CMD_MOTOR_GET_WHEELS1,
        .arg_count = CAN_ARG_MOTOR_GET_WHEELS1,
        .execute = Cmd_Bus_Motor_GetWheels1,
    },
    {
        .cmd = CAN_CMD_MOTOR_GET_WHEELS2,
        .arg_count = CAN_ARG_MOTOR_GET_WHEELS2,
        .execute = Cmd_Bus_Motor_GetWheels2,
    },
    {
        .cmd = CAN_CMD_MOTOR_GET_STATUS,
        .arg_count = CAN_ARG_MOTOR_GET_STATUS,
        .execute = Cmd_Bus_Motor_GetStatus,
    },
    {
        .cmd = CAN_CMD_MOTOR_DEBUG_RX,
        .arg_count = CAN_ARG_MOTOR_DEBUG_RX,
        .execute = Cmd_Bus_Motor_DebugRx,
    },

    // --- Arm ---
    {
        .cmd = CAN_CMD_ARM_GET_POS1,
        .arg_count = CAN_ARG_ARM_GET_POS1,
        .execute = Cmd_Bus_Arm_GetPos1,
    },
    {
        .cmd = CAN_CMD_ARM_GET_POS2,
        .arg_count = CAN_ARG_ARM_GET_POS2,
        .execute = Cmd_Bus_Arm_GetPos2,
    },
    {
        .cmd = CAN_CMD_ARM_GET_24V,
        .arg_count = CAN_ARG_ARM_GET_24V,
        .execute = Cmd_Bus_Arm_Get24V,
    },
    {
        .cmd = CAN_CMD_ARM_GET_STATUS,
        .arg_count = CAN_ARG_ARM_GET_STATUS,
        .execute = Cmd_Bus_Arm_GetStatus,
    },
    {
        .cmd = CAN_CMD_ARM_DEBUG_RX,
        .arg_count = CAN_ARG_ARM_DEBUG_RX,
        .execute = Cmd_Bus_Arm_DebugRx,
    },

    // --- Arm 6DoF ---
    {
        .cmd = CAN_CMD_ARM_6DOF_GET_POS1,
        .arg_count = CAN_ARG_ARM_6DOF_GET_POS1,
        .execute = Cmd_Bus_Arm6DOF_GetPos1,
    },
    {
        .cmd = CAN_CMD_ARM_6DOF_GET_POS2,
        .arg_count = CAN_ARG_ARM_6DOF_GET_POS2,
        .execute = Cmd_Bus_Arm6DOF_GetPos2,
    },

    // --- Universal ---
    {
        .cmd = CAN_CMD_UNIVERSAL_GET_WEIGHT,
        .arg_count = CAN_ARG_UNIVERSAL_GET_WEIGHT,
        .execute = Cmd_Bus_Universal_GetWeight,
    },
    {
        .cmd = CAN_CMD_UNIVERSAL_GET_STATUS,
        .arg_count = CAN_ARG_UNIVERSAL_GET_STATUS,
        .execute = Cmd_Bus_Universal_GetStatus,
    },
    {
        .cmd = CAN_CMD_UNIVERSAL_DEBUG_RX,
        .arg_count = CAN_ARG_UNIVERSAL_DEBUG_RX,
        .execute = Cmd_Bus_Universal_DebugRx,
    },

    // --- Science ---
    {
        .cmd = CAN_CMD_SCIENCE_GET_TEMPERATURE1,
        .arg_count = CAN_ARG_SCIENCE_GET_TEMPERATURE1,
        .execute = Cmd_Bus_Science_GetTemperature1,
    },
    {
        .cmd = CAN_CMD_SCIENCE_GET_TEMPERATURE2,
        .arg_count = CAN_ARG_SCIENCE_GET_TEMPERATURE2,
        .execute = Cmd_Bus_Science_GetTemperature2,
    },
    {
        .cmd = CAN_CMD_SCIENCE_GET_HUMIDITY,
        .arg_count = CAN_ARG_SCIENCE_GET_HUMIDITY,
        .execute = Cmd_Bus_Science_GetHumidity,
    },
    {
        .cmd = CAN_CMD_SCIENCE_GET_ATMOSPHERE,
        .arg_count = CAN_ARG_SCIENCE_GET_ATMOSPHERE,
        .execute = Cmd_Bus_Science_GetAtmosphere,
    },
    {
        .cmd = CAN_CMD_SCIENCE_GET_WEIGHT,
        .arg_count = CAN_ARG_SCIENCE_GET_WEIGHT,
        .execute = Cmd_Bus_Science_GetWeight,
    },
    {
        .cmd = CAN_CMD_SCIENCE_GET_STATUS,
        .arg_count = CAN_ARG_SCIENCE_GET_STATUS,
        .execute = Cmd_Bus_Science_GetStatus,
    },
    {
        .cmd = CAN_CMD_SCIENCE_DEBUG_RX,
        .arg_count = CAN_ARG_SCIENCE_DEBUG_RX,
        .execute = Cmd_Bus_Science_DebugRx,
    },

    // --- Fallback handlers ---
    //TODO: uh, how
    #warning "Frame 0xBE is discarded, because for some reason we receive it"
    {
        .cmd = 190,
        .arg_count = 2,
        .execute = Cmd_Bus_EmptyHandler,
    },
};

#endif //KALMAN_ELECTRONICS_MASTER_V3_CAN_PACKET_DEFS_H
