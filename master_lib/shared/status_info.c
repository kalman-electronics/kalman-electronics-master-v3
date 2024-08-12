/**
* @author Jakub Bubak
* @date 02.08.2024
*/

#include "status_info.h"

StaticTask_t StatusInfoTaskBuffer;
StackType_t StatusInfoTaskStack[STATUS_INFO_TASK_STACK_SIZE];

void StatusInfo_Task(void *argument) {

	while(1) {

		printf("--------------------\n");
		printf("Free heap: %d\n", xPortGetFreeHeapSize());
		printf("Worst free heap: %d\n", xPortGetMinimumEverFreeHeapSize());
		printf("Status info worst free task stack size: %lu\n", uxTaskGetStackHighWaterMark(NULL));
		printf("GPIO Expander worst free task stack size: %lu\n", uxTaskGetStackHighWaterMark(GpioExpanderTaskHandle));
		printf("UART Parser worst free task stack size: %lu\n", uxTaskGetStackHighWaterMark(UARTParserTaskHandle));
		printf("UART Handler worst free task stack size: %lu\n", uxTaskGetStackHighWaterMark(UARTHandlerTaskHandle));
		printf("UART Encoder worst free task stack size: %lu\n", uxTaskGetStackHighWaterMark(UARTEncoderTaskHandle));
		printf("CAN Manager worst free task stack size: %lu\n", uxTaskGetStackHighWaterMark(CANManagerTaskHandle));
		printf("CAN Handler worst free task stack size: %lu\n", uxTaskGetStackHighWaterMark(CANHandlerTaskHandle));
		printf("--------------------\n");


		vTaskDelay(pdMS_TO_TICKS(5000));

	}

}
