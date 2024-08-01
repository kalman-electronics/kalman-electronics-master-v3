#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"
#include "uart/commands/uart_cmd.h"

//TODO: rename

/*
 *  RX Frames
 */

/**
 * Odczytanie aktualnej prędkości obrotu kół. Po 2 bajty na koło, kodowanie U2, wartość: prędkość kątowa w 0.1 stopnia na sekundę (np. -23 = jazda do tyłu z prędkością 2.3 stopni/s).
 * Ze względu na redundantną magistralę RS485, Master musi wiedzieć, kiedy transmisja z kontrolerem się zatrzymała - z tego względu ramka GET_WHEELS1 jest wysyłana w odpowiedzi
 * na ramkę SET_WHEELS, a nie cyklicznie.
 *
 * Nie aktualne ^
 *
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
 */
void Cmd_Bus_Motor_GetWheels1(uint8_t* data) {
    for (uint8_t ch=0; ch<4; ch++) {
        bus_motor.current_speed[ch] += (int16_t)((data[2*ch] << 8) + data[2*ch+1]);
    }

    GpioExpander_SetLed(LED_MOTOR, on, 20);
}

/**
 * Odczytanie aktualnego wychylenia modułów skrętu. Po 1 bajcie na moduł, kodowanie U2, wartość: +-90, odchylenie w stopniach względem położenia domyślnego (dodatnie - skręt w prawo).
 * Ze względu na redundantną magistralę RS485, Master musi wiedzieć, kiedy transmisja z kontrolerem się zatrzymała - z tego względu ramka GET_WHEELS2 jest wysyłana w odpowiedzi
 * na ramkę SET_WHEELS, a nie cyklicznie.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
 */
void Cmd_Bus_Motor_GetWheels2(uint8_t* data) {
    for (uint8_t ch=0; ch<4; ch++) {
        bus_motor.current_angle[ch] = (int8_t)data[ch];
    }

    GpioExpander_SetLed(LED_MOTOR, on, 20);
}

/**
 * Odczytywanie aktualnych statusów podsystemów i danych kontrolnych. Nadawana cyklicznie co 100ms.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
 */
void Cmd_Bus_Motor_GetStatus(uint8_t* data) {
    bus_motor.limit_status = data[0];
    bus_motor.motor_status = data[1];
    bus_motor.status = data[2];
    bus_motor.supply_voltage = data[3];

    GpioExpander_SetLed(LED_MOTOR, on, 20);
}

/**
 * Ramka na potrzeby testów i rozwoju oprogramowania. Przekazywana na świat transparentnie, bez ingerencji.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
 */
void Cmd_Bus_Motor_DebugRx(uint8_t* data) {
    Cmd_UART_Common_DebugRx(data, DEVICE_MOTOR);

    GpioExpander_SetLed(LED_MOTOR, on, 20);
}

/*
 *  TX Frames
 */

/**
 * Ustawianie zadanej prędkości obrotu kół oraz wychylenia modułów skrętu.
 */
void Cmd_Bus_Motor_SetWheels() {
    can_packet_t msg = {
            .cmd = CAN_CMD_MOTOR_SET_WHEELS,
            .arg_count = CAN_ARG_MOTOR_SET_WHEELS,
    };

    for (uint8_t i=0; i<4; i++) {
        msg.args[i] = bus_motor.required_speed[i];
        msg.args[i+4] = bus_motor.required_angle[i];
    }

    Queues_SendCANFrame(&msg);
}



/**
 * Zlecenie kalibracji rozregulowanego modułu skrętu. Po ustawieniu silnika w pozycji zerowej (jazda do przodu), wysłanie ramki spowoduje nadpisanie wartości odniesienia,
 * względem której obliczana jest pozycja kątowa. Kalibracja wykona się tylko wtedy, gdy argumenty będą miały wartości opisane poniżej.
 * @param channel   indeks kanału do kalibracji (numeracja zgodna z powyższymi, 0..3)
 */
void Cmd_Bus_Motor_Calibrate(uint8_t channel) {
    can_packet_t msg = {
            .cmd = CAN_CMD_MOTOR_CALIBRATE,
            .arg_count = CAN_ARG_MOTOR_CALIBRATE,
            .args = {'d', 'o', ' ', 'i', 't', channel}
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Ramka do celów testowych i rozwoju oprogramowania. Przekazuje kontrolerowi przezrocznie, bez ingerencji.
 * @param data      wskaźnik do 8-bajtowego bufora danych
 */
void Cmd_Bus_Motor_DebugTx(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_MOTOR_DEBUG_TX,
            .arg_count = CAN_ARG_MOTOR_DEBUG_TX,
    };
    memcpy(msg.args, data, 8);

    Queues_SendCANFrame(&msg);
}

/**
 * Odczytywanie temperatury z termistorow w napedach
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Motor_GetTemperature(uint8_t *data){
    memcpy((void*)&bus_motor.motor_temperature, data, CAN_ARG_MOTOR_GET_TEMPERATURE);

    GpioExpander_SetLed(LED_MOTOR, on, 20);
}

