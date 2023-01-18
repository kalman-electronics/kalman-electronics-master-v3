/*
 * In FreeRTOS master all scheduled / reoccurring actions are defined by dedicated
 * FreeRTOS timers. Every action needs to have its callback function and ID defined
 * and be registered in Timer_Init() function.
 */

#ifndef KALMAN_ELECTRONICS_MASTER_V3_TIMER_H
#define KALMAN_ELECTRONICS_MASTER_V3_TIMER_H

#include "FreeRTOS.h"
#include "timers.h"

#define TIMER_COUNT 8

//TODO: timer struct and dynamic init

extern TimerHandle_t timer_defs[TIMER_COUNT];

typedef enum {
    TIMER_CAN_TRAFFIC_MOTOR_ARM = 0,
    TIMER_UART_TRAFFIC_6DOF     = 1,
    TIMER_UART_TRAFFIC_STATUS   = 2,
    TIMER_UART_TRAFFIC_MOTOR    = 3,
    TIMER_MOTOR_TIMEOUT         = 4,
    TIMER_ARM_TIMEOUT           = 5,
    TIMER_TCAN                  = 6,
    TIMER_HEALTH_CHECK          = 7
} timer_id;

void Timer_Init();
void Timer_Start();
void Timer_ResetTimeout(timer_id timer);

// --- Timer callbacks ---

// --- Traffic ---
void Timer_CAN_TrafficMotorArm();
void Timer_UART_Traffic6DoF();
void Timer_UART_TrafficStatus();
void Timer_UART_TrafficMotor();

// --- Timeouts ---
void Timer_MotorTimeout();
void Timer_ArmTimeout();

// --- TCAN update ---
void Timer_TCANUpdate();

// --- Health check ---
void Timer_HealthCheck();

#endif //KALMAN_ELECTRONICS_MASTER_V3_TIMER_H
