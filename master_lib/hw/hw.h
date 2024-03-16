#ifndef KALMAN_ELECTRONICS_MASTER_V3_HW_H
#define KALMAN_ELECTRONICS_MASTER_V3_HW_H

#include "arm.h"
#include "arm_6dof.h"
#include "motor.h"
#include "science.h"
#include "universal.h"
#include "mobilab.h"

#define BUS_UNIVERSAL_COUNT 1
#define BUS_SCIENCE_COUNT 1
#define BUS_MOBILAB_COUNT 3

extern volatile motor_controller_t bus_motor;
extern volatile arm_controller_t bus_arm;
extern volatile arm_6dof_controller_t bus_arm_6dof;
extern volatile universal_t bus_universal[BUS_UNIVERSAL_COUNT];
extern volatile science_t bus_science[BUS_SCIENCE_COUNT];
extern volatile mobilab_t bus_mobilab[BUS_MOBILAB_COUNT];

void HW_Init();

#endif //KALMAN_ELECTRONICS_MASTER_V3_HW_H
