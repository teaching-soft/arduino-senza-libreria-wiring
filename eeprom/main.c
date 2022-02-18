/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso della memoria eeprom'
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/

// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <util/delay_basic.h>
#include "usart.h"

// Si usa la porta B per entrambi, PB5 per il led e PB4 per il pulsante
#define pin_led_pos			0x20	//	 0b00100000 oppure 32
#define pin_button_pos		0x10		//  0b00010000 oppure 16
#define EE_MEM_POS		(uint8_t *)0x00

// Inizio del programma
int main(void)
{
	unsigned long i;
	char ee_value_str[10];
	// DATA DIRECTION REGISTER PORT B - Con il bit ad 1 = OUTPUT, bit 0 = INPUT
	// Imposta PB5/13 come output
	DDRB = DDRB | pin_led_pos;
	// Imposta il PB4/12 come input mettendo il rispettivo bit a 0
	DDRB = DDRB & (~pin_button_pos);
	// Inizializza la seriale
	usart_init(9600);
	while (1) {
		// Controlla il pin PB4 per vedere se è premuto il pulsante
		if(PINB & pin_button_pos) {
			// Attende 48 ms
			_delay_loop_2(0);
			// Looppa finche il tasto non è stato rilasciato
			while((PINB & pin_button_pos) != 0);
			// Accende il led scrivendo 1 al 5 bit della porta B
			PORTB = PORTB | pin_led_pos;
			// Legge il valore memorizzato nella eeprom alla posizione 0 su 1024 per Arduino
			uint8_t ee_value = eeprom_read_byte(EE_MEM_POS);
			// Lo invia sulla seriale
			itoa(ee_value,ee_value_str,10);
			usart_send_str(ee_value_str);
			usart_send_char('-');
			// Controlla se ha raggiunto il massimo
			if(ee_value == 0xFF) ee_value = 0;
			// Incrementa il valore letto
			ee_value++;
			// Attende che la eeprom sia pronta
			eeprom_busy_wait ();
			// Lo scrive nella eeprom
			eeprom_write_byte	(EE_MEM_POS,ee_value);
			// Lo invia sulla seriale
			itoa(ee_value,ee_value_str,10);
			usart_send_strn(ee_value_str);
		} else {
			// Spenge il led
			PORTB = PORTB & (~pin_led_pos);
		}
	}	// Fine while
}
