#pragma once
void uart_init();
void uart_send(char letter);
char uart_read();

#define BASE_ADRESS 0x40002000

#define UART ((NRF_UART_REG *)BASE_ADRESS)

typedef struct {
    uint32_t  TASKS_STARTRX;                /*!< (@ 0x00000000) Start UART receiver                                        */
    uint32_t  TASKS_STOPRX;                 /*!< (@ 0x00000004) Stop UART receiver                                         */
    uint32_t  TASKS_STARTTX;                /*!< (@ 0x00000008) Start UART transmitter                                     */
    uint32_t  TASKS_STOPTX;                 /*!< (@ 0x0000000C) Stop UART transmitter                                      */
    uint32_t  RESERVED[3];
    uint32_t  TASKS_SUSPEND;                /*!< (@ 0x0000001C) Suspend UART                                               */
    uint32_t  RESERVED1[56];
    uint32_t  EVENTS_CTS;                   /*!< (@ 0x00000100) CTS is activated (set low). Clear To Send.                 */
    uint32_t  EVENTS_NCTS;                  /*!< (@ 0x00000104) CTS is deactivated (set high). Not Clear To Send.          */
    uint32_t  EVENTS_RXDRDY;                /*!< (@ 0x00000108) Data received in RXD                                       */
    uint32_t  RESERVED2[4];
    uint32_t  EVENTS_TXDRDY;                /*!< (@ 0x0000011C) Data sent from TXD                                         */
    uint32_t  RESERVED3;
    uint32_t  EVENTS_ERROR;                 /*!< (@ 0x00000124) Error detected                                             */
    uint32_t  RESERVED4[7];
    uint32_t  EVENTS_RXTO;                  /*!< (@ 0x00000144) Receiver timeout                                           */
    uint32_t  RESERVED5[46];
    uint32_t  SHORTS;                       /*!< (@ 0x00000200) Shortcuts between local events and tasks                   */
    uint32_t  RESERVED6[64];
    uint32_t  INTENSET;                     /*!< (@ 0x00000304) Enable interrupt                                           */
    uint32_t  INTENCLR;                     /*!< (@ 0x00000308) Disable interrupt                                          */
    uint32_t  RESERVED7[93];
    uint32_t  ERRORSRC;                     /*!< (@ 0x00000480) Error source                                               */
    uint32_t  RESERVED8[31];
    uint32_t  ENABLE;                       /*!< (@ 0x00000500) Enable UART                                                */
    uint32_t  RESERVED9;
    uint32_t  PSELRTS;                      /*!< (@ 0x00000508) Pin select for RTS                                         */
    uint32_t  PSELTXD;                      /*!< (@ 0x0000050C) Pin select for TXD                                         */
    uint32_t  PSELCTS;                      /*!< (@ 0x00000510) Pin select for CTS                                         */
    uint32_t  PSELRXD;                      /*!< (@ 0x00000514) Pin select for RXD                                         */
    uint32_t  RXD;                          /*!< (@ 0x00000518) RXD register                                               */
    uint32_t  TXD;                          /*!< (@ 0x0000051C) TXD register                                               */
    uint32_t  RESERVED10;
    uint32_t  BAUDRATE;                     /*!< (@ 0x00000524) Baud rate                                                  */
    uint32_t  RESERVED11[17];
    uint32_t  CONFIG;  
} NRF_UART_REG;