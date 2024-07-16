//=====================================================================
//                          Universal Module
//=====================================================================

#include <string.h>
#include "uart_cmd.h"
#include "../can/can_cmd.h"


void Cmd_UART_Universal_SetDigitalOutput(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetDigitalOutput(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_SetPWMOutput(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetPWMOutput(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_SetLEDDriver(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetLEDDriver(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_SetHBridge(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetHBridge(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_SetStepperPosition(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetStepperPosition(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_StepperHomingRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_StepperHomingRequest(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_WeightRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_WeightRequest(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_InputRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_InputRequest(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_StepperPositionRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_StepperPositionRequest(data);
    Cmd_UART_BlinkLed(link_type);
}

void Cmd_UART_Universal_AutomationSequenceBeginRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_AutomationSequenceBeginRequest(data);
    Cmd_UART_BlinkLed(link_type);
}

void Cmd_UART_Universal_AutomationSequenceStateRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_AutomationSequenceStateRequest(data);
    Cmd_UART_BlinkLed(link_type);
}

void Cmd_UART_Universal_SetResponse(uint8_t* data) {
    uart_packet_t msg = {
        .cmd = UART_CMD_UNIVERSAL_SET_RESPONSE,
        .arg_count = UART_ARG_UNIVERSAL_SET_RESPONSE,
        .origin = logic.link_type
};

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_SET_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}

void Cmd_UART_Universal_WeightResponse(uint8_t* data){
    uart_packet_t msg = {
            .cmd = UART_CMD_UNIVERSAL_WEIGHT_RESPONSE,
            .arg_count = UART_ARG_UNIVERSAL_WEIGHT_RESPONSE,
            .origin = logic.link_type
    };

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_WEIGHT_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}
void Cmd_UART_Universal_InputResponse(uint8_t* data){
    uart_packet_t msg = {
            .cmd = UART_CMD_UNIVERSAL_INPUT_RESPONSE,
            .arg_count = UART_ARG_UNIVERSAL_INPUT_RESPONSE,
            .origin = logic.link_type
    };

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_INPUT_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}
void Cmd_UART_Universal_StepperPositionResponse(uint8_t* data){
    uart_packet_t msg = {
            .cmd = UART_CMD_UNIVERSAL_STEPPER_POSITION_RESPONSE,
            .arg_count = UART_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE,
            .origin = logic.link_type
    };

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}

void Cmd_UART_Universal_AutomationSequenceStateResponse(uint8_t* data){
    uart_packet_t msg = {
        .cmd = UART_CMD_UNIVERSAL_STEPPER_POSITION_RESPONSE,
        .arg_count = UART_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE,
        .origin = logic.link_type
};

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}

/**
 * Ustawianie zadanych kierunków i prędkości mostków H.
 * @param data      wskaźnik na bufor odebranych danych
 * @param link_type łącze komunikacyjne, na którym odebrano ramkę
 */
void Cmd_UART_Universal_SetBridge(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal SetBridge: %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            Cmd_Bus_Universal_SetBridge(data[0], data[1], &(data[2]));
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Ustawienie zadanych wartości wychylenia serw.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Universal_SetServo(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal SetServo: %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            Cmd_Bus_Universal_SetServo(data[0], data[1], &(data[2]));
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Ustawienie zadanych wartości wypełnienia PWMów mocy.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Universal_SetPwm(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal SetPwm: %d %d %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            Cmd_Bus_Universal_SetPwm(data[0], data[1], &(data[2]));
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Komenda dodana na przyszłość, aktualnie nie jest używana.
 * @param data      wskaźnik na bufor odebranych danych
 * @param link_type łącze komunikacyjne, na którym odebrano ramkę
 */
void Cmd_UART_Universal_SetGpio(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal SetGpio: %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            Cmd_Bus_Universal_SetGpio(data[0], data[1], data[2], data[3], data[4]);
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Żądanie odczytania aktualnych wartości belek tensometrycznych. W odpowiedzi Master zwraca serię ramek UNIVERSAL_GET_WEIGHT, po jednej na każdą belkę danego modułu uniwersalnego.
 * @param data      wskaźnik na bufor odebranych danych
 * @param link_type łącze komunikacyjne, na którym odebrano ramkę
 */
void Cmd_UART_Universal_GetWeightRequest(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Universal GetWeightRequest: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        uint8_t id = data[0];
        for (uint8_t index=0; index<BUS_UNIVERSAL_COUNT; index++) {
            if (id == bus_universal[index].id) {
                //znaleziono strukture odpowiadajaca modulowi o ID odczytanym z ramki
                Cmd_UART_Universal_GetWeight(id, 0);
            }
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zwraca surową wartość odczytaną z zadanej belki tensometrycznej modułu uniwersalnego o konkretnym ID.
 * @param id                bajt identyfikacji urządzenia odbiorczego
 * @param loadcell_index    numer belki tensometrycznej (na przyszłość, aktualnie niewspierane)
 */
void Cmd_UART_Universal_GetWeight(uint8_t id, uint8_t loadcell_index) {
    if ((logic.link_type == LINK_RF_UART) || (logic.link_type == LINK_AUTO_UART)) {
        uart_packet_t msg = {
            .cmd = UART_CMD_UNIVERSAL_GET_WEIGHT,
            .arg_count = UART_ARG_UNIVERSAL_GET_WEIGHT,
            .origin = logic.link_type,
        };

        for (uint8_t index=0; index<BUS_UNIVERSAL_COUNT; index++) {
            if (id == bus_universal[index].id) {
                //znaleziono strukture odpowiadajaca modulowi o podanym ID
                msg.args[0] = id;
                msg.args[1] = loadcell_index;

                uint32_t tmp = (uint32_t)bus_universal[index].loadcell_value;
                msg.args[2] = (uint8_t)((tmp >> 24) & 0xFF);
                msg.args[3] = (uint8_t)((tmp >> 16) & 0xFF);
                msg.args[4] = (uint8_t)((tmp >> 8) & 0xFF);
                msg.args[5] = (uint8_t)((tmp) & 0xFF);
                Queues_SendUARTFrame(&msg);
            }
        }
    }
}



