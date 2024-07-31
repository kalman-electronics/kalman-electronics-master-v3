/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "handler/uart_parser.h"
#include "handler/uart_encoder.h"
#include "handler/uart_packet_handler.h"
#include "handler/can_manager.h"
#include "handler/can_packet_handler.h"
#include "shared/gpio_expander.h"
#include "shared/common.h"
#include "stdio.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

// Task handles
TaskHandle_t UARTParser_TaskHandle;

/* USER CODE END Variables */
/* Definitions for idleTask */
osThreadId_t idleTaskHandle;
const osThreadAttr_t idleTask_attributes = {
  .name = "idleTask",
  .priority = (osPriority_t) osPriorityLow,
  .stack_size = 128 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartIdleTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(TaskHandle_t xTask, signed char *pcTaskName)
{
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
void StatusTask() {
	while (1) {
		debug_printf("Queue backlog RX: %d TX: %d\n", (int)uxQueueMessagesWaiting(uart_handler_incoming_packet_queue), (int)uxQueueMessagesWaiting(uart_handler_outgoing_packet_queue));
		debug_printf("Parser  [0] head: %d tail: %d\n", parser_defs[0].rx_parser_buf_head, parser_defs[0].rx_parser_buf_tail);
		debug_printf("Encoder [0] head: %d tail: %d\n", encoder_defs[0].tx_dma_buf_head, encoder_defs[0].tx_dma_buf_tail);

		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}

void vApplicationMallocFailedHook(void)
{
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of idleTask */
  idleTaskHandle = osThreadNew(StartIdleTask, NULL, &idleTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
    configASSERT(xTaskCreate(CanManager_Task,  "CAN_Manager",  512, NULL, 9,  NULL));
    configASSERT(xTaskCreate(CANHandler_Task,  "CAN_Handler",  256, NULL, 10, NULL));
    configASSERT(xTaskCreate(UARTParser_Task,  "UART_Parser",  1024, NULL, 6,  &UARTParser_TaskHandle));
    configASSERT(xTaskCreate(UARTEncoder_Task, "UART_Encoder", 1024, NULL, 8,  NULL));
    configASSERT(xTaskCreate(UARTHandler_Task, "UART_Handler", 512, NULL, 7,  NULL));
    configASSERT(xTaskCreate(GpioExpander_Task, "GpioExpander", 128, NULL, 5,  NULL));
    //configASSERT(xTaskCreate(StatusTask,       "status", 512, NULL, 5,  NULL));
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartIdleTask */
/**
  * @brief  Function implementing the idleTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartIdleTask */
void StartIdleTask(void *argument)
{
  /* USER CODE BEGIN StartIdleTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartIdleTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

