/* 	*************************************************
 *	Giancarlo Martini 2020/06/26
 *	Semplice esempio per far lampeggiare un led con il pwm
 *  Viene usato il timer a 8 bit (Timer/Counter0 TC0)
 *	email:gm@giancarlomartini.it
 *	http:www.giancarlomartini.it
 ***********************************************/

// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include <util/delay.h>
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

// Inizio del programma
int main(void)
{
	// usart_init(9600);
	pwm_init();
	while (1) {
		//usart_send_strn("DC 10");
		pwm_set_duty_cycle(10);
		_delay_ms(2000);

		//usart_send_strn("DC 30");
		pwm_set_duty_cycle(30);
		_delay_ms(2000);

		//usart_send_strn("DC 50");
		pwm_set_duty_cycle(50);
		_delay_ms(2000);

		//usart_send_strn("DC 70");
		pwm_set_duty_cycle(70);
		_delay_ms(2000);

		//usart_send_strn("DC 100");
		pwm_set_duty_cycle(100);
		_delay_ms(2000);
	}
}

