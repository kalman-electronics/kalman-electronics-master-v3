#ifndef KALMAN_ELECTRONICS_MASTER_V3_ARM_H
#define KALMAN_ELECTRONICS_MASTER_V3_ARM_H

#include "stdint.h"

/**
 * statusy kontrolera ramienia
 */
typedef enum {
    arm_status_ok = 0,              //!< status domyslny
    arm_status_ocp = (1<<0),        //!< flaga wystapienia zabezpieczenia nadpradowego
    arm_status_uvp = (1<<1),        //!< flaga obnizenia napiecia wejsciowego ponizej wartosci progowej
    arm_status_gnc = (1<<2),        //!< flaga nieskalibrowanego chwytaka (ustawiana po resecie kontrolera), kasowana po kalibracji
} arm_status_t;

/**
 * struktura reprezentujaca modul Arm Controller v2
 */
typedef struct {
    //dane wysylane cyklicznie do modulu
    int16_t required_pos[6];    //!< zadane pozycje kolejnych czlonow, wartosci: 0.1 stopnia (lub 0.1mm dla silownikow) od krancowki MIN

    //dane odbierane cyklicznie od modulu
    int16_t current_pos[6];     //!< aktualne pozycje kolejnych czlonow (wartosci jak wyzej)
    int16_t measured_voltage;   //!< aktualna wartosc napiecia na sondzie +-24V (w mV)
    uint8_t supply_voltage;     //!< aktualna wartosc napiecia zasilania czesci mocy (w 0.1V)
    uint16_t limit_status;      //!< stany krancowek czlonow
    uint8_t motor_status;       //!< status silnikow czlonow
    arm_status_t status;        //!< status kontrolera
} arm_controller_t;

#endif //KALMAN_ELECTRONICS_MASTER_V3_ARM_H
