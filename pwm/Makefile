AVR_TOOLS_PATH=${HOME}/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/bin/
# Compilatore https://linux.die.net/man/1/avr-gcc
# Avr-libc https://www.nongnu.org/avr-libc/user-manual/index.html
AVR_CC=${AVR_TOOLS_PATH}avr-gcc
# Gestore archivi librerie https://linux.die.net/man/1/avr-ar
AVR_AR=${AVR_TOOLS_PATH}avr-gcc-ar
# Convertitore di formati https://linux.die.net/man/1/avr-objcopy
AVR_OBJCOPY=${AVR_TOOLS_PATH}avr-objcopy
# Mostra le informazioni sull'eseguibile https://linux.die.net/man/1/avr-size
AVR_SIZE=${AVR_TOOLS_PATH}avr-size
# Programma per trasferire l'eseguibile su arduino https://linux.die.net/man/1/avrdude
AVRDUDE=${HOME}/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/bin/avrdude

# Imposta i percorsi di ricerca degli include
INCLUDE=${HOME}/.arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino5/avr/include/

# Opzioni compilatore
# -Os ottimizza per dimensione eseguibile, 0 disabilita
# -DF_CPU comunica con un define la frequenza della cpu
# -mmcu comunica la cpu utilizzata
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=atmega328p -I${INCLUDE} # rimosso -O0 per delay.h

# Opzioni avrdude

# Definisce la porta di caricamento
PORT=/dev/ttyUSB0

# Configurazione di avrdude
AVRDUDE_CONF=${HOME}/.arduino15/packages/arduino/tools/avrdude/6.3.0-arduino17/etc/avrdude.conf

# Opzioni avrdude
# -C file di configurazione
# -v verbose
# -p atmega328p tipo di micro
# -c arduino tipo di programmatore
# -P /dev/ttyUSB0 porta
# -b 115200 velocità di trasmissione
# -D disabilita la auto cancellazione della memoria
# -Uflash:w:main.hex:i specifica il tipo di operazione da fare sulla memoria, file, formato i = intel hex
AVRDUDE_FLAGS=-C${AVRDUDE_CONF} -v -p atmega328p -c arduino -P ${PORT} -b 115200 -D -U flash:w:main.hex:i


main.hex: main.elf
	${AVR_OBJCOPY} -O ihex -R .eeprom main.elf main.hex
	${AVR_SIZE} -C --mcu=atmega328p  main.elf

main.elf: main.c pwm.c usart.c
	${AVR_CC} ${CFLAGS} -o main.elf main.c pwm.c usart.c

install: main.hex
	${AVRDUDE} ${AVRDUDE_FLAGS}


