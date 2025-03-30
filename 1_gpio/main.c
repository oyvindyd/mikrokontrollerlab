#include <stdint.h>
#include <stdio.h>

#define BASE_ADRESS 0x50000000

#define GPIO ((NRF_GPIO_REGS *)BASE_ADRESS)

typedef struct
{
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[118];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

void button_init()
{
	GPIO->PIN_CNF[13] = (3 << 2);
	GPIO->PIN_CNF[14] = (3 << 2);
	GPIO->PIN_CNF[15] = (3 << 2);
	GPIO->PIN_CNF[16] = (3 << 2);

	// Fill inn the configuration for the remaining buttons
}

// led matrisen starter på pin 17
#define LED_PIN_START 17
#define LED_PIN_END 20
#define BUTTON_PIN_1 13
#define BUTTON_PIN_2 14

int main()
{
	// Configure LED Matrix
	for (int i = 17; i <= 20; i++)
	{
		GPIO->DIRSET = (1 << i); // setter led-matrix til output
		GPIO->OUTCLR = (1 << i); // skru av lysene ved oppstart
	}

	// Configure buttons -> see button_init()
	button_init();

	int sleep = 0;
	while (1)
	{

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		if ((GPIO->IN & (1 << BUTTON_PIN_1)) == 0)
		{
			printf("knapp 1 \n");
		}

		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */

		sleep = 10000;
		while (--sleep)
			; // Delay
	}
	return 0;
}
