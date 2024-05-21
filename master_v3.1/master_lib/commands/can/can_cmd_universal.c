#include <string.h>
#include "can_cmd.h"
#include "../../hw/hw.h"
#include "../uart/uart_cmd.h"

/*
 *  RX Frames
 */

/**
 * Zwracanie aktualnej surowej wartości odczytu z belki tensometrycznej. Jedna ramka dotyczy tylko jednej belki
 * @param data      wskaznik na bufor odebranych danych
 * @param count     ilosc odebranych danych w ramce
 */
void Cmd_Bus_Universal_GetWeight(uint8_t* data) {
    for (uint16_t index = 0; index < BUS_UNIVERSAL_COUNT; index++) {
        if (data[0] == bus_universal[index].id) {
            //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki

            //indeks belki - nieuzywany
            bus_universal[index].loadcell_value = (int32_t)(((uint32_t)data[2] << 24UL) | ((uint32_t)data[3] << 16UL) | ((uint32_t)data[4] << 8UL) | ((uint32_t)data[5]));

            break;
        }
    }

    GpioExpander_SetLed(LED_UNIVERSAL2, on, 20);
}

/**
 * Odczytywanie aktualnych statusów podsystemów i danych kontrolnych.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
 */
void Cmd_Bus_Universal_GetStatus(uint8_t* data) {
    for (uint16_t index = 0; index < BUS_UNIVERSAL_COUNT; index++) {
        if (data[0] == bus_universal[index].id) {
            //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki

            bus_universal[index].status = data[1];
            bus_universal[index].supply_voltage = data[2];

            break;
        }
    }

    GpioExpander_SetLed(LED_UNIVERSAL2, on, 20);
}

/**
 * Ramka na potrzeby testów i rozwoju oprogramowania. Przekazywana na świat transparentnie, bez ingerencji.
 * @param data      wskaźnik na bufor odebranych danych
 * @param count     ilość odebranych danych w ramce
 */
void Cmd_Bus_Universal_DebugRx(uint8_t* data) {
    Cmd_UART_Common_DebugRx(data, DEVICE_UNIVERSAL);

    GpioExpander_SetLed(LED_UNIVERSAL2, on, 20);
}

/*
 *  TX Frames
 */
void Cmd_Bus_Universal_SetDigitalOutput(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_SET_DIGITAL_OUTPUT,
            .arg_count = CAN_ARG_UNIVERSAL_SET_DIGITAL_OUTPUT
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_DIGITAL_OUTPUT);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_SetPWMOutput(uint8_t* data) {
    can_packet_t msg = {
            .cmd  = CAN_CMD_UNIVERSAL_SET_PWM_OUTPUT,
            .arg_count = CAN_ARG_UNIVERSAL_SET_PWM_OUTPUT
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_PWM_OUTPUT);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_SetLEDDriver(uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_SET_LED_DRIVER,
            .arg_count =  CAN_ARG_UNIVERSAL_SET_LED_DRIVER
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_LED_DRIVER);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_SetHBridge(uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_SET_HBRIDGE,
            .arg_count = CAN_ARG_UNIVERSAL_SET_HBRIDGE
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_HBRIDGE);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_SetStepperPosition(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_SET_STEPPER_POSITION,
            .arg_count = CAN_ARG_UNIVERSAL_SET_STEPPER_POSITION
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_STEPPER_POSITION);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_StepperHomingRequest(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_STEPPER_HOMING_REQUEST,
            .arg_count = CAN_ARG_UNIVERSAL_STEPPER_HOMING_REQUEST,
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_STEPPER_HOMING_REQUEST);

    Queues_SendCANFrame(&msg);
}
void Cmd_Bus_Universal_WeightRequest(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_WEIGHT_REQUEST,
            .arg_count = CAN_ARG_UNIVERSAL_WEIGHT_REQUEST
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_WEIGHT_REQUEST);

    Queues_SendCANFrame(&msg);
}
void Cmd_Bus_Universal_InputRequest(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_INPUT_REQUEST,
            .arg_count = CAN_ARG_UNIVERSAL_INPUT_REQUEST
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_INPUT_REQUEST);

    Queues_SendCANFrame(&msg);
}
void Cmd_Bus_Universal_StepperPositionRequest(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_STEPPER_POSITION_REQUEST,
            .arg_count = CAN_ARG_UNIVERSAL_STEPPER_POSITION_REQUEST
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_STEPPER_POSITION_REQUEST);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_WeightResponse(uint8_t *data) {
    Cmd_UART_Universal_WeightResponse(data, LINK_RF_UART);
}
void Cmd_Bus_Universal_InputResponse(uint8_t *data) {
    Cmd_UART_Universal_InputResponse(data, LINK_RF_UART);
}
void Cmd_Bus_Universal_StepperPositionResponse(uint8_t *data) {
    Cmd_UART_Universal_StepperPositionResponse(data, LINK_RF_UART);
}



