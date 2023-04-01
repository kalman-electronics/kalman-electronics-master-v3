#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"
#include "commands/uart/uart_cmd.h"

//TODO: rename

/*
 *  RX Frames
 */

/**
 * Odczytanie aktualnej pr�dko�ci obrotu k�. Po 2 bajty na ko�o, kodowanie U2, warto��: pr�dko�� k�towa w 0.1 stopnia na sekund� (np. -23 = jazda do ty�u z pr�dko�ci� 2.3 stopni/s).
 * Ze wzgl�du na redundantn� magistral� RS485, Master musi wiedzie� kiedy transmisja z kontrolerem si� zatrzyma�a - z tego wzgl�du ramka GET_WHEELS1 jest wysy�ana w odpowiedzi
 * na ramk� SET_WHEELS, a nie cyklicznie.
 *
 * Nie aktualne ^
 *
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Motor_GetWheels1(uint8_t* data) {
    for (uint8_t ch=0; ch<4; ch++) {
        bus_motor.current_speed[ch] += (int16_t)((data[2*ch] << 8) + data[2*ch+1]);
    }

    GpioExpander_SetLed(LED_MOTOR, on, 20);
}

/**
 * Odczytanie aktualnego wychylenia modu��w skr�tu. Po 1 bajcie na modu�, kodowanie U2, warto��: +-90, odchylenie w stopniach wzgl�dem po�o�enia domy�lnego (dodatnie - skr�t w prawo).
 * Ze wzgl�du na redundantn� magistral� RS485, Master musi wiedzie� kiedy transmisja z kontrolerem si� zatrzyma�a - z tego wzgl�du ramka GET_WHEELS2 jest wysy�ana w odpowiedzi
 * na ramk� SET_WHEELS, a nie cyklicznie.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Motor_GetWheels2(uint8_t* data) {
    for (uint8_t ch=0; ch<4; ch++) {
        bus_motor.current_angle[ch] = (int8_t)data[ch];
    }

    GpioExpander_SetLed(LED_MOTOR, on, 20);
}

/**
 * Odczytywanie aktualnych status�w podsystem�w i danych kontrolnych. Nadawana cyklicznie co 100ms.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Motor_GetStatus(uint8_t* data) {
    bus_motor.limit_status = data[0];
    bus_motor.motor_status = data[1];
    bus_motor.status = data[2];
    bus_motor.supply_voltage = data[3];

    GpioExpander_SetLed(LED_MOTOR, on, 20);
}

/**
 * Ramka na potrzeby test�w i rozwoju oprogramowania. Przekazywana na �wiat transparentnie, bez ingerencji.
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Motor_DebugRx(uint8_t* data) {
    Cmd_UART_Common_DebugRx(data, DEVICE_MOTOR);

    GpioExpander_SetLed(LED_MOTOR, on, 20);
}

/*
 *  TX Frames
 */

/**
 * Ustawianie zadanej pr�dko�ci obrotu k� oraz wychylenia modu��w skr�tu.
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
 * Zlecenie kalibracji rozregulowanego modu�u skr�tu. Po ustawieniu silnika w pozycji zerowej (jazda do przodu), wys�anie ramki spowoduje nadpisanie warto�ci odniesienia,
 * wzgl�dem kt�rej obliczana jest pozycja k�towa. Kalibracja wykona si� tylko wtedy, gdy argumenty b�d� mia�y warto�ci opisane poni�ej.
 * @param channel   indeks kanalu do kalibracji (numeracja zgodna z powyzszymi, 0..3)
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
 * Ramka na potrzeby test�w i rozwoju oprogramowania. Przekazywa� kontrolerowi transparentnie, bez ingerencji.
 * @param data      wskaznik na 8-bajtowy bufor danych
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

