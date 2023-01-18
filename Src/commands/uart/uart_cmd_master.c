//=====================================================================
//                 komendy dodatkowe modulu Master v2
//=====================================================================

#include <string.h>
#include "uart_cmd.h"


/**
 * Wyb�r aktualnego ��cza komunikacyjnego. Komenda jako jedyna mo�e zosta� odebrana na dowolnym ��czu, bez wzgl�du na to kt�re obecnie obs�uguje modu� Master.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Master_SetLink(uint8_t *data, uart_packet_link_t link_type) {
    //komenda zawsze mozliwa do odebrania, bez wzgledu na aktualnie wybrane lacze i lacze po ktorym ja wyslano
    //dodatkowo informacja zawsze wysylana na uart debugowy

    printf("[%s] Master SetLink: %d\r\n",
            (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
            data[0]);

    //TODO: more dynamic uart
    uart_packet_link_t new_link = LINK_RF_UART;
    if (data[0] == 0) {
        new_link = LINK_RF_UART;
    }
    else if (data[0] == 1) {
        new_link = LINK_AUTO_UART;
    }
    else if (data[0] == 2) {
        new_link = LINK_AUTO_UART;
    }

    //najpierw odsylana jest odpowiedz na poprzednie lacze, a potem nastepuje jego aktualizacja
    Cmd_UART_Master_SetLinkResponse(new_link);
    logic.link_type = new_link;

    Cmd_UART_BlinkLed(link_type);
}



/**
 * Wyb�r trybu zwracania przez modu� Master ramek statusowych.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
void Cmd_UART_Master_SetStatusMode(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            printf("[%s] Master SetStatusMode INOP!: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        //TODO: verbosity select
        uint8_t mode = data[0];
        if (mode == 0) {
            //logic.status_mode = status_mode_none;
        }
        else if (mode == 1) {
            //logic.status_mode = status_mode_basic;
        }
        else if (mode == 2) {
            //logic.status_mode = status_mode_detailed;
        }

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Wyb�r ��danego widoku wizji analogowej. Dane przekazywane s� do Raspberry obs�uguj�cego konwersj� streamu IP na sygna� analogowy.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 *//*
void Cmd_Master_SetVideoChannel(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            printf("[%s] Master SetVideoChannel: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        //przekierowanie ramki do Raspberry przez uart pomocniczy
        Uarts_Aux_SendFrame(CMD_MASTER_SET_VIDEO_CHANNEL, ARG_MASTER_SET_VIDEO_CHANNEL, data);
        Uarts_Aux_SendBuf((uint8_t*)"\n", 1); //dodatkowy znak konca linii, zgodnie z wytycznymi

        Cmd_UART_BlinkLed(link_type);
    }
}*/

/**
 * "Wci�ni�cie" przycisku zasilania komputera pok�adowego.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
//TODO: PC control
void Cmd_UART_Master_ComputerPowerOn(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART)) && (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            printf("[%s] Master ComputerPowerOn\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"));
        //}

        //Logic_Gpio_ComputerPowerOn();

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * "Wci�ni�cie" przycisku resetu komputera pok�adowego.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
//TODO: PC control
void Cmd_UART_Master_ComputerReset(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART)) && (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            printf("[%s] Master ComputerReset\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"));
        //}

        //Logic_Gpio_ComputerReset();

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Reset Raspberry Pi 3 odpowiedzialnego za wizj� analogow�.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 *//*
void Cmd_UART_Master_RaspberryReset(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            printf("[%s] Master RaspberryReset\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"));
        }//

        //Logic_Gpio_RaspberryReset();

        Cmd_UART_BlinkLed(link_type);
    }
}*/



