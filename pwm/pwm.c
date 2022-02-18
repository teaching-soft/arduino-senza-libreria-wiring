/* 	*************************************************
*	Giancarlo Martini 2020/06/26
*	Semplice esempio per far lampeggiare un led con il pwm
*	email:gm@giancarlomartini.it
*	http:www.giancarlomartini.it
* pwm.c
***********************************************/
#include <avr/io.h>
#include <stdlib.h>

#include "pwm.h"
#include "usart.h"

/*
 NOTE
Si usa il Fast Pwm, il duty cycle dipenda dal valore memorizzato nel registro OCR0A,
il segnale cambia stato quando il valore di conteggio eguaglia quello del registro.
La frequenza è data da F = F_CPU / (2 * N * Top) in cui F_CPU è la frequenza del micro,
N il valore di prescaler e Top il valore massimo del conteggio.
Viene usato il pin 6 di arduino che corrisponde a PD6

*/

void pwm_init()
{
	// Viene usato il pin 6 di arduino che corrisponde a PD6
	DDRD |= (1 << PD6);
	// Resetta il registro, non ce ne sarebbe bisogno, al reset sono tutti a 0
	TCCR0A = 0;
	// COM0A1: COM0A0 [1,0] segnale in uscita alto quando si ha il timer
	// a 0 e poi segnale a 0 quando il timer counter raggiunge il valore memorizzato nel registro
	TCCR0A = (1 << COM0A1);
	// Modalità Fast Pwm, valore massimo 0xFF
	TCCR0A |= (1 << WGM00) | (1 << WGM01);
	// Resetta il registro, non ce ne sarebbe bisogno, al reset sono tutti a 0
	TCCR0B = 0;
	// Imposta il prescaler al valore 8 perciò la frequenza è Fpwm = F_CPU / (Top * N) =
	// 16000 KHz / (255 * 8) = 7.84 KHz
	TCCR0B = (1 << CS01);

	// Disabilita gli interrupt
	TIMSK0 &= ~((1 << TOIE0) | (1 << OCIE0A) | (1 << OCIE0B));
}
void pwm_set_duty_cycle(uint8_t percent)
{
	// x = (255 * p) / 100; quindi per non usare i float
	uint16_t tmp_v = ( ((uint16_t) percent) * ((uint16_t) 255) ) / (uint16_t)100 ;
	/*char tmp_s[10];
	itoa(tmp_v,tmp_s,10);
	usart_send_strn(tmp_s);*/
	OCR0A = (uint8_t) tmp_v ;
}

