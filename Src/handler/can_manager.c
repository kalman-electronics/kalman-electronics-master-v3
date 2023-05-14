#include "can_manager.h"

uint32_t can_status = 0;

// --- CAN Filters

const uint8_t canlib_rx_list[CANLIB_RX_LIST_COUNT] = {
        CAN_FILTER_ID_COMMON,   //! obowiazkowe dla kazdego modulu!
        CAN_FILTER_ID_MOTOR,
        CAN_FILTER_ID_ARM,
        CAN_FILTER_ID_PARTY,
        CAN_FILTER_ID_UNIVERSAL,
        CAN_FILTER_ID_SCIENCE,
        CAN_FILTER_ID_MUX,
        CAN_FILTER_ID_6DOF,
        CAN_FILTER_ID_MOBILAB,
        CAN_FILTER_ID_UEUOS
};

void CanManager_FilterConfig();

void CanManager_Task() {
    HAL_FDCAN_Start(&hfdcan1);

    // setup notifications
    HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_LIST_RX_FIFO0, 0);
    HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_LIST_TX_FIFO_ERROR, 0);
    HAL_FDCAN_ActivateNotification(&hfdcan1, FDCAN_IT_LIST_PROTOCOL_ERROR, 0);

    //TCAN_114x initialization
    //TODO: TCAN init here
    //HAL_GPIO_WritePin(TCAN_CS_GPIO_Port, TCAN_CS_Pin, GPIO_PIN_SET);
    //TCAN114x_Init(&tcan, &hspi3, TCAN_CS_GPIO_Port, TCAN_CS_Pin);  // pass communication periphs to hw proxy struct
    //TCAN114x_getDeviceID(&tcan);  // get device id, for debug
    //TCAN114x_setMode(&tcan, normal);  // set normal mode, for normal transceiver operation

    CanManager_FilterConfig();

    /*
    FDCAN_TxHeaderTypeDef canHead;
    uint8_t data[] = {0, 0};

    canHead.Identifier = CAN_CMD_MUX_SET_POWER; // CAN_CMD_MUX_SET_CAM
    canHead.IdType = FDCAN_STANDARD_ID;
    canHead.TxFrameType = FDCAN_DATA_FRAME;
    canHead.DataLength = CAN_CMD_MUX_SET_POWER << 16; // CAN_ARG_MUX_SET_CAM
    canHead.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
    canHead.BitRateSwitch = FDCAN_BRS_OFF;
    canHead.FDFormat = FDCAN_CLASSIC_CAN;
    canHead.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
    canHead.MessageMarker = 0;

    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &canHead, data);
    */

    while (1) {
        can_packet_t msg;
        xQueueReceive(can_handler_outgoing_packet_queue, &msg, portMAX_DELAY);

        // Create tx packet info header
        FDCAN_TxHeaderTypeDef can_header;
        can_header.Identifier = msg.cmd;
        can_header.IdType = FDCAN_STANDARD_ID;
        can_header.TxFrameType = FDCAN_DATA_FRAME; // Master never sends a CAN remote frame
        can_header.DataLength = msg.arg_count << 16;
        can_header.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
        can_header.BitRateSwitch = FDCAN_BRS_OFF;
        can_header.FDFormat = FDCAN_CLASSIC_CAN;   // Using CAN 2.0 for now
        can_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
        can_header.MessageMarker = 0;

        // Wait for space in CAN TX FIFO
        while(!HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1)) {
        	vTaskDelay(1 / portTICK_PERIOD_MS);
        }

        // Add the packet to be sent from the TX FIFO
        HAL_StatusTypeDef res = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &can_header, msg.args);
        if (res != HAL_OK) {
        	//GpioExpander_SetLed(LED_CAN_ERR, on, 50); //TODO: can err led is not working
        }
    }
}

void CanManager_FilterConfig() {
    FDCAN_FilterTypeDef filter;

#if CANMANAGER_ACCEPT_ALL_FRAMES == 1
    //filtr akceptujący wszystkie otrzymane ramki
	filter.IdType = FDCAN_STANDARD_ID;
	filter.FilterIndex = 0;
	filter.FilterType = FDCAN_FILTER_RANGE;
	filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	filter.FilterID1 = 0x000;
	filter.FilterID2 = 0x7FF;
	HAL_FDCAN_ConfigFilter(&hfdcan1, &filter);

#else
    //inicjalizacja filtrów akceptujących ramki ze zdefiniowanych modułów
    //TODO: use range/dual filter type
    for (uint8_t filter_number = 0; filter_number < CANLIB_RX_LIST_COUNT; filter_number++) {
        filter.IdType = FDCAN_STANDARD_ID;
        filter.FilterIndex = filter_number;
        filter.FilterType = FDCAN_FILTER_MASK;
        filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
        filter.FilterID1 = canlib_rx_list[filter_number];
        filter.FilterID2 = CAN_FILTER_MASK;
        HAL_FDCAN_ConfigFilter(&hfdcan1, &filter);
    }
#endif
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) {
    FDCAN_RxHeaderTypeDef header;
    can_packet_t msg;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &header, msg.args);
    //TODO: error state indicator support

    msg.cmd = header.Identifier;
	msg.arg_count = header.DataLength >> 16;

    //TODO: timeouts
    xQueueSendFromISR(can_handler_incoming_packet_queue, &msg, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


void HAL_FDCAN_TxFifoEmptyCallback(FDCAN_HandleTypeDef *hfdcan) {

}

void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan) {
    can_status = HAL_FDCAN_GetError(hfdcan);

    GpioExpander_SetLed(LED_CAN_ERR, on, 100);

    switch (can_status) {
        case HAL_FDCAN_ERROR_NONE:
            break;

        case HAL_FDCAN_ERROR_TIMEOUT:
            break;

        case HAL_FDCAN_ERROR_NOT_INITIALIZED:
            break;

        case HAL_FDCAN_ERROR_NOT_READY:
            break;

        case HAL_FDCAN_ERROR_NOT_STARTED:
            break;

        case HAL_FDCAN_ERROR_NOT_SUPPORTED:
            break;

        case HAL_FDCAN_ERROR_PARAM:
            break;

        case HAL_FDCAN_ERROR_PENDING:
            break;

        case HAL_FDCAN_ERROR_RAM_ACCESS:
            break;

        case HAL_FDCAN_ERROR_FIFO_EMPTY:
            break;

        case HAL_FDCAN_ERROR_FIFO_FULL:
            break;

        case HAL_FDCAN_ERROR_LOG_OVERFLOW:
            break;

        case HAL_FDCAN_ERROR_RAM_WDG:
            break;

        case HAL_FDCAN_ERROR_PROTOCOL_ARBT:
            break;

        case HAL_FDCAN_ERROR_PROTOCOL_DATA:
            break;

        case HAL_FDCAN_ERROR_RESERVED_AREA:
            break;
    }

}
void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs) {
    GpioExpander_SetLed(LED_CAN_ERR, on, 100);
}
