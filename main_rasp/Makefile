CC = gcc
CFLAGS = -Wall -lwiringPi

OBJS = main.o lcd.o pir.o dust.o adc.o motor.o

all: main

main: $(OBJS)
	$(CC) -o main $(OBJS) $(CFLAGS)

main.o: main.c lcd.h pir.h dust.h adc.h motor.h
	$(CC) -c main.c $(CFLAGS)

lcd.o: lcd.c lcd.h
	$(CC) -c lcd.c $(CFLAGS)

pir.o: pir.c pir.h
	$(CC) -c pir.c $(CFLAGS)

dust.o: dust.c dust.h
	$(CC) -c dust.c $(CFLAGS)

adc.o: adc.c adc.h
	$(CC) -c adc.c $(CFLAGS)

motor.o: motor.c motor.h
	$(CC) -c motor.c $(CFLAGS)

clean:
	rm -f *.o main