#include <stdio.h>
#include <stdlib.h>
#include "lib/png.h"
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Usage: %s <PNG File>\n", argv[0]);
    return 1;
  }

  // Open the file specified in argv[1] for reading:
  FILE *f = fopen(argv[1], "r");
  //char *gifName = "";
  //strncpy(gifName, argv[1], strlen(argv[1] - 4));
  FILE *write = fopen(strcat(argv[1], ".gif"), "w");

   // Read the PNG header, exiting if it is not a valid PNG:
  int result;
  result = PNGChunk_readHeader(f);
  if (result != 0) { fclose(f); return result; }
  printf("PNG Header: OK\n");  

  PNGChunk *chunk;

  while(1) {
    // Read chunk and ensure we get a valid result (exit on error):
    chunk = PNGChunk_readChunk_alloc(f);
    if (chunk == NULL) { fclose(f); return 1; }

    if (strcmp(chunk->type, "uiuc") == 0) {
      break;
    }

    // Check for the "IEND" chunk to exit:
    if ( strcmp(chunk->type, "IEND") == 0 ) {
      PNGChunk_free(chunk);
      break;  
    }

    PNGChunk_free(chunk);
  }
  fclose(f);
  //We now have the uiuc chunk
  fwrite(chunk->data, sizeof(char), chunk->len, write);
  fclose(write);

  return 0;
}
