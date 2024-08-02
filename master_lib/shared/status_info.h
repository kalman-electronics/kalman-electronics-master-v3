/**
* @author Jakub Bubak
* @date 02.08.2024
*/

#pragma once

#include "common.h"

#define STATUS_INFO_TASK_PRIORITY 10
#define STATUS_INFO_TASK_STACK_SIZE 256
extern StaticTask_t StatusInfoTaskBuffer;
extern StackType_t StatusInfoTaskStack[STATUS_INFO_TASK_STACK_SIZE];

void StatusInfo_Task(void *argument);
