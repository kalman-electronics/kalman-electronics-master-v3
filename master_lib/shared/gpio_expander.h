#ifndef INC_GPIO_EXPANDER_H_
#define INC_GPIO_EXPANDER_H_

#include "i2c.h"
#include "common.h"

#define GPIOEXPANDER_I2C_ADDR (0b1110100 << 1)
#define GPIOEXPANDER_CHANNEL_COUNT 16
#define on 1
#define off 0

typedef enum {
	LED_BLANK2     = 1 << 0,
	LED_BLANK1     = 1 << 1,
	LED_UNIVERSAL2 = 1 << 2,
	LED_UNIVERSAL1 = 1 << 3,
	LED_RS422      = 1 << 4,
	LED_MUX        = 1 << 5,
	LED_ARM        = 1 << 6,
	LED_MOTOR      = 1 << 7,
	LED_DEBUG_AUX2 = 1 << 8,
	LED_DEBUG_AUX1 = 1 << 9,
	LED_OK         = 1 << 10,
	LED_RF         = 1 << 11,
	LED_AUTO       = 1 << 12,
	LED_DEBUG1     = 1 << 13,
	LED_DEBUG2     = 1 << 14,
	LED_CAN_ERR    = 1 << 15,
	LED_ALL        = 0xffff,
	LED_NONE       = 0
} led_t;

void GpioExpander_Init(I2C_HandleTypeDef* hi2c);
void GpioExpander_SetLed(led_t led, uint8_t state, uint16_t timeout);
void GpioExpander_Toggle(led_t led);
void GpioExpander_Task(void *argument);

#endif /* INC_GPIO_EXPANDER_H_ */
