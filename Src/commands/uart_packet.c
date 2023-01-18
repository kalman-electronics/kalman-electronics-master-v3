#include "uart_packet.h"

/*
uint8_t UARTPacket_LinkToUARTID(uart_packet_link_t link) {
    // Mask UARTs
    link &= LINK_UART_ANY;

    // Check if link is valid
    //TODO: error reporting / fault
    if(!link)
        while(1);

    // Decode UART id
    uint8_t uart_id = 0;
    while(!(link & (1 << uart_id)))
        uart_id++;

    return uart_id;
}*/

uart_packet_link_t UARTPacket_UARTIDToLink(uint8_t uart_id) {
    // Check if the UART id is valid
    //TODO: error reporting / fault
    if (uart_id > UART_DEFS_COUNT)
        while(1);

    // Encode link
    return (uart_packet_link_t)(1 << uart_id);
}
