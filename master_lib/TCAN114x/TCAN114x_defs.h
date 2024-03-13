/*
 * TCAN114x_defs.h
 *
 *  Created on: Apr 4, 2022
 *      Author: Michał
 */

#ifndef SRC_CAN_TCAN114X_TCAN114X_TCAN114X_DEFS_H_
#define SRC_CAN_TCAN114X_TCAN114X_TCAN114X_DEFS_H_

// register addresses definitions

#define TCAN114x_DEVICE_ID_y       0x00
#define TCAN114x_REV_ID_MAJOR      0x08
#define TCAN114x_REV_ID_MINOR      0x09
#define TCAN114x_SPI_RSVD_x        0x0a
#define TCAN114x_SCRATCH_PAD_SPI   0x0f
#define TCAN114x_MODE_CNTRL        0x10
#define TCAN114x_WAKE_PIN_CONFIG   0x11
#define TCAN114x_PIN_CONFIG        0x12
#define TCAN114x_WD_CONFIG_1       0x13
#define TCAN114x_WD_CONFIG_2       0x14
#define TCAN114x_WD_INPUT_TRIG     0x15
#define TCAN114x_WD_RST_PULSE      0x16
#define TCAN114x_FSM_CONFIG        0x17
#define TCAN114x_FSM_CNTR          0x18
#define TCAN114x_DEVICE_RST        0x19
#define TCAN114x_DEVICE_CONFIG_1   0x1a
#define TCAN114x_DEVICE_CONFIG_2   0x1b
#define TCAN114x_SWE_DIS           0x1c
#define TCAN114x_SDO_CONFIG        0x29
#define TCAN114x_WD_QA_CONFIG      0x2d
#define TCAN114x_WD_QA_ANSWER      0x2e
#define TCAN114x_WD_QA_QUESTION    0x2f
#define TCAN114x_SW_ID1            0x30  // not for TCAN1144
#define TCAN114x_SW_ID2            0x31  // not for TCAN1144
#define TCAN114x_SW_ID3            0x32  // not for TCAN1144
#define TCAN114x_SW_ID4            0x33  // not for TCAN1144
#define TCAN114x_SW_ID_MASK1       0x34  // not for TCAN1144
#define TCAN114x_SW_ID_MASK2       0x35  // not for TCAN1144
#define TCAN114x_SW_ID_MASK3       0x36  // not for TCAN1144
#define TCAN114x_SW_ID_MASK4       0x37  // not for TCAN1144
#define TCAN114x_SW_ID_MASK_DLC    0x38  // not for TCAN1144
#define TCAN114x_DATA_y            0x39  // not for TCAN1144
#define TCAN114x_SW_RSVD_y         0x41  // not for TCAN1144
#define TCAN114x_SW_CONFIG_1       0x44  // not for TCAN1144
#define TCAN114x_SW_CONFIG_2       0x45  // not for TCAN1144
#define TCAN114x_SW_CONFIG_3       0x46  // not for TCAN1144
#define TCAN114x_SW_CONFIG_4       0x47  // not for TCAN1144
#define TCAN114x_SW_CONFIG_RSVD_y  0x48  // not for TCAN1144
#define TCAN114x_INT_GLOBAL        0x50
#define TCAN114x_INT_1             0x51
#define TCAN114x_INT_2             0x52
#define TCAN114x_INT_3             0x53
#define TCAN114x_INT_CANBUS        0x54
#define TCAN114x_INT_GLOBAL_ENABLE 0x55
#define TCAN114x_INT_ENABLE_1      0x56
#define TCAN114x_INT_ENABLE_2      0x57
#define TCAN114x_INT_ENABLE_3      0x58
#define TCAN114x_INT_ENABLE_CANBUS 0x59
#define TCAN114x_INT_RSVD_y        0x5a


//interrupt masks

#define TCAN114x_INT1_WD          (1 << 7)
#define TCAN114x_INT1_CANINT      (1 << 6)
#define TCAN114x_INT1_LWU         (1 << 5)
#define TCAN114x_INT1_WKERR       (1 << 4)
#define TCAN114x_INT1_FRAME_OVF   (1 << 3)
#define TCAN114x_INT1_CANSLNT     (1 << 2)
#define TCAN114x_INT1_CANTO       (1 << 1)
#define TCAN114x_INT1_CANDOM      (1 << 0)

