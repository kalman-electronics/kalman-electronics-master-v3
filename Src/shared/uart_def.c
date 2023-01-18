#include "uart_def.h"

uart_def_t uart_defs[] = {
	{.id = RF_UART_ID,    .uart_handle = &huart1,},
	{.id = AUTO_UART_ID,  .uart_handle = &huart3,},
	{.id = DEBUG_UART_ID, .uart_handle = &huart2,},
};
