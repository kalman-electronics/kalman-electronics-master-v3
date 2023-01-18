#ifndef KALMAN_ELECTRONICS_MASTER_V3_UNIVERSAL_H
#define KALMAN_ELECTRONICS_MASTER_V3_UNIVERSAL_H

#include "stdint.h"

/**
 * struktura reprezentujaca pojedynczy modul Universal Module (moze ich byc wiele na magistrali)
 */
typedef struct {
    uint8_t id;                 //!< bajt identyfikacji urzadzenia (okreslany w inicjalizacji logiki!)

    //dane odbierane cyklicznie z modulu
    int32_t loadcell_value;     //!< aktualna surowa wartosc odczytana z belki tensometrycznej
    uint8_t supply_voltage;     //!< wartosc napiecia zasilania w 0.1V
    uint8_t status;             //!< status kontrolera
} universal_t;

#endif //KALMAN_ELECTRONICS_MASTER_V3_UNIVERSAL_H
