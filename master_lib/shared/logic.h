#ifndef SHARED_LOGIC_H_
#define SHARED_LOGIC_H_

#include "common.h"
#include "uart/uart_packet.h"
#include "gpio.h"

#define LOGIC_COMM_START_TIME 2000

typedef struct {
    uart_packet_link_t link_type;
    //status_mode_t status_mode;
} logic_t;

extern logic_t logic;

void Logic_Init();
uint32_t Logic_GetUptime();
void Logic_SetRfDir(uint8_t reb, uint8_t de);

#endif /* SHARED_LOGIC_H_ */
