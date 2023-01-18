#ifndef KALMAN_ELECTRONICS_MASTER_V3_SCIENCE_H
#define KALMAN_ELECTRONICS_MASTER_V3_SCIENCE_H

#include "stdint.h"

/**
 * struktura reprezentujaca pojedynczy modul Science Module (moze ich byc wiele na magistrali)
 */
typedef struct {
    uint8_t id;                         //!< bajt identyfikacji urzadzenia (okreslany zworkami, 0..3)

    //dane odbierane cyklicznie z modulu
    uint16_t sample_temperature[4];     //!< wartosci temperatur mierzonych probek (jednostka 0.1*C, zakres 0..1000)
    uint8_t sample_humidity[4];         //!< wartosci wilgotnosci mierzonych probek (jednostka 1%, zakres 0..100)
    int32_t loadcell_raw[4];            //!< surowe wartosci odczytane z belek tensometrycznych
    uint16_t air_temperature;           //!< wartosc temperatury powietrza (jednostka 0.1*C, zakres 0..1000)
    uint8_t air_humidity;               //!< wartosc wilgotnosci powietrza (jednostka 1%, zakres 0..100)
    uint32_t air_pressure;              //!< wartosc cisnienia atmosferycznego (jednostka 1Pa, zakres 0..110000)
    uint8_t status;                     //!< status kontrolera
} science_t;

#endif //KALMAN_ELECTRONICS_MASTER_V3_SCIENCE_H
