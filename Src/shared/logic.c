#include "logic.h"
#include "timers/timer.h"

logic_t logic;

void Logic_Init() {
    logic.link_type = LINK_RF_UART;
    Logic_SetRfDir(1, 1);
}

uint32_t Logic_GetUptime() {
    return xTaskGetTickCount() / portTICK_PERIOD_MS;
}

void Logic_SetRfDir(uint8_t reb, uint8_t de) {
    HAL_GPIO_WritePin(SATEL_REB_GPIO_Port, SATEL_REB_Pin, reb);
    HAL_GPIO_WritePin(SATEL_DE_GPIO_Port, SATEL_DE_Pin, de);
}