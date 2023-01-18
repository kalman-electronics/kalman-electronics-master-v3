#include "gpio_expander.h"
#include "FreeRTOS.h"
#include "task.h"

//TODO: code copied from HAL v3 project, cleanup this shit

I2C_HandleTypeDef* gpio_hi2c;
uint16_t gpio_reg = 0;
uint16_t led_timeouts[GPIOEXPANDER_CHANNEL_COUNT] = {0};
uint8_t should_update = 0;

void GpioExpander_Write();

void GpioExpander_Init(I2C_HandleTypeDef* hi2c) {
	HAL_I2C_IsDeviceReady(hi2c, GPIOEXPANDER_I2C_ADDR, 10, 100);
	gpio_hi2c = hi2c;

	uint8_t buf[3] = {0};
	buf[0] = 6;

	HAL_I2C_Master_Transmit(hi2c, GPIOEXPANDER_I2C_ADDR, buf, 3, 100);

	buf[0] = 2;
	HAL_I2C_Master_Transmit(hi2c, GPIOEXPANDER_I2C_ADDR, buf, 3, 100);
}

void GpioExpander_Write() {
	if (gpio_hi2c->State != HAL_I2C_STATE_READY)
		return;

	uint8_t buf[3] = {0};
	buf[0] = 2;
	buf[1] = (uint8_t) (~gpio_reg & 0xff);
	buf[2] = (uint8_t) ((~gpio_reg >> 8) & 0xff);

	HAL_I2C_Master_Transmit(gpio_hi2c, GPIOEXPANDER_I2C_ADDR, buf, 3,100);
}

void GpioExpander_SetLed(led_t led, uint8_t state, uint16_t timeout) {
	switch (state) {
		case on:   gpio_reg |=  led; break;
		case off:  gpio_reg &= ~led; break;
		default:   break;
	}

    if (timeout) {
        for (int i = 0; i < GPIOEXPANDER_CHANNEL_COUNT; i++) {
            if ((1 << i) & led)
                led_timeouts[i] = timeout;
        }
    }

    should_update = 1;
}

void GpioExpander_Toggle(led_t led) {
	gpio_reg = ~gpio_reg & led;
}

void GpioExpander_Task() {
    GpioExpander_Init(&hi2c4);

    GpioExpander_SetLed(LED_ALL, off, 0);
    vTaskDelay(500 / portTICK_PERIOD_MS);

    while (1) {
        static TickType_t previous_time = 0;
        TickType_t time_diff = xTaskGetTickCount() / portTICK_PERIOD_MS - previous_time;

        // LED timeout handling
        for (int i = 0; i < GPIOEXPANDER_CHANNEL_COUNT; i++) {
            // Skip check if there is no timeout set
            if (led_timeouts[i] == 0)
                continue;

            // Unset LED
            if (led_timeouts[i] <= time_diff) {
                led_timeouts[i] = 0;
                gpio_reg &= ~(1 << i);

                // Set update flag
                should_update = 1;
            }
            // Reduce remaining timeout
            else {
                led_timeouts[i] -= time_diff;
            }
        }

        // Prevent unnecessary I2C transmissions
        if (should_update) {
            GpioExpander_Write();
            should_update = 0;
        }

        previous_time += time_diff;

        vTaskDelay(5 / portTICK_PERIOD_MS);
    }
}
