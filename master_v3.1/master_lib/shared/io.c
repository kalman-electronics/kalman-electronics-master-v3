#include "io.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "gpio.h"

void IO_Finish_PC_PowerOn();
void IO_Finish_PC_Reset();

TimerHandle_t IO_PC_PowerOn_TimerHandle;
TimerHandle_t IO_PC_Reset_TimerHandle;

void IO_Timers_Init() {
    IO_PC_PowerOn_TimerHandle = xTimerCreate(
            "IO_PC_PowerOn",
            IO_TIMERS_PC_POWERON_PULSE_DURATION / portTICK_PERIOD_MS,
            pdFALSE,
            0,
            IO_Finish_PC_PowerOn);

    IO_PC_Reset_TimerHandle = xTimerCreate(
            "IO_PC_Reset",
            IO_TIMERS_PC_RESET_PULSE_DURATION / portTICK_PERIOD_MS,
            pdFALSE,
            0,
            IO_Finish_PC_Reset);
}

void IO_Finish_PC_PowerOn() {
    // End pulse
    HAL_GPIO_WritePin(PC_ON_GPIO_Port, PC_ON_Pin, 0);
}

void IO_Finish_PC_Reset() {
    // End pulse
    HAL_GPIO_WritePin(PC_RESET_GPIO_Port, PC_RESET_Pin, 0);
}

void IO_Request_PC_PowerOn() {
    // Start pulse to power on the PC
    HAL_GPIO_WritePin(PC_ON_GPIO_Port, PC_ON_Pin, 1);

    // Schedule end of the pulse
    xTimerStart(IO_PC_PowerOn_TimerHandle, 10 / portTICK_PERIOD_MS);
}

void IO_Request_PC_Reset() {
    // Start pulse to power on the PC
    HAL_GPIO_WritePin(PC_RESET_GPIO_Port, PC_RESET_Pin, 1);

    // Schedule end of the pulse
    xTimerStart(IO_PC_Reset_TimerHandle, 10 / portTICK_PERIOD_MS);
}