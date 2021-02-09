#pragma once

#include <stdint.h>

// Struct:
struct _PNGChunk {
  uint32_t len;
  char type[5];
  unsigned char *data;
  uint32_t crc;
};
typedef struct _PNGChunk PNGChunk;

// Reading PNG:
int PNGChunk_readHeader(FILE *f);
PNGChunk *PNGChunk_readChunk_alloc(FILE *f);

// Writing PNG:
size_t PNGChunk_writeHeader(FILE *f);
size_t PNGChunk_writeChunk(FILE *f, PNGChunk *chunk);

// Memory Free:
void PNGChunk_free(PNGChunk *chunk);
