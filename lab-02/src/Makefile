CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=cortex-m4 -mthumb

all: startup.o main.o

main.o : main.c
	$(CC) $(CFLAGS) $< -o $@

startup.o: startup.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f *.o