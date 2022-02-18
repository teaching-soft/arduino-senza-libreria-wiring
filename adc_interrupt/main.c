/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso dell'adc
	main.c
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/

// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "adc.h"
#include "usart.h"

// Inizio del programma
int main(void)
{
	char value_str[10];
	// Imposta PB5/13 come output
	DDRB = DDRB | pin_led_pos;
	// Inisizlizza l'usart'
	usart_init	(9600);
	
	// Imposta i parametri diconfigurazione
	adc_set_channel(ADCChannel_0);
	adc_set_voltage_reference(VRVcc);
	adc_set_prescaler(ADCPrescaler_2);
	adc_enable(TRUE);

	// Abilita gi interrutp
	sei();
	while (1) {
		usart_send_strn("DISABILITA GLI INTERRUPT");
		// Disabilita gli interrupt
		cli();
		uint16_t value = adc_value;
		// Abilita gi interrutp
		sei();
		usart_send_strn("ABILITO GLI INTERRUTP");
		// Converto il valore letto in stringa
		itoa(value,value_str,10);
		usart_send_strn(value_str);
		// Attendo per poter leggere meglio i valori della seriale
		for (uint32_t i = 0; i < 10000; i++);			
  }	// Fine while
}
