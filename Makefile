CC=gcc
CFLAGS=-I.

current_dir = $(shell pwd)

$(info starting make)
$(info current working directory: ${current_dir})

generate_priv_key: generate_priv_key.c
	$(CC) -O0 -Wall -Wextra -g -o generate_priv_key.o generate_priv_key.c -lssl -lcrypto

read_random: read_random.c
	$(CC) -O0 -Wall -Wextra -g -o read_random.o read_random.c

clean:
	rm -f *.o
