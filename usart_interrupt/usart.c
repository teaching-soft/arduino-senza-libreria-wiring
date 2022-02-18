/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso della seriale (usart)
	usart.c
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/
// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "usart.h"

// F_CPU è definito sulla riga di comando al momento della compilazione

// Definizione della struttura che contiene i dati da trasmettere / ricevere
typedef struct {
	// Vettore di char
	uint8_t buffer[USART_BUF_SIZE];
	// Indice
	uint8_t index;
	// Messaggio completo se è arrivato \n
	uint8_t is_complete;
} usart_buffer;

usart_buffer rx_buffer;


ISR(USART_RX_vect, ISR_BLOCK)
{
	// Preleva il carattere arrivato
	rx_buffer.buffer[rx_buffer.index] = UDR0;
	// Controlla se è il fine messaggio
	if(rx_buffer.buffer[rx_buffer.index] == USART_LAST_CHAR) {
		// Imposta il flag di fine buffer
		rx_buffer.is_complete = TRUE;
		// Mette il terminatore di stringa
		rx_buffer.buffer[rx_buffer.index] = '\0';
	}
	// Incrementa il puntatore al buffer
	rx_buffer.index++;
	// Controlla che non si vada oltre alla memoria allocata
	if(rx_buffer.index == USART_BUF_SIZE -1) rx_buffer.index = 0;
}

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

	// Abilita la ricezione,  l'invio e l'interrupt in ricezione
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	// Predispone le variabili per memorizzare i dati
	rx_buffer.index = 0;
	rx_buffer.is_complete = FALSE;

	/*
	 *Bit 7 – RXCIE0 RX Complete Interrupt Enable 0
	Writing this bit to one enables interrupt on the RXC0 flag. A USART receive complete interrupt will be
	generated only if the RXCIE0 bit is written to one, the global interrupt flag in SREG is written to one and
	the RXC0 bit in UCSR0A is set.

	Bit 6 – TXCIE0 TX Complete Interrupt Enable 0
	Writing this bit to one enables interrupt on the TXC0 flag. A USART transmit complete interrupt will be
	generated only if the TXCIE0 bit is written to one, the global interrupt flag in SREG is written to one and
	the TXC0 bit in UCSR0A is set.
	*/

}


BOOL usart_complete()
{
	return rx_buffer.is_complete;
}

void usart_get_str(char s[])
{
	// Disabilita gli interrupt
	cli();
	// Copia ciò che è arrivato
	strcpy(s,rx_buffer.buffer);
	// Ripristina le variabili
	rx_buffer.is_complete = FALSE;
	rx_buffer.index = 0;
	// Abilita gli interrupt
	sei();
}

// Usato per il debug
void usart_send_char(uint8_t c)
{
	// Attende che il registro UDRE0 sia ad 1
	while ( ! (UCSR0A & (1 << UDRE0)));
	// Invia il carattere sulla seriale
	UDR0 = c;
}

