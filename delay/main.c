/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso della funzione _delay_loop_2
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/

// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include <util/delay_basic.h>
// Si usa la porta B per entrambi, PB5 per il led e PB4 per il pulsante
#define pin_led_pos			0x20	//	 0b00100000 oppure 32

// Inizio del programma
int main(void)
{
	unsigned long i;
	// DATA DIRECTION REGISTER PORT B - Con il bit ad 1 = OUTPUT, bit 0 = INPUT
	// Imposta PB5/13 come output
	DDRB = DDRB | pin_led_pos;

	while (1) {
		// Accende il led
		PORTB = PORTB | pin_led_pos;
		// Decrementa il valore passato, per il valore massimo 65536 passare alla funzione 0
		// in quel caso la funzione ritorna dopo 768 milli sec con un clock di 1MHz - con un clock di 16 MHz ritorna dopo 768 / 16 = 48 ms
		// per 1s va moltiplicata per 20, per 1 ms circa _delay_loop_2(1365)
		for(uint8_t i = 0; i <= 20; i++)_delay_loop_2(0);
		// Spenge il led
		PORTB = PORTB & (~pin_led_pos);
		for(uint8_t i = 0; i <= 20; i++)_delay_loop_2(0);
	}	// Fine while
}
