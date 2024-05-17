#ifndef KALMAN_ELECTRONICS_MASTER_V3_MOBILAB_H
#define KALMAN_ELECTRONICS_MASTER_V3_MOBILAB_H

#include "stdint.h"

/**
 * struktura reprezentujaca pojedynczy modul Mobilaba (moze ich byc wiele na magistrali)
 */
typedef struct {
    uint8_t id;				//!< bajt identyfikacji urzadzenia (okreslany zworkami, 0..3)
    float temperature;		//!< float z temperaturą grzałki
} mobilab_t;

#endif //KALMAN_ELECTRONICS_MASTER_V3_MOBILAB_H
