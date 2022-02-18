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
#define BOOL uint8_t
#endif
#define USART_BUF_SIZE 20
#define  USART_LAST_CHAR '\n'

void usart_init(uint32_t baud_rate);
BOOL usart_complete();
void usart_get_str(char *s);
void usart_send_char(uint8_t c);
/*void usart_send_char(uint8_t c);
void usart_send_str(unsigned char *s);
void usart_send_strn(unsigned char *s);
uint8_t usart_char_ispresent(void);
unsigned char usart_get_char(void);
*/
