#include <stdint.h>
#include <stdio.h>
#include "uarth.h"
#include "gpio.h"




void uart_init() {
    GPIO->PIN_CNF[8] = 1;       // setter mottakslinja RX til 0 (mottak)
    GPIO->PIN_CNF[6] = 0;       // setter sendelinja TX til 1 (sende)

    UART->PSELRXD = 8;          // setter pinnene i UART sin PSELRXD-mottaks regiseter
    UART->PSELTXD = 6;          // --||-- sende register

    UART->BAUDRATE = 0x00275000;    // setter BAUDRATEN til 9600
    
    // forteller UART modulen at vi ikke har CTS eller TRS koblinger
    UART->PSELRTS = 0xFFFFFFFF;       
    UART->PSELCTS = 0xFFFFFFFF;

    UART->ENABLE = 4;                   // skrur på UART modulen
    UART->TASKS_STARTRX = 1;            // starter UART reciever
}

void uart_send(char letter) {
    UART->TASKS_STARTTX = 1;        // triggering STARTTTX task
    UART->TXD = letter;             // data sendes i TXD registeret
    while (!(UART->EVENTS_TXDRDY));    // venter på at dataen skal sendes

    UART->EVENTS_TXDRDY = 0;        // clearer interruptet som kommer når man er ferdig å sende
    UART->TASKS_STOPTX = 1;         // stopper transmit, sier ifra at man er ferdig
}

char uart_read() {

    if (UART->EVENTS_RXDRDY != 0) {
        UART->EVENTS_RXDRDY = 0;        // unngå pakketap
        return UART->RXD;
    }
    else {
        return '\0';
    }
}


