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
		GPIO->OUTSET = (1 << i); // skru av lysene ved oppstart
	}

	// Configure buttons -> see button_init()
	button_init();

	int sleep = 0;
	while (1)
	{

		/* Check if button 1 is pressed;
		 * turn on LED matrix if it is. */
		// bitvis and for å sjekke om IN og button_pin_1 er 
		if ((GPIO->IN & (1 << BUTTON_PIN_1)) == 0)
		{	
			
			GPIO->OUTCLR = (1 << 17);
			GPIO->OUTCLR = (1 << 18);
			GPIO->OUTCLR = (1 << 19);
			GPIO->OUTCLR = (1 << 20);
		}

		// skru av lysene med knapp 2
		if ((GPIO->IN & (1 << BUTTON_PIN_2)) == 0)
		{	
			GPIO->OUTSET = (1 << 17);
			GPIO->OUTSET = (1 << 18);
			GPIO->OUTSET = (1 << 19);
			GPIO->OUTSET = (1 << 20);
		}



		/* Check if button 2 is pressed;
		 * turn off LED matrix if it is. */

		sleep = 10000;
		while (--sleep)
			; // Delay
	}
	return 0;
}
