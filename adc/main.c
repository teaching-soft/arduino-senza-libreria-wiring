/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso del convertitore
	main.c
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/

// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include <stdlib.h>
#include "adc.h"
#include "usart.h"

#define pin_led_pos			0x20	//	 0b00100000 oppure 32

// Inizio del programma
int main(void)
{
	char value_str[10];
	// Imposta PB5/13 come output
	DDRB = DDRB | pin_led_pos;
	usart_init	(9600);

	while (1) {
		// Accende il led scrivendo 1 al 5 bit della porta B
		PORTB = PORTB | pin_led_pos;
		usart_send_strn("AVVIO CONVERSIONE");
		adc_set_channel(ADCChannel_0);
		adc_set_voltage_reference(VRVcc);
		adc_set_prescaler(ADCPrescaler_2);
		adc_enable(TRUE);
		adc_start();
		uint16_t value = adc_get_value();
		itoa(value,value_str,10);
		usart_send_strn(value_str);
		usart_send_strn("FINE CONVERSIONE");
		// Spenge il led
		PORTB = PORTB & (~pin_led_pos);
		for (uint32_t i = 0; i < 100000; i++);
	}	// Fine while
}
