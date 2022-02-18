/* 	*************************************************
	Giancarlo Martini 2020/06/26
	Semplice esempio d'uso della seriale (usart)
	usart.h
	email:gm@giancarlomartini.it
	http:www.giancarlomartini.it
	***********************************************/
#ifndef TRUE
#define TRUE	1
#define FALSE 0
#endif

void usart_init(uint32_t baud_rate);
void usart_send_char(uint8_t c);
void usart_send_str(unsigned char *s);
void usart_send_strn(unsigned char *s);
uint8_t usart_char_ispresent(void);
unsigned char usart_get_char(void);
