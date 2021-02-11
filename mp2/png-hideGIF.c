#include <stdio.h>
#include <stdlib.h>
#include "lib/png.h"
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Usage: %s <PNG File> <GIF File> <New Filename>\n", argv[0]);
    return 1;
  }

  // Open the file specified in argv[1] for reading and argv[2] for writing:
  FILE *png = fopen(argv[1], "r");
  FILE *gif = fopen(argv[2], "r");
  FILE *out = fopen(argv[3], "w");
  size_t bytesWritten;

  // Read the PNG header, exiting if it is not a valid PNG:
  int result = PNGChunk_readHeader(png);
  if (result != 0) { fclose(png); return result; }

  PNGChunk *gifChunk = malloc(sizeof(PNGChunk));
  // Specify gifChunk
    // find size of file
  fseek(png, 0, SEEK_END);
  uint32_t gifLength= ftell(png);
  gifChunk->len = gifLength;

  bytesWritten = PNGChunk_writeHeader(out);
  printf("PNG Header written (%lu bytes)\n", bytesWritten); 
  // Read chunks until reaching "IEND" or in invalid chunk:
  while (1) {
    // Read chunk and ensure we get a valid result (exit on error):
    PNGChunk *chunk = PNGChunk_readChunk_alloc(png);
    if (chunk == NULL) { fclose(png); return 1; }

    // Report data about the chunk to the command line:
    bytesWritten = PNGChunk_writeChunk(out, chunk);
    printf("PNG chunk %s written (%lu bytes)\n", chunk->type, bytesWritten);

    // Check for the "IEND" chunk to exit:
    if ( strcmp(chunk->type, "IEND") == 0 ) {
      PNGChunk_free(chunk);
      break;  
    }

    // Free the memory associated with the chunk we just read:
    PNGChunk_free(chunk);
  }
  
  fclose(png);
  fclose(gif);
  fclose(out);
  return 0;
}
