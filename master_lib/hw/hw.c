#include <string.h>
#include "hw.h"

volatile motor_controller_t bus_motor;
volatile arm_6dof_controller_t bus_arm_6dof;
volatile science_t bus_science[BUS_SCIENCE_COUNT];
volatile mobilab_t bus_mobilab[BUS_MOBILAB_COUNT];

void HW_Init() {
	// Science init
    bus_science[0].id = 0;

    // 6-DoF init
    memset((void*)&bus_arm_6dof, 0, sizeof(bus_arm_6dof));
    bus_arm_6dof.mode = ARM_6DOF_VELOCITY_MODE;
    bus_arm_6dof.gripper = 500;

    //mobilab v2 init
    for (int i = 0; i < BUS_MOBILAB_COUNT; i++)
        bus_mobilab[i].id = i;
}
