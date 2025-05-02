#include <stdint.h>
#include <stdio.h>
#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

void button_init()
{
	GPIO->PIN_CNF[13] = (3 << 2);        // | (3 << 2) for pull up på knappene
	GPIO->PIN_CNF[14] = (3 << 2);
	GPIO->PIN_CNF[15] = (3 << 2);
	GPIO->PIN_CNF[16] = (3 << 2);

}

void led_init() {
    // initaliserer LEDene
    for (int i = 17; i <= 20; i++)
	{
		GPIO->DIRSET = (1 << i); // setter led-matrix til output
		GPIO->OUTSET = (1 << i); // skru av lysene ved oppstart
	}
}

int main() {
    // GPIO init
    button_init();
    led_init();
    
    
    // setter opp kanal 0 for event
    GPIOTE->CONFIG[0] = (13 << 8) | (1 << 0) | (1 << 16);     // knapp 1 med pin 13 settes i config0. Bitskift 8??

    GPIOTE->CONFIG[1] = (17 << 8) | (3 << 0) | (3 << 16);
    GPIOTE->CONFIG[2] = (18 << 8) | (3 << 0) | (3 << 16);
    GPIOTE->CONFIG[3] = (19 << 8) | (3 << 0) | (3 << 16);
    GPIOTE->CONFIG[4] = (20 << 8) | (3 << 0) | (3 << 16);

    // Button1 knappehendelsen kobles til oppgavene (fire ppi kanaler, en for hver pinne)
    for (int i = 0; i < 4; i++) {
        PPI->PPI_CH[i].EEP = (uint32_t)&GPIOTE->EVENTS_IN[0];       // typecaster til uint32_t. EEP = event end point
        PPI->PPI_CH[i].TEP = (uint32_t)&GPIOTE->TASKS_OUT[i + 1];   // ----||------             TEP = task end point

        // aktiverer PPI-kanal nummer i ved å sette høy i Chenset-registeret
        PPI->CHENSET = (1 << i);                    
    }

    while (1) {

    }

    return 0;
}