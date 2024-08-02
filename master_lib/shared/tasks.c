/**
* @author Jakub Bubak
* @date 01.08.2024
*/

#include "tasks.h"
#include "gpio_expander.h"

#include "uart/handler/uart_parser.h"
#include "uart/handler/uart_packet_handler.h"
#include "uart/handler/uart_encoder.h"

#include "can/handler/can_manager.h"
#include "can/handler/can_packet_handler.h"

#include "status_info.h"

TaskHandle_t GpioExpanderTaskHandle;
TaskHandle_t UARTParserTaskHandle;
TaskHandle_t UARTHandlerTaskHandle;
TaskHandle_t UARTEncoderTaskHandle;
TaskHandle_t CANManagerTaskHandle;
TaskHandle_t CANHandlerTaskHandle;
TaskHandle_t StatusInfoTaskHandle;


void createTasks(void) {
	GpioExpanderTaskHandle = xTaskCreateStatic(
			GpioExpander_Task,
			"GPIO Expander Task",
			GPIO_EXPANDER_TASK_STACK_SIZE,
			NULL,
			GPIO_EXPANDER_TASK_PRIORITY,
			GPIOExpanderTaskStack,
			&GPIOExpanderTaskBuffer
	);

	UARTParserTaskHandle = xTaskCreateStatic(
			UARTParser_Task,
			"UART Parser Task",
			UART_PARSER_TASK_STACK_SIZE,
			NULL,
			UART_PARSER_TASK_PRIORITY,
			UARTParserTaskStack,
			&UARTParserTaskBuffer
	);

	UARTHandlerTaskHandle = xTaskCreateStatic(
			UARTHandler_Task,
			"UART Handler Task",
			UART_HANDLER_TASK_STACK_SIZE,
			NULL,
			UART_HANDLER_TASK_PRIORITY,
			UARTHandlerTaskStack,
			&UARTHandlerTaskBuffer
	);

	UARTEncoderTaskHandle = xTaskCreateStatic(
			UARTEncoder_Task,
			"UART Encoder Task",
			UART_ENCODER_TASK_STACK_SIZE,
			NULL,
			UART_ENCODER_TASK_PRIORITY,
			UARTEncoderTaskStack,
			&UARTEncoderTaskBuffer
	);

	CANManagerTaskHandle = xTaskCreateStatic(
			CANManager_Task,
			"CAN Manager Task",
			CAN_MANAGER_TASK_STACK_SIZE,
			NULL,
			CAN_MANAGER_TASK_PRIORITY,
			CANManagerTaskStack,
			&CANManagerTaskBuffer
	);

	CANHandlerTaskHandle = xTaskCreateStatic(
			CANHandler_Task,
			"CAN Handler Task",
			CAN_HANDLER_TASK_STACK_SIZE,
			NULL,
			CAN_HANDLER_TASK_PRIORITY,
			CANHandlerTaskStack,
			&CANHandlerTaskBuffer
	);

	StatusInfoTaskHandle = xTaskCreateStatic(
			StatusInfo_Task,
			"Status Info Task",
			STATUS_INFO_TASK_STACK_SIZE,
			NULL,
			STATUS_INFO_TASK_PRIORITY,
			StatusInfoTaskStack,
			&StatusInfoTaskBuffer
	);

	configASSERT(GpioExpanderTaskHandle);
	configASSERT(UARTParserTaskHandle);
	configASSERT(UARTHandlerTaskHandle);
	configASSERT(UARTEncoderTaskHandle);
	configASSERT(CANManagerTaskHandle);
	configASSERT(CANHandlerTaskHandle);
	configASSERT(StatusInfoTaskHandle);
}