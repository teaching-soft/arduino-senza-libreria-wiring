/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso della seriale (usart)
	main.c
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/

// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include "usart.h"

#define pin_led_pos			0x20	//	 0b00100000 oppure 32

// Inizio del programma
int main(void)
{
	unsigned long i;
	// DATA DIRECTION REGISTER PORT B - Con il bit ad 1 = OUTPUT, bit 0 = INPUT
	// Imposta PB5/13 come output
	DDRB = DDRB | pin_led_pos;

	// Inizializza la porta USART
	usart_init(9600);

	while (1) {
		// Accende il led scrivendo 1 al 5 bit della porta B
		PORTB = PORTB | pin_led_pos;
		usart_send_strn("ACCESO");
		for (uint32_t i = 0; i < 100000; i++);

		// Spenge il led
		PORTB = PORTB & (~pin_led_pos);
		usart_send_strn("SPENTO");
		for (uint32_t i = 0; i < 100000; i++);
		if(usart_char_ispresent()) {
			unsigned char char_arrived = usart_get_char();
			usart_send_char(char_arrived);
			usart_send_char(10);
		}

	}	// Fine while
}
