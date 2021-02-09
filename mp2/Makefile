FLAGS = -g -Wall
CC = gcc

LIBS = lib/crc32.c lib/png.c

all: png-analyze png-extractGIF png-hideGIF png-rewrite

png-analyze: png-analyze.c $(LIBS)
	$(CC) $^ $(FLAGS) -o $@

png-extractGIF: png-extractGIF.c $(LIBS)
	$(CC) $^ $(FLAGS) -o $@

png-hideGIF: png-hideGIF.c $(LIBS)
	$(CC) $^ $(FLAGS) -o $@

png-rewrite: png-rewrite.c $(LIBS)
	$(CC) $^ $(FLAGS) -o $@

clean:
	rm -rf png-analyze png-extractGIF png-hideGIF png-rewrite