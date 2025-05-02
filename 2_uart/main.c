#include <stdint.h>
#include <stdio.h>
#include "uarth.h"
#include "gpio.h"

// initaliserer knappene
void button_init() {
    GPIO->PIN_CNF[13] = (3 << 2);
    GPIO->PIN_CNF[14] = (3 << 2);
    GPIO->PIN_CNF[15] = (3 << 2);
    GPIO->PIN_CNF[16] = (3 << 2);
}

int main() {

    button_init();
    uart_init();

    // initaliserer LEDene
    for (int i = 17; i <= 20; i++)
	{
		GPIO->DIRSET = (1 << i); // setter led-matrix til output
		GPIO->OUTSET = (1 << i); // skru av lysene ved oppstart
	}

    #define LED_PIN_START 17
    #define LED_PIN_END 20
    #define BUTTON_PIN_1 13
    #define BUTTON_PIN_2 14

    int sleep = 0;
    int light_on = 1;

	while (1)
	{
        
        // lytter etter BTN-1
        if ((GPIO->IN & (1 << BUTTON_PIN_1)) == 0)
		{	
            uart_send('A');
		}

        // lytter etter BTN-2
        if ((GPIO->IN & (1 << BUTTON_PIN_2)) == 0)
		{	
			uart_send('B');
		}

        // Skru på LED gitt tastaturtrykk
        if (uart_read() != 0 && light_on == 1) {
            GPIO->OUTCLR = (1 << 17);
            GPIO->OUTCLR = (1 << 18);
            GPIO->OUTCLR = (1 << 19);
            GPIO->OUTCLR = (1 << 20);
            light_on = 1;
        } else if (uart_read() != 0 && light_on == 0) {
            GPIO->OUTSET = (1 << 17);
            GPIO->OUTSET = (1 << 18);
            GPIO->OUTSET = (1 << 19);
            GPIO->OUTSET = (1 << 20);
            light_on = 0;
        }

		
		sleep = 10000;
		while (--sleep); // Delay
	}

    return 0;
}