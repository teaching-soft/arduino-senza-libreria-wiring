/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso dell'adc con gli interrupt
	adc.c
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	
	***********************************************/
// Include i file header del compilare gcc x micro atmel/avr
#include <avr/io.h>
#include <avr/interrupt.h>
#include "adc.h"

// F_CPU è definito sulla riga di comando al momento della compilazione
volatile uint16_t adc_value;

 ISR(ADC_vect)
 {	
	 static uint32_t n_times = 0, on = TRUE;
	 // Gestisce l'accensione spengimento del led'
	 if( on == TRUE) PORTB |= pin_led_pos;
	 else PORTB &= ~pin_led_pos;
	 n_times++;
	 if(n_times == 100000L){
			if(on == TRUE) on = FALSE;
			else on = TRUE;
		 n_times = 0;
	}
		 
	 // Recupera il valore della conversione
	adc_value = ADC;
	// Avvia un altra conversione
	ADCSRA |= (1 << ADSC);	
}



void adc_enable(BOOL what)
{
	if (what) ADCSRA |= (1 << ADEN);	// ADC control e status register, Enable adc
	else ADCSRA &= ~(1 << ADEN);
	// Analog Comparator Control and Status Register , Analog Comparator Disable (power switch off)
	if (what) ACSR &= ~(1 << ACD);		
	else ACSR |= (1 << ACD);
	
	// Abilita l'interrupt ed avvia la prima conversione impostando il campionamento automatico (Free Running mode)
	ADCSRA |= 1<<ADIE | 1<<ADSC ;
}

void adc_start()
{
	PRR &= ~(1 << PRADC);		// Power reduction register
	ADCSRA |= (1 << ADSC);	// ADC control e status register, start conversion
}

void adc_set_prescaler(enum ADCPrescaler p)
{
	// ADCSRA &= ~(0b00000111); // ADC Prescaler Select - Predefinisce ADCPrescaler_2
	switch(p) {
		case ADCPrescaler_2: ADCSRA &= ~(0b00000111); break;
		case ADCPrescaler_4: ADMUX |= 0b00000010; break;
		case ADCPrescaler_8: ADMUX |= 0b00000011; break;
		case ADCPrescaler_16: ADMUX |= 0b00000100; break;
		case ADCPrescaler_32: ADMUX |= 0b00000101; break;
		case ADCPrescaler_64: ADMUX |= 0b00000110; break;
		case ADCPrescaler_128: ADMUX |= 0b00000111; break;// Oppure ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);  
	}
}

void adc_set_channel(enum ADCChannel channel)
{
	//ADMUX &= ~(0b1111); // Predefinisce il registro portando a 0 i 4 bit, ADCChannel_0
	switch(channel) {
		case ADCChannel_0: ADMUX &= ~(0b1111); break;
		case ADCChannel_1: ADMUX |= 0b0001; break;
		case ADCChannel_2: ADMUX |= 0b0010; break;
		case ADCChannel_3: ADMUX |= 0b0011; break;
		case ADCChannel_4: ADMUX |= 0b0100; break;
		case ADCChannel_5: ADMUX |= 0b0101; break;
		case ADCChannel_6: ADMUX |= 0b0110; break;
		case ADCChannel_7: ADMUX |= 0b0111; break;
	}
}

void adc_set_voltage_reference(enum VoltageReference vr)
{
	//ADMUX &= ~(0b11000000); // Predefinisce il registro portando a 0 i 2 bit, VRAref
	
	switch(vr) {
		case VRAref: ADMUX &= ~(0b11000000); break;
		case VRVcc: ADMUX |= 0b01000000; break;// Oppure  ADMUX |= (1 << REFS0);
		case VRInternal: ADMUX |= 0b11000000; break;
	}
		
}

uint16_t adc_get_value()
{
	while( ADCSRA & (1 << ADSC) );
	return ADC;
	// ADCval = ADCL;
    // ADCval = (ADCH << 8) + ADCval; 
}