/**
 * Wyb�r informacji wysy�anych na debugowym uarcie modu�u Master.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
//TODO: verbosity select
void Cmd_UART_Master_SetDebugInfo(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            printf("[%s] Master SetDebugInfo INOP!: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);
        //}

        uint8_t info = data[0];
        //if (info != logic_flash.debug_info) {
        //    logic_flash.debug_info = data[0];
        //    Logic_Flash_Write();
        //}

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zmiana stanu wyj�cia odpowiedzialnego za lamp� sygnalizacyjn�.
 * @warning aktualnie nieuzywane - patrz Cmd_Arm_SetMagnet
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 */
 /*
void Cmd_Master_SetIndicator(uint8_t *data, uart_packet_link_t link_type) {
    if (link_type == logic.link_type) {
        //if (logic_flash.debug_info & debug_comm_control) {
            printf("[%s] Master SetIndicator: %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0]);

            printf("   Funkcja przestarzala, uzyj Arm SetMagnet.\r\n");
        }

        Cmd_UART_BlinkLed(link_type);
    }
}*/



/**
 * Zadawanie pr�dko�ci kamery PTZ (x,y,zoom). Ramka przekazywana przez Mastera do Raspberry Pi, nast�pnie przez ONVIF do kamer z funkcj� PTZ.
 * @param data      wskaznik na bufor odebranych danych
 * @param link_type lacze komunikacyjne, na ktorym odebrano ramke
 *//*
void Cmd_Master_SetPtzMove(uint8_t *data, uart_packet_link_t link_type) {
    if (((link_type == LINK_RF_UART) || (link_type == LINK_AUTO_UART)) && (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            printf("[%s] Master SetPtzMove: %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3]);
        //}

        //przekierowanie ramki do Raspberry przez uart pomocniczy
        Uarts_Aux_SendFrame(CMD_MASTER_SET_PTZ_MOVE, ARG_MASTER_SET_PTZ_MOVE, data);
        Uarts_Aux_SendBuf((uint8_t*)"\n", 1); //dodatkowy znak konca linii, zgodnie z wytycznymi

        Cmd_UART_BlinkLed(link_type);
    }
}*/



/**
 * Zwracanie potwierdzenia zmiany ��cza komunikacyjnego, po odebraniu komendy Cmd_Master_SetLink. Ramka zwracana jest jeszcze na poprzednim ��czu (tzn. odsy�ana jest przed zmian�).
 */
void Cmd_UART_Master_SetLinkResponse(uart_packet_link_t new_link) {
    uart_packet_t msg = {
        .cmd = UART_CMD_MASTER_SET_LINK_RESPONSE,
        .arg_count = UART_ARG_MASTER_SET_LINK_RESPONSE,
        .origin = logic.link_type,
        .args = {new_link}
    };

    Queues_SendUARTFrame(&msg);
}



/**
 * Zwracanie podstawowych status�w pracy systemu elektroniki. Ramka wysy�ana jest tylko wtedy, gdy ustawiono odpowiedni tryb (patrz Cmd_Master_SetStatusMode).
 */
void Cmd_UART_Master_GetBasicStatus(void) {
    uart_packet_link_t link = logic.link_type;
    if ((link == LINK_RF_UART) || (link == LINK_AUTO_UART)) {
        //static uint8_t args[ARG_MASTER_GET_BASIC_STATUS];

        //todo uzupelnic komende Master_GetBasicStatus
        //widze ze nie tylko mi sie nie chcialo ~mily

        //Uarts_SendFrame(link, CMD_MASTER_GET_BASIC_STATUS, ARG_MASTER_GET_BASIC_STATUS, args);
    }
}



/**
 * Zwracanie szczeg�owych status�w pracy systemu elektroniki. Ramka wysy�ana jest tylko wtedy, gdy ustawiono odpowiedni tryb (patrz Cmd_Master_SetStatusMode).
 */
void Cmd_UART_Master_GetDetailedStatus(void) {
    uart_packet_link_t link = logic.link_type;
    if ((link == LINK_RF_UART) || (link == LINK_AUTO_UART)) {
        //static uint8_t args[ARG_MASTER_GET_DETAILED_STATUS];

        //todo uzupelnic komende Master_GetDetailedStatus

        //Uarts_SendFrame(link, CMD_MASTER_GET_DETAILED_STATUS, ARG_MASTER_GET_DETAILED_STATUS, args);
    }
}