#define TCAN114x_INT2_SMS         (1 << 7)
#define TCAN114x_INT2_PWRON       (1 << 6)
#define TCAN114x_INT2_RSVD        (1 << 5)
#define TCAN114x_INT2_UVSUP       (1 << 4)
#define TCAN114x_INT2_UVIO_OVF    (1 << 3)
#define TCAN114x_INT2_UVCC        (1 << 2)
#define TCAN114x_INT2_TSD         (1 << 1)
#define TCAN114x_INT2_TSDW        (1 << 0)

#define TCAN114x_INT3_SPIERR      (1 << 7)
#define TCAN114x_INT3_SWERR       (1 << 6)
#define TCAN114x_INT3_FSM         (1 << 5)
#define TCAN114x_INT3_CRC_EEPROM  (1 << 0)

#define TCAN114x_INTC_CANBUSTERMOPEN   (1 << 6)
#define TCAN114x_INTC_CANHCANL         (1 << 5)
#define TCAN114x_INTC_CANHBAT          (1 << 4)
#define TCAN114x_INTC_CANLGND          (1 << 3)
#define TCAN114x_INTC_CANBUSOPEN       (1 << 2)
#define TCAN114x_INTC_CANBUSGND        (1 << 1)
#define TCAN114x_INTC_CANBUSBAT        (1 << 0)

#define TCAN114x_INT1_GLOBAL_INT    (1 << 6)
#define TCAN114x_INT2_GLOBAL_INT    (1 << 5)
#define TCAN114x_INT3_GLOBAL_INT    (1 << 4)
#define TCAN114x_INTC_GLOBAL_INT    (1 << 3)

// intertupt enable masks
#define TCAN114x_INT1_WD_ENABLE  (1 << 7)
#define TCAN114x_INT1_CANINT_ENABLE  (1 << 6)
#define TCAN114x_INT1_LWU_ENABLE  (1 << 5)
#define TCAN114x_INT1_WKERR_ENABLE  (1 << 4)
#define TCAN114x_INT1_FRAME_OVF_ENABLE  (1 << 3)
#define TCAN114x_INT1_CANSLNT_ENABLE  (1 << 2)
#define TCAN114x_INT1_CANTO_ENABLE  (1 << 1)
#define TCAN114x_INT1_CANDOM_ENABLE  (1 << 0)

#define TCAN114x_INT2_UVSUP_ENABLE  (1 << 4)
#define TCAN114x_INT2_UVIO_ENABLE  (1 << 3)
#define TCAN114x_INT2_UVCC_ENABLE  (1 << 2)
#define TCAN114x_INT2_TSD_ENABLE  (1 << 1)
#define TCAN114x_INT2_TSDW_ENABLE  (1 << 0)

#define TCAN114x_INT3_SPIERR_ENABLE  (1 << 7)
#define TCAN114x_INT3_SWERR_ENABLE  (1 << 6)
#define TCAN114x_INT3_FSM_ENABLE  (1 << 5)

#define TCAN114x_INTC_CANBUSTERMOPEN_ENABLE  (1 << 6)
#define TCAN114x_INTC_CANHCANL_ENABLE  (1 << 5)
#define TCAN114x_INTC_CANHBAT_ENABLE  (1 << 4)
#define TCAN114x_INTC_CANLGND_ENABLE  (1 << 3)
#define TCAN114x_INTC_CANBUSOPEN_ENABLE  (1 << 2)
#define TCAN114x_INTC_CANBUSGND_ENABLE  (1 << 1)
#define TCAN114x_INTC_CANBUSBAT_ENABLE  (1 << 0)

// reset masks
#define TCAN114x_HARD_RESET (1 << 0)
#define TCAN114x_SOFT_RESET (1 << 1)

// HW dependent struct, contains info about SPI interface
typedef struct
{
	SPI_HandleTypeDef* spiHandle;
	GPIO_TypeDef* nCSHandle;
	uint16_t nCS;
}TCAN114x_SPI;

typedef struct
{
	uint8_t int_1;
	uint8_t int_2;
	uint8_t int_3;
	uint8_t int_canbus;
}TCAN114x_interrupts;

typedef enum
{
	sleep = 0x01,
	standby = 0x04,
	listen = 0x05,
	normal = 0x07,
}TCAN114x_Mode;

typedef struct
{
	uint8_t type[8];
	uint8_t majorRev;
	uint8_t minorRev;
}TCAN114x_ID;

#endif /* SRC_CAN_TCAN114X_TCAN114X_TCAN114X_DEFS_H_ */
