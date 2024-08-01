/**
* @author Jakub Bubak
* @date 15.03.2024
*/

#include "Program.h"
#include "shared/common.h"
#include "shared/logic.h"
#include "hw/hw.h"
#include "timers/timer.h"

int __io_putchar(int ch) {
	HAL_UART_Transmit(PRINTF_UART_DEF, (uint8_t*)&ch, 1, 0xFFFF);
	return ch;
}


void Init() {
	Queues_Init();
	HW_Init();
	Logic_Init();
	Timer_Init();
}


void ErrorHandler() {

}