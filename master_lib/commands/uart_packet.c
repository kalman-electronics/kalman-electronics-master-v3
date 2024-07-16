#include "uart_packet.h"

uart_packet_link_t UARTPacket_UARTIDToLink(uint8_t uart_id) {
    // Check if the UART id is valid
    if (!(LINK_UART_ANY & (1 << uart_id))) {
        debug_printf("UARTPacket_UARTIDToLink unknown UART ID, something has gone very wrong\n");
        return LINK_DEBUG_UART;
    }

    // Encode link
    return (uart_packet_link_t)(1 << uart_id);
}
