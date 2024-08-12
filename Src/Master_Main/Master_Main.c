/**
* @author Jakub Bubak
* @date 15.03.2024
*/

#include "Master_Main.h"
#include "shared/common.h"
#include "shared/logic.h"
#include "hw/hw.h"
#include "timers/timer.h"

// Redirect printf to debug UART
int __io_putchar(int ch) {
	if (ch == '\n') {
		uint8_t ch2 = '\r';
		HAL_UART_Transmit(uart_defs[DEBUG_UART_ID].uart_handle, &ch2, 1, HAL_MAX_DELAY);
	}

	HAL_UART_Transmit(uart_defs[DEBUG_UART_ID].uart_handle, (uint8_t *) &ch, 1, HAL_MAX_DELAY);
	return 1;
}

void Init() {
	Queues_Init();
	HW_Init();
	Logic_Init();
	Timer_Init();
}


void ErrorHandler() {

}