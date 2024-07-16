#include "uart_cmd.h"

void Cmd_UART_BlinkLed(uart_packet_link_t link) {
    switch (link) {
        case    LINK_RF_UART: GpioExpander_SetLed(LED_RF, on, 20); break;
        case LINK_DEBUG_UART: GpioExpander_SetLed(LED_AUTO, on, 20); break;
        case  LINK_AUTO_UART: GpioExpander_SetLed(LED_AUTO, on, 20); break;
        case LINK_RS422_UART: GpioExpander_SetLed(LED_RS422, on, 20); break;
        default: break;
    }
}

//TODO: fix this clusterfuck
void Cmd_UART_UnknownHandler(uart_packet_t* msg) {
    debug_printf("\t[AUX  ] Nieobsluzona komenda komunikacji (link = ");

	if (msg->origin == LINK_RF_UART) {
		debug_printf("RF");
	} else {
		debug_printf("Auto");
	}

	debug_printf("; cmd=%d; data = ", msg->cmd);
    for (uint8_t i = 0; i < msg->arg_count; i++) {
        debug_printf("%2x", msg->args[i]);
    }
    debug_printf(")\r\n");

    Cmd_UART_BlinkLed(msg->origin);
}
