CC = gcc
CFLAGS = -Wall -Wextra
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

all: 
	$(CC) $(CFLAGS) -o client dgram_socket_client.c
	$(CC) $(CFLAGS) -o server demo_socket.c

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:	
	rm -f *.o *.elf client server

