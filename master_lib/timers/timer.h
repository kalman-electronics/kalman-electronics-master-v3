/*
 * In FreeRTOS master all scheduled / reoccurring actions are defined by dedicated
 * FreeRTOS timers. Every action needs to have its callback function and ID defined
 * and be registered in Timer_Init() function.
 */

#ifndef KALMAN_ELECTRONICS_MASTER_V3_TIMER_H
#define KALMAN_ELECTRONICS_MASTER_V3_TIMER_H

#include "FreeRTOS.h"
#include "timers.h"

#define TIMER_COUNT 9

typedef struct {
	TimerHandle_t handle;
	StaticTimer_t buffer;
} timer_t;

#define TIMER_MOTOR_TIMEOUT_TIME 1100
#define TIMER_ARM_TIMEOUT_TIME   500

extern timer_t timer_defs[TIMER_COUNT];

typedef enum {
    TIMER_CAN_TRAFFIC_SET_ARM,
    TIMER_CAN_TRAFFIC_SET_MOTOR,
    TIMER_UART_TRAFFIC_6DOF,
    TIMER_UART_TRAFFIC_MOTOR,
    TIMER_MOTOR_TIMEOUT,
    TIMER_ARM_TIMEOUT,
    TIMER_TCAN,
    TIMER_HEALTH_CHECK,
    TIMER_UART_TRAFFIC_MOTOR_TEMP,
} timer_id;

void Timer_Init(void);
void Timer_Start(void);
void Timer_ResetTimeout(timer_id timer);

// --- Timer callbacks ---

// --- Traffic ---
void Timer_CAN_TrafficSetArm(TimerHandle_t xTimer);
void Timer_CAN_TrafficSetMotor(TimerHandle_t xTimer);
void Timer_UART_Traffic6DoF(TimerHandle_t xTimer);
void Timer_UART_TrafficMotor(TimerHandle_t xTimer);
void Timer_UART_TrafficMotorTemp(TimerHandle_t xTimer);

// --- Timeouts ---
void Timer_MotorTimeout(TimerHandle_t xTimer);
void Timer_ArmTimeout(TimerHandle_t xTimer);

// --- TCAN update ---
void Timer_TCANUpdate(TimerHandle_t xTimer);

// --- Health check ---
void Timer_HealthCheck(TimerHandle_t xTimer);

#endif //KALMAN_ELECTRONICS_MASTER_V3_TIMER_H
