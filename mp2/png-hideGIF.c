#include <stdio.h>
#include <stdlib.h>
#include "lib/png.h"
#include <string.h>


//./png-hideGIF 240.png taylor.gif 240_gif.png
// gif is uiuc written (3044155 bytes)
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



  //get size of the gif
  fseek(gif, 0, SEEK_END);
  uint32_t gifLength= ftell(gif);
  if (gifLength == -1) {
    printf("Something wrong with gifLength");
  }
  gifChunk->len = gifLength;
  printf("The gif has %u bytes \n", gifLength);

  //setup the chunk
  strcpy(gifChunk->type, "uiuc");
  gifChunk->data = malloc(gifChunk->len);

  //since we used fseek to get the size of the file, we have to put the stream back to the beginning
  if (fseek(gif, 0, SEEK_SET) != 0) {
    printf("Something wrong with fseek");
  }
  //put data into chunk
  fread(gifChunk->data, sizeof(char), gifChunk->len, gif);

  printf("gifChunk data size: %ld \n", sizeof(gifChunk->data));

  bytesWritten = PNGChunk_writeHeader(out);
  printf("PNG Header written (%lu bytes)\n", bytesWritten); 

  // Read chunks until IEND then insert the gifChunk before it
  while (1) {
    // Read chunk and ensure we get a valid result (exit on error):
    PNGChunk *chunk = PNGChunk_readChunk_alloc(png);

   
    if (chunk == NULL) { fclose(png); return 1; }

    // Check for the "IEND" chunk to insert the gifChunk:
    if ( strcmp(chunk->type, "IEND") == 0 ) {
      //write the uiuc chunk
      bytesWritten = PNGChunk_writeChunk(out, gifChunk);
      printf("PNG chunk %s written (%lu bytes)\n", gifChunk->type, bytesWritten);

      //then write the IEND chunk
      bytesWritten = PNGChunk_writeChunk(out, chunk);
      printf("PNG chunk %s written (%lu bytes)\n", chunk->type, bytesWritten);

      PNGChunk_free(chunk);
      break;  
    }
    // Report data about the chunk to the command line:
    bytesWritten = PNGChunk_writeChunk(out, chunk);
    printf("PNG chunk %s written (%lu bytes)\n", chunk->type, bytesWritten);
    
    
  // Check for the "IEND" chunk to insert the gifChunk:
    if ( strcmp(chunk->type, "IEND") == 0 ) {
      PNGChunk_free(chunk);
      break;  
    }

    // Free the memory associated with the chunk we just read:
    PNGChunk_free(chunk);
  }
  
  PNGChunk_free(gifChunk);
  fclose(png);
  fclose(gif);
  fclose(out);
  return 0;
}
