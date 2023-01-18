#ifndef KALMAN_ELECTRONICS_MASTER_V3_PARTY_H
#define KALMAN_ELECTRONICS_MASTER_V3_PARTY_H

#include "stdint.h"

/**
 * struktura reprezentujaca modul Party Module
 */
typedef struct {
    //dane odbierane cyklicznie z modulu
    uint8_t supply_voltage;     //!< wartosc napiecia zasilania w 0.1V
    uint8_t status;             //!< status kontrolera
    uint8_t detectors[7];       //!< stany detektorow zapalnikow
} party_t;

#endif //KALMAN_ELECTRONICS_MASTER_V3_PARTY_H
