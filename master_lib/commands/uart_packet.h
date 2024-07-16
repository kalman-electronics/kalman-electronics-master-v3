#ifndef KALMAN_ELECTRONICS_MASTER_V3_UART_PACKET_H
#define KALMAN_ELECTRONICS_MASTER_V3_UART_PACKET_H

#include "stdint.h"
#include "config.h"

typedef enum {
    // Packets coming from UART parsers
    LINK_RF_UART    = 1 << RF_UART_ID,
    LINK_AUTO_UART  = 1 << AUTO_UART_ID,
    LINK_DEBUG_UART = 1 << DEBUG_UART_ID,
    LINK_RS422_UART = 1 << RS422_UART_ID,
    LINK_UART_ANY   = LINK_RF_UART | LINK_AUTO_UART | LINK_DEBUG_UART | LINK_RS422_UART,

    // Packet was generated / received by the CAN bus and forwarded to UART handler
    LINK_CAN        = 1 << 7,
} uart_packet_link_t;

typedef enum {
    //komendy wspolne dla modulow systemu elektroniki
    UART_CMD_COMMON_RESET_ALL                = 0x00,     //!< [TX]
    UART_CMD_COMMON_RESET_DEVICE             = 0x01,     //!< [TX]
    UART_CMD_COMMON_SET_PID                  = 0x02,     //!< [TX]
    UART_CMD_COMMON_GET_PID_REQUEST          = 0x03,     //!< [TX]
    UART_CMD_COMMON_DEBUG_TX                 = 0x04,     //!< [TX]
    UART_CMD_COMMON_GET_PID                  = 0x1E,     //!< [RX]
    UART_CMD_COMMON_DEBUG_RX                 = 0x1F,     //!< [RX]

    //komendy dodatkowe modulu Master v2
    UART_CMD_MASTER_SET_LINK                 = 0x20,     //!< [TX]
    UART_CMD_MASTER_SET_STATUS_MODE          = 0x21,     //!< [TX]
    UART_CMD_MASTER_SET_VIDEO_CHANNEL        = 0x22,     //!< [TX]
    UART_CMD_MASTER_COMPUTER_POWER_ON        = 0x23,     //!< [TX]
    UART_CMD_MASTER_COMPUTER_RESET           = 0x24,     //!< [TX]
    UART_CMD_MASTER_RASPBERRY_RESET          = 0x25,     //!< [TX]
    UART_CMD_MASTER_SET_DEBUG_INFO           = 0x26,     //!< [TX]
    UART_CMD_MASTER_SET_INDICATOR            = 0x27,     //!< [TX]
    UART_CMD_MASTER_SET_PTZ_MOVE             = 0x28,     //!< [TX]
    UART_CMD_MASTER_SET_LINK_RESPONSE        = 0x3D,     //!< [RX]
    UART_CMD_MASTER_GET_BASIC_STATUS         = 0x3E,     //!< [RX]
    UART_CMD_MASTER_GET_DETAILED_STATUS      = 0x3F,     //!< [RX]

    //Motor Controller v2
    UART_CMD_MOTOR_SET_WHEELS                = 0x40,     //!< [TX]
    UART_CMD_MOTOR_CALIBRATE                 = 0x41,     //!< [TX]
    UART_CMD_MOTOR_GET_WHEELS                = 0x4F,     //!< [RX]
    UART_CMD_MOTOR_GET_TEMPERATURE           = 0x42,     //!< [RX]

    // Drill
    UART_CMD_DRILL_A_BRIDGE_SET              = 0x45,     //!< [TX]
    UART_CMD_DRILL_B_BRIDGE_SET              = 0x46,     //!< [TX]
    UART_CMD_DRILL_C_BRIDGE_SET              = 0x47,     //!< [TX]
    UART_CMD_DRILL_GET_WEIGHT                = 0x48,     //!< [TX]
    UART_CMD_DRILL_SEND_WEIGHT               = 0x49,     //!< [TX]

    //Universal Module v2

    UART_CMD_UNIVERSAL_SET_DIGITAL_OUTPUT = 0x50,
    UART_CMD_UNIVERSAL_SET_PWM_OUTPUT = 0x51,
    UART_CMD_UNIVERSAL_SET_LED_DRIVER = 0x52,
    UART_CMD_UNIVERSAL_SET_HBRIDGE = 0x53,
    UART_CMD_UNIVERSAL_SET_STEPPER_POSITION = 0x54,
    UART_CMD_UNIVERSAL_SET_RESPONSE = 0x55,
    UART_CMD_UNIVERSAL_STEPPER_HOMING_REQUEST = 0x56,
    UART_CMD_UNIVERSAL_WEIGHT_REQUEST = 0x57,
    UART_CMD_UNIVERSAL_INPUT_REQUEST = 0x58,
    UART_CMD_UNIVERSAL_STEPPER_POSITION_REQUEST  = 0x59,
    UART_CMD_UNIVERSAL_WEIGHT_RESPONSE = 0x5A,
    UART_CMD_UNIVERSAL_INPUT_RESPONSE = 0x5B,
    UART_CMD_UNIVERSAL_STEPPER_POSITION_RESPONSE = 0x5C,
    UART_CMD_UNIVERSAL_AUTOMATION_SEQUENCE_BEGIN_REQUEST = 0x5D,
    UART_CMD_UNIVERSAL_AUTOMATION_SEQUENCE_STATE_REQUEST = 0x5E,
    UART_CMD_UNIVERSAL_AUTOMATION_SEQUENCE_STATE_RESPONSE = 0x5F,

    //UEUOS v2
    UART_CMD_UEUOS_SET_STATE                 = 0x60,     //!< [TX]
    UART_CMD_UEUOS_SET_COLOR                 = 0x61,     //!< [TX]
    UART_CMD_UEUOS_SET_EFFECT                = 0x62,     //!< [TX]

    //Universal Module

    UART_CMD_UNIVERSAL_SET_BRIDGE            = 0x70,     //!< [TX]
    UART_CMD_UNIVERSAL_SET_SERVO             = 0x71,     //!< [TX]
    UART_CMD_UNIVERSAL_SET_PWM               = 0x72,     //!< [TX]
    UART_CMD_UNIVERSAL_SET_GPIO              = 0x73,     //!< [TX]
    UART_CMD_UNIVERSAL_GET_WEIGHT_REQUEST    = 0x74,     //!< [TX]
    UART_CMD_UNIVERSAL_GET_WEIGHT            = 0x8F,     //!< [RX]

    //Sajens Module
    UART_CMD_SCIENCE_GET_SAMPLES_REQUEST     = 0xA0,     //!< [TX]
    UART_CMD_SCIENCE_GET_WEIGHT_REQUEST      = 0xA1,     //!< [TX]
    UART_CMD_SCIENCE_GET_ATMOSPHERE_REQUEST  = 0xA2,     //!< [TX]
    UART_CMD_SCIENCE_GET_ATMOSPHERE          = 0xAD,     //!< [RX]
    UART_CMD_SCIENCE_GET_WEIGHT              = 0xAE,     //!< [RX]
    UART_CMD_SCIENCE_GET_SAMPLES             = 0xAF,     //!< [RX]

    //Mobilab v2
    UART_CMD_MOBILAB_SET_PUMP				= 0xC0, 	//!< [TX]
    UART_CMD_MOBILAB_SET_HEATER				= 0xC1,		//!< [TX]
    UART_CMD_MOBILAB_SET_BACKLIGHT			= 0xC2,		//!< [TX]
    UART_CMD_MOBILAB_SET_AUX				= 0xC3,		//!< [TX]
    UART_CMD_MOBILAB_SET_SERVO				= 0xC4,		//!< [TX]
    UART_CMD_MOBILAB_GET_TEMPERATURE		= 0xC5,		//!< [RX]

    //6dof arm
    UART_CMD_ARM_6DOF_SET_POS                = 0xE0,     //!< [TX]
    UART_CMD_ARM_6DOF_SET_POS_VEL            = 0xE4,     //!< [TX]
    UART_CMD_ARM_6DOF_SET_VELOCITY           = 0xE1,     //!< [TX]
    UART_CMD_ARM_6DOF_SET_TORQUE             = 0xE5,     //!< [TX]
    UART_CMD_ARM_6DOF_SET_GRIPPER            = 0xE2,     //!< [TX]
    UART_CMD_ARM_6DOF_GET_POS                = 0xF3,     //!< [RX]
    UART_CMD_ARM_6DOF_AUTOCLICK_SET_POS      = 0xE3,
    UART_CMD_ARM_6DOF_POSITIONING_START      = 0xF4,     //!< [TX]
    UART_CMD_ARM_6DOF_POSITIONING_ABORT      = 0xF5,     //!< [TX]
    UART_CMD_ARM_6DOF_SET_ACTUAL_POS         = 0xF6,     //!< [TX]
	UART_CMD_ARM_6DOF_GET_GRIPPER            = 0xFB,     //!< [RX]
	UART_CMD_ARM_6DOF_KEYBOARD_CLICK         = 0xF9,     //!< [TX]
	UART_CMD_ARM_6DOF_SOFT_RESET             = 0xFA,     //!< [TX]
    UART_CMD_ARM_6DOF_GET_PROBE              = 0xFC,     //!< [RX]
    UART_CMD_ARM_6DOF_GET_PROBE_REQUEST      = 0xFD,     //!< [TX]
	UART_CMD_ARM_6DOF_GET_PROBE_ESP			 = 0xFE,


    //analog visiom mux
    UART_CMD_MUX_SET_CAM                     = 0xB1,     //!< [TX]
    UART_CMD_MUX_SET_CHANNEL                 = 0xB2,     //!< [TX]
    UART_CMD_MUX_SET_POWER                   = 0xB3,     //!< [TX]

    //rpi cm4
    UART_CMD_ARM_CM4                         = 0xB4,

    //rf switch
    UART_CMD_SILENT_MODE                     = 0xB5,



    UART_CMD_CUSTOM_TO_UART                  = 0x80,     //!< [TX, RX]
    UART_CMD_CUSTOM_TO_RF                    = 0x81,     //!< [TX, RX]
    UART_CMD_SUPERVISOR_TO_UART              = 0x82,     //!< [TX, RX]
    UART_CMD_SUPERVISOR_TO_RF                = 0x83,     //!< [TX, RX]
    UART_CMD_RF_TO_ESP32                     = 0x84,     //!< [TX, RX]
    UART_CMD_ESP32_TO_RF                     = 0x85,     //!< [TX, RX]
    UART_CMD_CUSTOM_ARM_TO_UART              = 0x86,
    UART_CMD_CUSTOM_ARM_TO_RF                = 0x87
} uart_cmd_t;

