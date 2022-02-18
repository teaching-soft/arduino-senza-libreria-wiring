/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso del convertitore
	adc.h
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/
#ifndef TRUE
#define BOOL	uint8_t
#define TRUE	1
#define FALSE 0
#endif

enum ADCChannel {ADCChannel_0,ADCChannel_1, ADCChannel_2,ADCChannel_3,ADCChannel_4,ADCChannel_5,
				 ADCChannel_6,ADCChannel_7
				};

enum VoltageReference {VRAref, VRVcc, VRInternal};

enum ADCPrescaler {ADCPrescaler_2,ADCPrescaler_4,ADCPrescaler_8,ADCPrescaler_16,ADCPrescaler_32,ADCPrescaler_64,ADCPrescaler_128};

void adc_enable(BOOL what);
void adc_start();
void adc_set_channel(enum ADCChannel channel);
void adc_set_voltage_reference(enum VoltageReference vr);
void adc_set_prescaler(enum ADCPrescaler p);
uint16_t adc_get_value();
