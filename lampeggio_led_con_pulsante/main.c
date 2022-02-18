/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio per far lampeggiare un led + pulsante
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/

// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
// Si usa la porta B per entrambi, PB5 per il led e PB4 per il pulsante
#define pin_led_pos			0x20	//	 0b00100000 oppure 32
#define pin_button_pos		0x10		//  0b00010000 oppure 16

// Inizio del programma
int main(void)
{
	unsigned long i;
	// DATA DIRECTION REGISTER PORT B - Con il bit ad 1 = OUTPUT, bit 0 = INPUT
	// Imposta PB5/13 come output
	DDRB = DDRB | pin_led_pos;
	// Imposta il PB4/12 come input mettendo il rispettivo bit a 0
	DDRB = DDRB & (~pin_button_pos);

	while (1) {
		// Controlla il pin PB4 per vedere se è premuto il pulsante
		if(PINB & pin_button_pos) {
			// Accende il led scrivendo 1 al 5 bit della porta B
			PORTB = PORTB | pin_led_pos;
		} else {
			// Spenge il led
			PORTB = PORTB & (~pin_led_pos);
		}
	}	// Fine while
}
