#ifndef KALMAN_ELECTRONICS_MASTER_V3_CAN_CMD_H
#define KALMAN_ELECTRONICS_MASTER_V3_CAN_CMD_H

#include "../can_packet.h"
#include "../../shared/common.h"

/*
 *  RX Frames
 */

// --- Common ---
void Cmd_Bus_Common_GetPid(uint8_t *data);

// --- Motor ---
void Cmd_Bus_Motor_GetWheels1(uint8_t *data);
void Cmd_Bus_Motor_GetWheels2(uint8_t *data);
void Cmd_Bus_Motor_GetStatus(uint8_t* data);
void Cmd_Bus_Motor_DebugRx(uint8_t* data);
void Cmd_Bus_Motor_GetTemperature(uint8_t* data);

// --- Arm ---
void Cmd_Bus_Arm_GetPos1(uint8_t* data);
void Cmd_Bus_Arm_GetPos2(uint8_t* data);
void Cmd_Bus_Arm_Get24V(uint8_t* data);
void Cmd_Bus_Arm_GetStatus(uint8_t* data);
void Cmd_Bus_Arm_DebugRx(uint8_t *data);

// --- Arm 6DoF ---
void Cmd_Bus_Arm6DOF_GetPos1(uint8_t *data);
void Cmd_Bus_Arm6DOF_GetPos2(uint8_t *data);
void Cmd_Bus_Arm6DOF_GetGripper(uint8_t *data, uint8_t count);
void Cmd_Bus_Arm6DOF_GetSmartKutongData(uint8_t *data);

// --- Universal ---
void Cmd_Bus_Universal_GetWeight(uint8_t* data);
void Cmd_Bus_Universal_GetStatus(uint8_t* data);
void Cmd_Bus_Universal_DebugRx(uint8_t* data);

// --- Science ---
void Cmd_Bus_Science_GetTemperature1(uint8_t* data);
void Cmd_Bus_Science_GetTemperature2(uint8_t* data);
void Cmd_Bus_Science_GetHumidity(uint8_t* data);
void Cmd_Bus_Science_GetAtmosphere(uint8_t* data);
void Cmd_Bus_Science_GetWeight(uint8_t* data);
void Cmd_Bus_Science_GetStatus(uint8_t* data);
void Cmd_Bus_Science_DebugRx(uint8_t* data);

// --- Mobilab v2 ---
void Cmd_Bus_Mobilab_GetTemperature(uint8_t* data);

// --- Fallback handlers ---
void Cmd_Bus_UnknownHandler(can_packet_t* msg);
void Cmd_Bus_EmptyHandler(uint8_t* msg);

// --- Drill ---
void Cmd_Bus_Drill_GetWeight(uint8_t* data);

/*
 *  TX Frames
 */

// --- Common ---
void Cmd_Bus_Common_ResetAll();
void Cmd_Bus_Common_ResetDevice(can_device_t id);
void Cmd_Bus_Common_SetPid(uint16_t p, uint8_t i, uint8_t d, uint8_t min, uint8_t max, can_device_t id, uint8_t flags);
void Cmd_Bus_Common_GetPidRequest(can_device_t id);

// --- Motor ---
void Cmd_Bus_Motor_SetWheels();
void Cmd_Bus_Motor_Calibrate(uint8_t channel);
void Cmd_Bus_Motor_DebugTx(uint8_t* data);

// --- Arm ---
void Cmd_Bus_Arm_SetPos1();
void Cmd_Bus_Arm_SetPos2();
void Cmd_Bus_Arm_SetMagnet(uint8_t state);
void Cmd_Bus_Arm_Calibrate(uint8_t joint);
void Cmd_Bus_Arm_DebugTx(uint8_t* data);

// --- Arm 6DoF
void Cmd_Bus_Arm6DOF_SetPosVel();
void Cmd_Bus_Arm6DOF_SetTorque();
void Cmd_Bus_Arm6DOF_SetPos();
void Cmd_Bus_Arm6DOF_SetVelocity();
void Cmd_Bus_Arm6DOF_SetGripper();
void Cmd_Bus_Arm6DOF_SetParams();
void Cmd_Bus_Arm6DOF_PositioningStart(uint8_t ID);
void Cmd_Bus_Arm6DOF_PositioningAbort();
void Cmd_Bus_Arm6DOF_KeyboardClick();
void Cmd_Bus_Arm6DOF_SetActualPos(uint8_t ID, uint8_t MSB, uint8_t LSB);
void Cmd_Bus_Arm6DOF_SoftReset();
void Cmd_Bus_Arm6DOF_SmartKutongToggle();
void Cmd_Bus_Arm6DOF_Autoclick_SetPos(uint8_t pos);

// --- Drill ---
void Cmd_Bus_Drill_A_Bridge_Set(uint8_t direction, uint8_t speed);
void Cmd_Bus_Drill_B_Bridge_Set(uint8_t direction, uint8_t speed);
void Cmd_Bus_Drill_GetWeightRequest();

// --- UEUOS v2 ---
void Cmd_Bus_Ueuos_SetState(const uint8_t* data);
void Cmd_Bus_Ueuos_SetColor(const uint8_t* data);
void Cmd_Bus_Ueuos_SetEffect(const uint8_t* data);

// --- Universal ---
void Cmd_Bus_Universal_SetBridge(uint8_t id, uint8_t flags, uint8_t* data);
void Cmd_Bus_Universal_SetServo(uint8_t id, uint8_t flags, uint8_t* data);
void Cmd_Bus_Universal_SetPwm(uint8_t id, uint8_t flags, uint8_t *data);
void Cmd_Bus_Universal_SetGpio(uint8_t id, uint8_t flags1, uint8_t flags2, uint8_t gpio1, uint8_t gpio2);
void Cmd_Bus_Universal_DebugTx(uint8_t* data);

// --- Science ---
void Cmd_Bus_Science_Poll(uint8_t id);
void Cmd_Bus_Science_DebugTx(uint8_t* data);

// --- Mobilab v2 ---
void Cmd_Bus_Mobilab_SetPump(const uint8_t* data);
void Cmd_Bus_Mobilab_SetHeater(const uint8_t* data);
void Cmd_Bus_Mobilab_SetBacklight(const uint8_t* data);
void Cmd_Bus_Mobilab_SetAux(const uint8_t* data);
void Cmd_Bus_Mobilab_SetServo(const uint8_t* data);

// --- Mux --
void Cmd_Bus_Mux_SetChannel(uint8_t vtx, uint8_t channel);
void Cmd_Bus_Mux_SetCam(uint8_t vtx, uint8_t cam);
void Cmd_Bus_Mux_SetPower(uint8_t vtx, uint8_t power);

#endif //KALMAN_ELECTRONICS_MASTER_V3_CAN_CMD_H
