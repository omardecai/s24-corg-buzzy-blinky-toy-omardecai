#makefile configuration
Common_objects = main.o
CPU	       = msp430g2553
CFLAGS 	       = -mmcu=${CPU} -I../h


#switch the compiler (for the internal make rules)
CC		= msp430-elf-gcc
AS		= msp430-elf-as

all: led-c.elf led-s.elf

clean:
	rm -f *.o *.elf
