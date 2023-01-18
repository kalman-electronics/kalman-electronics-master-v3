#ifndef KALMAN_ELECTRONICS_MASTER_V3_ARM_6DOF_H
#define KALMAN_ELECTRONICS_MASTER_V3_ARM_6DOF_H

typedef enum {
    ARM_6DOF_VELOCITY_MODE,
    ARM_6DOF_POSITION_MODE
} arm_6dof_mode_t;


#include "stdint.h"

typedef struct {
    arm_6dof_mode_t mode;

    // Cmd_Bus_Arm6DOF_SetPos and Cmd_Bus_Arm6DOF_SetVelocity depends
    // on this union being exactly in declared order and 16B long.
    union settings {
        struct {
            int16_t velocity[6];
            uint8_t max_torque;
        } __attribute__((packed)) velocity;

        struct {
            int16_t pos[7]; //!< 0-4 -> 1-5 czlon, 5-6 -> 6. czlon
            uint8_t manip_speed;
            uint8_t torque;
        } __attribute__((packed)) position;
    } required;

    union settings current;

    int16_t gripper;    //!< wartosc wypelnienia do sterowania chwytakiem

    // Smart kutong extension
    struct __attribute__((packed)) {
        uint16_t temperature;
        uint16_t humidity;
    } kutong;
} arm_6dof_controller_t;


#endif //KALMAN_ELECTRONICS_MASTER_V3_ARM_6DOF_H
