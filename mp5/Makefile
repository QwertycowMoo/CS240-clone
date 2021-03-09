CC = gcc
INC = -I.
FLAGS = -W -Wall -g
LINKOPTS = -pthread

all: degree

wallet.o: lib/wallet.c
	$(CC) -Ilib -W -Wall -g -c lib/wallet.c -o wallet.o

degree: degree.c wallet.o
	$(CC) $(INC) $(FLAGS) $(LINKOPTS) wallet.o degree.c -o degree

clean:
	rm -rf wallet.o degree