#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

#include "crc32.h"
#include "png.h"

const char PNG_FILE_FINGERPRINT[8] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };


int PNGChunk_readHeader(FILE *f) {
  // Read the first 8-bytes of the file:
  char buffer[8];
  size_t len = fread(buffer, sizeof(char), 8, f);

  // Ensure the first eight chars are a valid PNG file:
  if (len != 8 || memcmp(buffer, PNG_FILE_FINGERPRINT, len) != 0) {
    return 1;
  }

  return 0;
}


PNGChunk *PNGChunk_readChunk_alloc(FILE *f) {
  PNGChunk *chunk = malloc( sizeof(PNGChunk) );

  // Read the 4-byte length of the chunk:
  // - The value is always in "network byte order", which may differ from the "host byte order".
  // - `ntohl` converts "network byte order" to "host byte order" (if they differ).
  fread(&chunk->len, sizeof(uint32_t), 1, f);
  chunk->len = ntohl(chunk->len);

  // Read the 4-byte chunk type:
  // - The chunk type will always be ASCII and may be printed as a string.
  // - Therefore, a NULL byte is added at chunk->type[4] to terminate the string.
  fread(chunk->type, sizeof(char), 4, f);
  chunk->type[4] = 0;

  // Allocate and read the `chunk->len` bytes of data (or set the pointer to NULL if length is 0):
  if (chunk->len > 0) {
    chunk->data = malloc(chunk->len);
    fread(chunk->data, sizeof(char), chunk->len, f);
  } else {
    chunk->data = NULL;
  }

  // Finally, read the 4-byte CRC (using ntohl again to convert from network byte order to host byte order):
  fread(&chunk->crc, sizeof(uint32_t), 1, f);
  chunk->crc = ntohl(chunk->crc);

  return chunk;
}


size_t PNGChunk_writeHeader(FILE *f) {
  return fwrite(PNG_FILE_FINGERPRINT, sizeof(char), sizeof(PNG_FILE_FINGERPRINT), f);
}


size_t PNGChunk_writeChunk(FILE *f, PNGChunk *chunk) {
  size_t bytesWritten = 0;

  // Write the length in network byte order:
  uint32_t networkOrder_len = htonl(chunk->len);
  bytesWritten += fwrite(&networkOrder_len, sizeof(uint32_t), 1, f) * sizeof(uint32_t);

  // Write the byte type and data:
  bytesWritten += fwrite(chunk->type, sizeof(char), 4, f);
  bytesWritten += fwrite(chunk->data, sizeof(char), chunk->len, f);

  // Calculate the CRC:
  unsigned char *crcBuffer = malloc(4 + chunk->len);
  memcpy(crcBuffer, chunk->type, 4);
  memcpy(crcBuffer + 4, chunk->data, chunk->len);
  uint32_t crc = 0;
  crc32(crcBuffer, 4 + chunk->len, &crc);
  free(crcBuffer);

  // Write the CRC in network byte order:
  uint32_t networkOrder_crc = htonl(crc);
  bytesWritten += fwrite(&networkOrder_crc, sizeof(uint32_t), 1, f) * sizeof(uint32_t);

  return bytesWritten;
}


void PNGChunk_free(PNGChunk *chunk) {
  if (chunk) {
    free(chunk->data);
    free(chunk);
  }
}
