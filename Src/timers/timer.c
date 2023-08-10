#include "timer.h"
#include "shared/common.h"
#include "shared/logic.h"
#include "commands/can/can_cmd.h"
#include "commands/uart/uart_cmd.h"
#include "spi.h"
#include "gpio.h"

TimerHandle_t timer_defs[TIMER_COUNT];

void Timer_Init() {
    timer_defs[TIMER_CAN_TRAFFIC_SET_ARM] = xTimerCreate(
            "CAN_TrafficSetArm",
            50 / portTICK_PERIOD_MS,
            pdTRUE,
            0,
            Timer_CAN_TrafficSetArm);

    timer_defs[TIMER_CAN_TRAFFIC_SET_MOTOR] = xTimerCreate(
            "CAN_TrafficSetMotor",
            150 / portTICK_PERIOD_MS,
            pdTRUE,
            0,
            Timer_CAN_TrafficSetMotor);

    timer_defs[TIMER_UART_TRAFFIC_6DOF] = xTimerCreate(
            "CAN_Traffic6DoF",
            50 / portTICK_PERIOD_MS,
            pdTRUE,
            0,
            Timer_UART_Traffic6DoF);

    timer_defs[TIMER_UART_TRAFFIC_STATUS] = xTimerCreate(
            "UART_TrafficStatus",
            100 / portTICK_PERIOD_MS,
            pdTRUE,
            0,
            Timer_UART_TrafficStatus);

    timer_defs[TIMER_UART_TRAFFIC_MOTOR] = xTimerCreate(
            "UART_TrafficMotor",
            500 / portTICK_PERIOD_MS,
            pdTRUE,
            0,
            Timer_UART_TrafficMotor);

    timer_defs[TIMER_UART_TRAFFIC_MOTOR_TEMP] = xTimerCreate(
            "UART_TrafficMotorTemp",
            2000 / portTICK_PERIOD_MS,
            pdTRUE,
            0,
            Timer_UART_TrafficMotorTemp);

    timer_defs[TIMER_UART_TRAFFIC_MOBILAB] = xTimerCreate(
            "UART_TrafficMobilab",
            1000 / portTICK_PERIOD_MS,
            pdTRUE,
            0,
            Timer_UART_TrafficMobilab);

    // --- Timeouts ---

    timer_defs[TIMER_MOTOR_TIMEOUT] = xTimerCreate(
            "Timeout_Motor",
            TIMER_MOTOR_TIMEOUT_TIME / portTICK_PERIOD_MS,
            pdFALSE,
            0,
            Timer_MotorTimeout);

    timer_defs[TIMER_ARM_TIMEOUT] = xTimerCreate(
            "Timeout_Arm",
            TIMER_ARM_TIMEOUT_TIME / portTICK_PERIOD_MS,
            pdFALSE,
            0,
            Timer_ArmTimeout);

    // --- TCAN ---
    HAL_GPIO_WritePin(TCAN_CS_GPIO_Port, TCAN_CS_Pin, GPIO_PIN_SET);
    TCAN114x_Init(&tcan, &hspi3, TCAN_CS_GPIO_Port, TCAN_CS_Pin);
    TCAN114x_getDeviceID(&tcan);
    TCAN114x_setMode(&tcan, normal);

    timer_defs[TIMER_TCAN] = xTimerCreate(
            "TCAN_Update",
            1000 / portTICK_PERIOD_MS,
            pdTRUE,
            0,
            Timer_TCANUpdate);

    // --- Health check ---
    timer_defs[TIMER_HEALTH_CHECK] = xTimerCreate(
            "HealthCheck",
            1000 / portTICK_PERIOD_MS,
            pdTRUE,
            0,
            Timer_HealthCheck);

    Timer_Start();
}

void Timer_Start() {
    // Start all timers
    for (int i = 0; i < TIMER_COUNT; i++) {
        configASSERT(xTimerStart(timer_defs[i], portMAX_DELAY));
    }
}

