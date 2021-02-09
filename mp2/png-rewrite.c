#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lib/png.h"

int main(int argc, char *argv[]) {
  // Ensure the correct number of arguments:
  if (argc != 3) {
    printf("Usage: %s <SOURCE PNG> <DEST PNG>\n", argv[0]);
    return 1;
  }


  // Open the file specified in argv[1] for reading and argv[2] for writing:
  FILE *f = fopen(argv[1], "r");
  FILE *out = fopen(argv[2], "w");
  size_t bytesWritten;


  // Read the PNG header, exiting if it is not a valid PNG:
  int result = PNGChunk_readHeader(f);
  if (result != 0) { fclose(f); return result; }

  bytesWritten = PNGChunk_writeHeader(out);
  printf("PNG Header written (%lu bytes)\n", bytesWritten);
 

  // Read chunks until reaching "IEND" or in invalid chunk:
  while (1) {
    // Read chunk and ensure we get a valid result (exit on error):
    PNGChunk *chunk = PNGChunk_readChunk_alloc(f);
    if (chunk == NULL) { fclose(f); return 1; }

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
  
  fclose(f);
  fclose(out);
  return 0;
}