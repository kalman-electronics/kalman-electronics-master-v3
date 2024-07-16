/*
 * TCAN114x_config.h
 *
 *  Created on: Apr 6, 2022
 *      Author: Michał
 */

#ifndef SRC_CAN_TCAN114X_TCAN114X_TCAN114X_CONFIG_H_
#define SRC_CAN_TCAN114X_TCAN114X_TCAN114X_CONFIG_H_

/*mode config*/
#define TCAN114x_SELECTIVE_WAKE_EN          0
#define TCAN114x_DOMINANT_TIME_OUT_DISABLE  0
#define TCAN114x_CAN_FAULT_DETECTION        1

/*fail safe mode config*/ //TODO obsluzyc to
#define TCAN114x_FAIL_SAFE_DISABLE         0
#define TCAN114x_FAIL_SAFE_COUNTER_EN      0
#define TCAN114x_FAIL_SAFE_COUNTER_ACTION  0x00


/*interrupt config*/
#define TCAN114x_WATCHDOG_INT_ENABLE                    1
#define TCAN114x_CAN_BUS_WK_INT_ENABLE                  1
#define TCAN114x_LOCAL_WAKEUP_INT_ENABLE                1
#define TCAN114x_WAKEUP_ERR_INT_ENABLE                  1
#define TCAN114x_FRAME_ERR_COUNTER_OVERFLOW_INT_ENABLE  1
#define TCAN114x_CAN_SILENCE_INT_ENABLE                 1
#define TCAN114x_CAN_SILENCE_SW_SM_INT_ENABLE           1
#define TCAN114x_CAN_STUCK_DOM_INT_ENABLE               1

#define TCAN114x_VSUP_UNDER_VOL_INT_ENABLE              1
#define TCAN114x_VIO_UNDER_VOL_ENABLE                   1
#define TCAN114x_VCC_UNDER_VOL_ENABLE                   1
#define TCAN114x_THERMAL_SHUTDOWN_INT_ENABLE            1
#define TCAN114x_THERMAL_SHUTDOWN_WARNING_INT_ENABLE    1

#define TCAN114x_SPI_ERR_INT_ENABLE                     1
#define TCAN114x_SELECTIVE_WAKE_ERR_INT_ENABLE          1
#define TCAN114x_FAIL_SAVE_MODE_INT_ENABL               1

#define TCAN114x_CAN_TERM_OPEN_INT_ENABLE               1
#define TCAN114x_CAN_H_L_SHORT_INT_ENABLE               1
#define TCAN114x_CAN_H_SHORTED_VBAT_INT_ENABLE          1
#define TCAN114x_CAN_L_SHORTED_GND_INT_ENABLE           1
#define TCAN114x_CAN_BUS_OPEN_INT_ENABLE                1
#define TCAN114x_CAN_BUS_SHORTED_GND_INT_ENABLE         1
#define TCAN114x_CAN_BUS_SHORTED_VBAT_INT_ENABLE        1


#endif /* SRC_CAN_TCAN114X_TCAN114X_TCAN114X_CONFIG_H_ */