void Timer_ResetTimeout(timer_id timer) {
    //TODO: timer validation
    TimerHandle_t t_handle = timer_defs[timer];

    // Reset timer timeout
    if (xTimerIsTimerActive(t_handle)) {
        xTimerReset(timer_defs[timer], portMAX_DELAY);
    }
    else { // Timeout has already fired, restart timer
        xTimerStart(t_handle, portMAX_DELAY);
    }
}

// --- Timer callbacks ---

// --- Traffic ---

void Timer_CAN_TrafficSetArm() {
    if (Logic_GetUptime() < LOGIC_COMM_START_TIME)
        return;

    #warning Old arm support disabled
    //TODO: W A R N I N G - DISABLED OLD ARM TRAFFIC, add a way to select which one is being used
    //Cmd_Bus_Arm_SetPos1();
    //Cmd_Bus_Arm_SetPos2();
    Cmd_Bus_Arm6DOF_SetParams();
}

void Timer_CAN_TrafficSetMotor() {
    if (Logic_GetUptime() < LOGIC_COMM_START_TIME)
        return;

    Cmd_Bus_Motor_SetWheels();
}

void Timer_UART_Traffic6DoF() {
    Cmd_UART_Arm6DOF_GetPos(NULL, logic.link_type);
    Cmd_UART_Arm6DOF_GetGripper();
}

void Timer_UART_TrafficStatus() {

}

void Timer_UART_TrafficMotor() {
    Cmd_UART_Motor_GetWheels();
}

void Timer_UART_TrafficMotorTemp() {
    Cmd_UART_Motor_GetTemperature();
}

void Timer_UART_TrafficMobilab(){
    Cmd_UART_Mobilab_GetTemperature(0);
    Cmd_UART_Mobilab_GetTemperature(1);
    Cmd_UART_Mobilab_GetTemperature(2);
}

// --- Timeouts ---

void Timer_MotorTimeout() {
    #if TIMER_COMM_TIMEOUT_BYPASS == 0
    debug_printf("[COMM] Przekroczono czas oczekiwania na cykliczna ramke Motor Controllera - zatrzymanie silnikow.\r\n");
    for (uint8_t i=0; i<4; i++) {
        bus_motor.required_angle[i] = bus_motor.current_angle[i];
        bus_motor.required_speed[i] = 0;
    }
    #else
        #warning Motor timeout bypassed
    #endif
}

//TODO: stop 6dof
void Timer_ArmTimeout() {
    #if TIMER_COMM_TIMEOUT_BYPASS == 0
    debug_printf("[COMM] Przekroczono czas oczekiwania na cykliczna ramke Arm Controllera - zatrzymanie silnikow.\r\n");
    // for (uint8_t i=0; i<6; i++) {
    //     bus_arm.required_pos[i] = bus_arm.current_pos[i];
    // }

    // Switch 6DoF to velocity mode and hold in last state to prevent collision
    bus_arm_6dof.mode = ARM_6DOF_VELOCITY_MODE;
    
    for (uint8_t i=0; i<6; i++) {
        bus_arm_6dof.required.velocity.velocity[i] = 0;
        bus_arm_6dof.required.velocity.max_torque = 100;

    }

    #else
        #warning Motor timeout bypassed
    #endif
}

// --- TCAN ---

void Timer_TCANUpdate() {
    // Read and clear CAN interrupts
    TCAN114x_getInterrupts(&tcan);
    TCAN114x_clearInterrupts(&tcan);
    TCAN114x_getMode(&tcan);

    // reset TCAN after error condition
    if(tcan.mode != normal)
        TCAN114x_setMode(&tcan, normal);

    //TODO: process CAN IT / call CAN Manager notify error function
}

// --- Health check ---

void Timer_HealthCheck() {
    // Toggle LED
    GpioExpander_SetLed(LED_OK, on, 500);

    // Report FreeRTOS memory usage
    //debug_printf("Free: %0.2fKB / Worst: %0.2f\n", xPortGetFreeHeapSize() / 1024.f, xPortGetMinimumEverFreeHeapSize() / 1024.f);
}
