/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso della seriale (usart)
	usart.c
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/
// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include "usart.h"

// F_CPU è definito sulla riga di comando al momento della compilazione

void usart_init(uint32_t baud_rate)
{
	// Imposta il baud rate corretto
	uint16_t ubrr_value = F_CPU / 16UL / baud_rate - 1UL;
	UBRR0H = (uint8_t) (ubrr_value >> 8);
	UBRR0L = (uint8_t) ubrr_value;

	// Imposta il formato della comunicazione
	// Bit 7/6 UMSELn Modalità sincrona/asincrona (00 = asincrona - 01 = sincrona UMSEL0 = 1)
	// Bit 5/4 UPMn Imposta la parità (00 = nessuna)
	// Bit 3 USBS0 Imposta il numero di bit di stop (0 = 1 bit)
	// Bit 2/1 UCSZn[2:0] Imposta il numero di bit dei dati (11 = 8 data bits )
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	// Abilita la ricezione e l'invio
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void usart_send_char(uint8_t c)
{
	// Attende che il registro UDRE0 sia ad 1
	while ( ! (UCSR0A & (1 << UDRE0)));
	// Invia il carattere sulla seriale
	UDR0 = c;
}

void usart_send_str(char *s)
{
	// Invia un carattere per volta, la stringa deve essere terminata con \0
	while(*s) {
		usart_send_char(*s);
		s++;
	}
}

void usart_send_strn(char *s)
{
	usart_send_str(s);
	usart_send_char(10);
}

uint8_t usart_char_ispresent(void)
{
	if ((UCSR0A & (1 << RXC0))) return TRUE;
	return FALSE;
}

unsigned char usart_get_char(void)
{
	// wait for data
	while(!(UCSR0A & (1 << RXC0)));

	// return data
	return UDR0;
}


