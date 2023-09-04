#ifndef KALMAN_ELECTRONICS_MASTER_V3_UART_CMD_H
#define KALMAN_ELECTRONICS_MASTER_V3_UART_CMD_H

#include "commands/uart_packet.h"
#include "shared/common.h"
#include "shared/logic.h"
#include "hw/hw.h"
#include "timers/timer.h"
#include "shared/io.h"

/*
 *  RX Frames
 */

// --- Common ---
void Cmd_UART_Common_ResetAll(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Common_ResetDevice(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Common_SetPid(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Common_GetPidRequest(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Common_DebugTx(uint8_t* data, uart_packet_link_t link);

// --- Master ---
void Cmd_UART_Master_SetLink(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Master_SetStatusMode(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Master_SetVideoChannel(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Master_ComputerPowerOn(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Master_ComputerReset(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Master_RaspberryReset(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Master_SetDebugInfo(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Master_SetIndicator(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Master_SetPtzMove(uint8_t* data, uart_packet_link_t link);

// --- Motor ---
void Cmd_UART_Motor_SetWheels(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Motor_Calibrate(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Motor_GetTemperature(void);

// --- Arm ---
void Cmd_UART_Arm_SetPos(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm_SetMagnet(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm_Calibrate(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm_GetVoltageRequest(uint8_t* data, uart_packet_link_t link);

// --- Arm 6DoF ---
void Cmd_UART_Arm6DOF_SetPos(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm6DOF_SetPosVel(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm6DOF_SetTorque(uint8_t *data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_SetVelocity(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm6DOF_SetGripper(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm6DOF_GetPos(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm6DOF_Autoclick_SetPos(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm6DOF_PositioningStart(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm6DOF_PositioningAbort(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm6DOF_SetActualPos(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Arm6DOF_KeyboardClick(uint8_t *data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_SoftReset(uint8_t *data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_GetProbeRequest(uint8_t* data, uart_packet_link_t link_type);

// --- Drill ---
void Cmd_UART_Drill_A_Bridge_Set(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Drill_B_Bridge_Set(uint8_t* data, uart_packet_link_t link_type);

// --- UEUOS v2 ---
void Cmd_UART_Ueuos_SetState(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Ueuos_SetColor(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Ueuos_SetEffect(uint8_t *data, uart_packet_link_t link_type);

// --- Universal ---
void Cmd_UART_Universal_SetBridge(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Universal_SetServo(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Universal_SetPwm(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Universal_SetGpio(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Universal_GetWeightRequest(uint8_t* data, uart_packet_link_t link);

// --- Party ---
void Cmd_UART_Party_SetIgniters(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Party_SetLeds(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Party_SetPower(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Party_SetDetectorsMode(uint8_t* data, uart_packet_link_t link);

// --- Science ---
void Cmd_UART_Science_GetSamplesRequest(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Science_GetWeightRequest(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Science_GetAtmosphereRequest(uint8_t* data, uart_packet_link_t link);

// --- Mobilab v2 ---
void Cmd_UART_Mobilab_SetPump(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Mobilab_SetHeater(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Mobilab_SetBacklight(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Mobilab_SetAux(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Mobilab_SetServo(uint8_t* data, uart_packet_link_t link);

// --- Mux ---
void Cmd_UART_Mux_SetCam(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Mux_SetChannel(uint8_t* data, uart_packet_link_t link);
void Cmd_UART_Mux_SetPower(uint8_t* data, uart_packet_link_t link);

// --- Custom ---
void Cmd_UART_CustomToRF(uint8_t* data, uint8_t len);
void Cmd_UART_CustomToUART(uint8_t* data, uint8_t len);
void Cmd_UART_SupervisorToRF(uint8_t* data, uint8_t len);
void Cmd_UART_SupervisorToUART(uint8_t* data, uint8_t len);
void Cmd_UART_ESP32_To_RF(uint8_t* data, uint8_t len);
void Cmd_UART_RF_To_ESP32(uint8_t* data, uint8_t len);

// --- Unknown ---
void Cmd_UART_UnknownHandler(uart_packet_t* msg);

/*
 *  TX Frames
 */

// --- Common ---
void Cmd_UART_Common_GetPid(uint16_t p, uint8_t i, uint8_t d, uint8_t min, uint8_t max, can_device_t id, uint8_t flags);
void Cmd_UART_Common_DebugRx(uint8_t *data, can_device_t id);

// --- Master ---
void Cmd_UART_Master_SetLinkResponse(uart_packet_link_t new_link);
void Cmd_UART_Master_GetBasicStatus(void);
void Cmd_UART_Master_GetDetailedStatus(void);

// --- Motor ---
void Cmd_UART_Motor_GetWheels(void);

// --- Arm ---
void Cmd_UART_Arm_GetPos(void);
void Cmd_UART_Arm_GetVoltage(uart_packet_link_t link);

// --- Arm 6DoF ---
//TODO: change name
void Cmd_UART_Arm6DOF_GetPos_helper(uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_GetGripper();

// --- Universal ---
void Cmd_UART_Universal_GetWeight(uint8_t id, uint8_t loadcell_index);

// --- Party ---
void Cmd_UART_Party_GetDetectors(void);

// --- Science ---
void Cmd_UART_Science_GetAtmosphere(uint8_t id);
void Cmd_UART_Science_GetWeight(uint8_t id, uint8_t loadcell_index);
void Cmd_UART_Science_GetSamples(uint8_t id, uint8_t sample_index);

// --- Mobilab v2 ---
void Cmd_UART_Mobilab_GetTemperature(uint8_t id);

/*
 *  Helpers
 */

void Cmd_UART_BlinkLed(uart_packet_link_t link);

#endif //KALMAN_ELECTRONICS_MASTER_V3_UART_CMD_H
