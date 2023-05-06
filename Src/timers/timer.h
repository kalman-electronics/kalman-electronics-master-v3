/*
 * In FreeRTOS master all scheduled / reoccurring actions are defined by dedicated
 * FreeRTOS timers. Every action needs to have its callback function and ID defined
 * and be registered in Timer_Init() function.
 */

#ifndef KALMAN_ELECTRONICS_MASTER_V3_TIMER_H
#define KALMAN_ELECTRONICS_MASTER_V3_TIMER_H

#include "FreeRTOS.h"
#include "timers.h"

#define TIMER_COUNT 11

//TODO: timer struct and dynamic init

extern TimerHandle_t timer_defs[TIMER_COUNT];

typedef enum {
    TIMER_CAN_TRAFFIC_SET_ARM,
    TIMER_CAN_TRAFFIC_SET_MOTOR,
    TIMER_UART_TRAFFIC_6DOF,
    TIMER_UART_TRAFFIC_STATUS,
    TIMER_UART_TRAFFIC_MOTOR,
    TIMER_MOTOR_TIMEOUT,
    TIMER_ARM_TIMEOUT,
    TIMER_TCAN,
    TIMER_HEALTH_CHECK,
    TIMER_UART_TRAFFIC_MOBILAB,
    TIMER_UART_TRAFFIC_MOTOR_TEMP,
} timer_id;

void Timer_Init();
void Timer_Start();
void Timer_ResetTimeout(timer_id timer);

// --- Timer callbacks ---

// --- Traffic ---
void Timer_CAN_TrafficSetArm();
void Timer_CAN_TrafficSetMotor();
void Timer_UART_Traffic6DoF();
void Timer_UART_TrafficStatus();
void Timer_UART_TrafficMotor();
void Timer_UART_TrafficMotorTemp();
void Timer_UART_TrafficMobilab();

// --- Timeouts ---
void Timer_MotorTimeout();
void Timer_ArmTimeout();

// --- TCAN update ---
void Timer_TCANUpdate();

// --- Health check ---
void Timer_HealthCheck();

#endif //KALMAN_ELECTRONICS_MASTER_V3_TIMER_H