/**
 * Ustawianie zadanych kierunków i prędkości mostków H. Na każdy mostek przypadają 2 bajty, kodowane jako 16-bitowe inty w formacie U2. Dozwolone zakresy: od -1000 do +1000.
 * @param id        bajt identyfikacji urządzenia odbiorczego
 * @param flags     flagi aktualizacji wartości
 * @param data      wskaźnik na bufor wartości dla mostków (MSB pierwszego, LSB pierwszego, MSB drugiego, LSB drugiego)
 */
void Cmd_Bus_Universal_SetBridge(uint8_t id, uint8_t flags, uint8_t* data) {
    can_packet_t msg = {
        .cmd = CAN_CMD_UNIVERSAL_SET_BRIDGE,
        .arg_count = CAN_ARG_UNIVERSAL_SET_BRIDGE,
        .args = {id, flags},
    };
    memcpy(msg.args + 2, data, 4);

    Queues_SendCANFrame(&msg);
}



/**
 * Ustawienie zadanych wartości wychylenia serw. Kodowanie i wartości: 0-100, w procentach wychylenia. Wartość 0% odpowiada wypełnieniu 0.5ms, a 100% - 2.5ms.
 * @param id        bajt identyfikacji urządzenia odbiorczego
 * @param flags     flagi aktualizacji wartości
 * @param data      wskaźnik na bufor wartości dla serw (wartości 0..100 dla kolejnych 4 wyjść, licząc od pierwszego)
 */
void Cmd_Bus_Universal_SetServo(uint8_t id, uint8_t flags, uint8_t* data) {
    can_packet_t msg = {
        .cmd = CAN_CMD_UNIVERSAL_SET_SERVO,
        .arg_count = CAN_ARG_UNIVERSAL_SET_SERVO,
        .args = {id, flags},
    };
    memcpy(msg.args + 2, data, 4);

    Queues_SendCANFrame(&msg);
}



/**
 * Ustawienie zadanych wartości wypełnienia PWM-ów mocy. Kodowanie i wartości: 0-100, w procentach.
 * @param id        bajt identyfikacji urządzenia odbiorczego
 * @param flags     flagi aktualizacji wartości
 * @param data      wskaźnik na bufor wartości dla PWM-ów (wartości 0..100 dla kolejnych 6 wyjść, licząc od pierwszego)
 */
void Cmd_Bus_Universal_SetPwm(uint8_t id, uint8_t flags, uint8_t *data) {
    can_packet_t msg = {
        .cmd = CAN_CMD_UNIVERSAL_SET_PWM,
        .arg_count = CAN_ARG_UNIVERSAL_SET_PWM,
        .args = {id, flags},
    };
    memcpy(msg.args + 2, data, 6);

    Queues_SendCANFrame(&msg);
}



/**
 * Ustawienie zadanych wartości wyjść GPIO.
 * @note            aktualnie funkcja nie jest wykorzystywana
 * @param id        bajt identyfikacji urządzenia odbiorczego
 * @param flags1    flagi aktualizacji wartości
 * @param flags2    flagi aktualizacji wartości
 * @param gpio1     wartości wyjść GPIO od 1 do 8
 * @param gpio2     wartości wyjść GPIO od 9 do 14
 */
void Cmd_Bus_Universal_SetGpio(uint8_t id, uint8_t flags1, uint8_t flags2, uint8_t gpio1, uint8_t gpio2) {
    can_packet_t msg = {
        .cmd = CAN_CMD_UNIVERSAL_SET_GPIO,
        .arg_count = CAN_ARG_UNIVERSAL_SET_GPIO,
        .args = {id, flags1, flags2, gpio1, gpio2},
    };

    Queues_SendCANFrame(&msg);
}



/**
 * Ramka na potrzeby testów i rozwoju oprogramowania. Przekazywana kontrolerowi transparentnie, bez ingerencji.
 * @param data      wskaźnik na 8-bajtowy bufor danych
 */
void Cmd_Bus_Universal_DebugTx(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_DEBUG_TX,
            .arg_count = CAN_ARG_UNIVERSAL_DEBUG_TX,
    };
    memcpy(msg.args, data, 8);

    Queues_SendCANFrame(&msg);
}