/**
 * ilosc argumentow komend komunikacji 433/WiFi/Auto
 */
typedef enum {
    //komendy wspolne dla modulow systemu elektroniki
    UART_ARG_COMMON_RESET_ALL                = 0,
    UART_ARG_COMMON_RESET_DEVICE             = 1,
    UART_ARG_COMMON_SET_PID                  = 8,
    UART_ARG_COMMON_GET_PID_REQUEST          = 1,
    UART_ARG_COMMON_DEBUG_TX                 = 9,
    UART_ARG_COMMON_GET_PID                  = 8,
    UART_ARG_COMMON_DEBUG_RX                 = 9,

    //komendy dodatkowe modulu Master v2
    UART_ARG_MASTER_SET_LINK                 = 1,
    UART_ARG_MASTER_SET_STATUS_MODE          = 1,
    UART_ARG_MASTER_SET_VIDEO_CHANNEL        = 1,
    UART_ARG_MASTER_COMPUTER_POWER_ON        = 0,
    UART_ARG_MASTER_COMPUTER_RESET           = 0,
    UART_ARG_MASTER_RASPBERRY_RESET          = 0,
    UART_ARG_MASTER_SET_DEBUG_INFO           = 1,
    UART_ARG_MASTER_SET_INDICATOR            = 1,
    UART_ARG_MASTER_SET_PTZ_MOVE             = 4,
    UART_ARG_MASTER_SET_LINK_RESPONSE        = 1,
    UART_ARG_MASTER_GET_BASIC_STATUS         = 8,
    UART_ARG_MASTER_GET_DETAILED_STATUS      = 15,

    //Motor Controller v2
    UART_ARG_MOTOR_SET_WHEELS                = 8,
    UART_ARG_MOTOR_CALIBRATE                 = 6,
    UART_ARG_MOTOR_GET_WHEELS                = 12,
    UART_ARG_MOTOR_GET_TEMPERATURE           = 8,

    // Drill
    UART_ARG_DRILL_A_BRIDE_SET              = 2,
    UART_ARG_DRILL_B_BRIDE_SET              = 2,
	UART_ARG_DRILL_C_BRIDE_SET              = 2,
    UART_ARG_DRILL_GET_WEIGHT               = 0,
    UART_ARG_DRILL_SEND_WEIGHT              = 4,

    //Ueuos v2
    UART_ARG_UEUOS_SET_STATE                 = 1,
    UART_ARG_UEUOS_SET_COLOR                 = 3,
    UART_ARG_UEUOS_SET_EFFECT                = 1,

    //Universal Module v2

    UART_ARG_UNIVERSAL_SET_DIGITAL_OUTPUT = 3,
    UART_ARG_UNIVERSAL_SET_PWM_OUTPUT = 3,
    UART_ARG_UNIVERSAL_SET_LED_DRIVER = 5,
    UART_ARG_UNIVERSAL_SET_HBRIDGE = 4,
    UART_ARG_UNIVERSAL_SET_STEPPER_POSITION = 6,
    UART_ARG_UNIVERSAL_SET_RESPONSE = 8,
    UART_ARG_UNIVERSAL_STEPPER_HOMING_REQUEST = 2,
    UART_ARG_UNIVERSAL_WEIGHT_REQUEST = 2,
    UART_ARG_UNIVERSAL_INPUT_REQUEST  = 2,
    UART_ARG_UNIVERSAL_STEPPER_POSITION_REQUEST = 2,
    UART_ARG_UNIVERSAL_WEIGHT_RESPONSE = 6,
    UART_ARG_UNIVERSAL_INPUT_RESPONSE = 4,
    UART_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE = 6,
    UART_ARG_UNIVERSAL_AUTOMATION_SEQUENCE_BEGIN_REQUEST = 2,
    UART_ARG_UNIVERSAL_AUTOMATION_SEQUENCE_STATE_REQUEST = 2,
    UART_ARG_UNIVERSAL_AUTOMATION_SEQUENCE_STATE_RESPONSE = 4,


    //Universal Module
    UART_ARG_UNIVERSAL_SET_BRIDGE            = 6,
    UART_ARG_UNIVERSAL_SET_SERVO             = 6,
    UART_ARG_UNIVERSAL_SET_PWM               = 8,
    UART_ARG_UNIVERSAL_SET_GPIO              = 5,
    UART_ARG_UNIVERSAL_GET_WEIGHT_REQUEST    = 1,
    UART_ARG_UNIVERSAL_GET_WEIGHT            = 6,

    //Sajens Module
    UART_ARG_SCIENCE_GET_SAMPLES_REQUEST     = 1,
    UART_ARG_SCIENCE_GET_WEIGHT_REQUEST      = 1,
    UART_ARG_SCIENCE_GET_ATMOSPHERE_REQUEST  = 1,
    UART_ARG_SCIENCE_GET_ATMOSPHERE          = 8,
    UART_ARG_SCIENCE_GET_WEIGHT              = 6,
    UART_ARG_SCIENCE_GET_SAMPLES             = 5,

    //Mobilab v2
    UART_ARG_MOBILAB_SET_PUMP				= 2,
    UART_ARG_MOBILAB_SET_HEATER				= 2,
    UART_ARG_MOBILAB_SET_BACKLIGHT			= 2,
    UART_ARG_MOBILAB_SET_AUX				= 2,
    UART_ARG_MOBILAB_SET_SERVO				= 2,
    UART_ARG_MOBILAB_GET_TEMPERATURE		= 5,

    // Arm 6 DOF
    UART_ARG_ARM_6DOF_SET_POS              = 16,
    UART_ARG_ARM_6DOF_SET_POS_VEL          = 12,
    UART_ARG_ARM_6DOF_SET_TORQUE           = 12,
    UART_ARG_ARM_6DOF_SET_VELOCITY         = 13,
    UART_ARG_ARM_6DOF_SET_GRIPPER          = 2,
    UART_ARG_ARM_6DOF_GET_POS              = 14,
    UART_ARG_ARM_6DOF_AUTOCLICK_SET_POS    = 1,
    UART_ARG_ARM_6DOF_POSITIONING_START    = 1,
    UART_ARG_ARM_6DOF_POSITIONING_ABORT    = 0,
    UART_ARG_ARM_6DOF_SET_ACTUAL_POS       = 3,
	UART_ARG_ARM_6DOF_GET_GRIPPER          = 2,
	UART_ARG_ARM_6DOF_KEYBOARD_CLICK       = 0,
	UART_ARG_ARM_6DOF_SOFT_RESET           = 0,
    UART_ARG_ARM_6DOF_GET_PROBE_REQUEST    = 0,
    UART_ARG_ARM_6DOF_GET_PROBE            = 4,
	UART_ARG_ARM_6DOF_GET_PROBE_ESP		   = 4,


    //analog visiom mux
    UART_ARG_MUX_SET_CAM                = 2,
    UART_ARG_MUX_SET_CHANNEL            = 2,
    UART_ARG_MUX_SET_POWER              = 2,

    //rpi cm4
    UART_ARG_ARM_CM4                 = 6,

    //rf switch
    UART_ARG_SILENT_MODE = 1,



    // Custom commands
    UART_ARG_MAX        = 255,
} uart_args_t;

typedef struct {
    uart_cmd_t cmd;
    uart_packet_link_t origin;
    uint8_t arg_count;
    uint8_t args[255];
} uart_packet_t;

typedef struct {
    uint8_t cmd;
    uint8_t arg_count;
    void (*execute)(uint8_t* args, uart_packet_link_t link);
} uart_packet_def_t;

//uint8_t UARTPacket_LinkToUARTID(uart_packet_link_t link);
uart_packet_link_t UARTPacket_UARTIDToLink(uint8_t uart_id);

#endif //KALMAN_ELECTRONICS_MASTER_V3_UART_PACKET_H
