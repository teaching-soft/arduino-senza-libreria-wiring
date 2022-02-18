/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio per far lampeggiare un led
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/

// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>

// Inizio del programma
int main(void)
{
	unsigned long i;
	// DATA DIRECTION REGISTER PORT B
	// Imposta il pin PB5/D13 come output mettendo
	// Con il bit ad 1 = OUTPUT, bit 0 = INPUT
	// PB5 = porta B, pin num. 5, contando da 0
	// DDRB = DDRB | 0x20 oppure DDRB = DDRB | 32
	DDRB = DDRB | 0b00100000;

	while (1) {
		// Accende il led scrivendo 1 al 5 bit
		// della porta B
		PORTB = PORTB | 0b00100000;
		// Pausa
		for (uint32_t i = 0; i < 100000; i++);
		// Spenge il led scrivendo 0 al 5 bit
		// della porta B
		PORTB = PORTB & 0b11011111;
		// Pausa
		for (uint32_t i = 0; i < 100000; i++);
	}
}
