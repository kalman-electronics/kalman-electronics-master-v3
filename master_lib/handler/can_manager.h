#ifndef KALMAN_ELECTRONICS_MASTER_V3_CAN_MANAGER_H
#define KALMAN_ELECTRONICS_MASTER_V3_CAN_MANAGER_H

#include "fdcan.h"
#include "../commands/can_packet.h"
#include "shared/common.h"
#include "spi.h"
#include "gpio.h"

#define CANMANAGER_ACCEPT_ALL_FRAMES 0

// --- CAN Filters
//przyklad: filtr ramek Motor Controllera przepusci odebrana ramke tylko wtedy, gdy jej kod komendy zamaskowany wartoscia 0xF0 da wartosc 0x10

#define CAN_FILTER_MASK                 0xF0
#define CAN_FILTER_ID_COMMON            0x30
#define CAN_FILTER_ID_MOTOR             0x10
#define CAN_FILTER_ID_ARM               0x20
#define CAN_FILTER_ID_DEBUG             0x70
#define CAN_FILTER_ID_PARTY             0x50
#define CAN_FILTER_ID_UEUOS             0x60
#define CAN_FILTER_ID_UNIVERSAL         0x80
#define CAN_FILTER_ID_SCIENCE           0x90
#define CAN_FILTER_ID_MUX               0xA0
#define CAN_FILTER_ID_6DOF              0xB0
#define CAN_FILTER_ID_MOBILAB           0xC0

#define CANLIB_RX_LIST_COUNT            10

void CanManager_Task();

#endif //KALMAN_ELECTRONICS_MASTER_V3_CAN_MANAGER_H
