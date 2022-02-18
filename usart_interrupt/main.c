/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso della seriale (usart) con gli interrupt
	main.c
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/

// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "usart.h"

#define pin_led_pos			0x20	//	 0b00100000 oppure 32

// Inizio del programma
int main(void)
{
	// unsigned long i;
	char str[USART_BUF_SIZE];
	// DATA DIRECTION REGISTER PORT B - Con il bit ad 1 = OUTPUT, bit 0 = INPUT
	// Imposta PB5/13 come output
	DDRB = DDRB | pin_led_pos;

	// Inizializza la porta USART
	usart_init(9600);

	// Abilita gli interrutp
	sei();

	while (1) {
		// Controlla se è arrivato tutto
		BOOL  flag = usart_complete();
		if(flag == TRUE) {
			usart_get_str(str);
			/*uint8_t i = 0;
			usart_send_char('[');
			while(str[i] != '\0') {
				usart_send_char(str[i]);
				i++;
			}
			usart_send_char(']');
			usart_send_char('\n');*/
			if(strcmp(str,"SI") == 0)	PORTB = PORTB | pin_led_pos;
			if(strcmp(str,"NO") == 0)	PORTB = PORTB & (~pin_led_pos);
		}
	}	// Fine while
}
