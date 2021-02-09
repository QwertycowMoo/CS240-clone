#include <stdio.h>
#include <string.h>

#include "lib/png.h"

int main(int argc, char *argv[]) {
  // Ensure the correct number of arguments:
  if (argc != 2) {
    printf("Usage: %s <PNG File>\n", argv[0]);
    return 1;
  }


  // Open the file specified in argv[1] for reading:
  FILE *f = fopen(argv[1], "r");


  // Read the PNG header, exiting if it is not a valid PNG:
  int result;
  result = PNGChunk_readHeader(f);
  if (result != 0) { fclose(f); return result; }
  printf("PNG Header: OK\n");  


  // Read chunks until reaching "IEND" or in invalid chunk:
  while (1) {
    // Read chunk and ensure we get a valid result (exit on error):
    PNGChunk *chunk = PNGChunk_readChunk_alloc(f);
    if (chunk == NULL) { fclose(f); return 1; }

    // Report data about the chunk to the command line:
    printf("Chunk: %s (%d bytes of data)\n", chunk->type, chunk->len);

    // Check for the "IEND" chunk to exit:
    if ( strcmp(chunk->type, "IEND") == 0 ) {
      PNGChunk_free(chunk);
      break;  
    }

    // Free the memory associated with the chunk we just read:
    PNGChunk_free(chunk);
  }


  fclose(f);
  return 0;
}