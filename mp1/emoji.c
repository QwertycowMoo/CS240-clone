#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Return your favorite emoji.
// (This should really be your favorite one, we may use this later in the semester. :))
const char *emoji_favorite() {
  return "\xF0\x9F\x9A\x80";
}


// Count the number of emoji in the UTF-8 string `utf8str`, returning the count.  You should
// consider everything in the ranges starting from (and including) U+1F000 up to (and including) U+1F9FF.
int emoji_count(char *utf8str) {
  int count = 0;
  for(size_t i = 0; i < strlen(utf8str); i++) {
    if (utf8str[i] == '\xF0') {
      i++;
      if (utf8str[i] == '\x9F') {
        i++;
        if (utf8str[i] > '\x80' && utf8str[i] < '\xFA'){
          i++;
          count++;
        }
        if (utf8str[i] == '\x80') {
          i++;
          if (utf8str[i] >= '\x80'){
            count++;
          }
        }
        if (utf8str[i] == '\xA7') {
          i++;
          if (utf8str[i] <= '\xBF'){
            count++;
          }
        }
      }
    }
  }
  return count;
}


// Modify the UTF-8 string `utf8str` to invert ONLY the FIRST UTF-8 character (which may be up to 4 bytes)
// in the string if the first character is an emoji.  At a minimum:
// - Invert "😊" U+1F60A ("\xF0\x9F\x98\x8A") into a non-smiling face.
// - Choose at least five more emoji to invert.
void emoji_invertChar(char *utf8str) {
  // - Invert "😊" U+1F60A ("\xF0\x9F\x98\x8A") into a non-smiling face 😔.
  if (utf8str[0] == '\xF0' && utf8str[1] == '\x9F' && utf8str[2] == '\x98' && utf8str[3] == '\x8A') {
    utf8str[3] = '\x9E';
  }
  // Inverts 💕 into 💔
  if (utf8str[0] == '\xF0' && utf8str[1] == '\x9F' && utf8str[2] == '\x92' && utf8str[3] == '\x95') {
    utf8str[3] = '\x94';
  }

  // Inverts 🚀 into 📉 

  if (utf8str[0] == '\xF0' && utf8str[1] == '\x9F' && utf8str[2] == '\x9A' && utf8str[3] == '\x80') {
    utf8str[2] = '\x93';
    utf8str[3] = '\x89';
  }

  // Inverts American Flag into Russian Flag
  if (utf8str[0] == '\xF0' && utf8str[1] == '\x9F' && utf8str[2] == '\x87' && utf8str[3] == '\xBA') {
    utf8str[3] = '\xB7';
  }

  // Inverts 😍 into 😢
  if (utf8str[0] == '\xF0' && utf8str[1] == '\x9F' && utf8str[2] == '\x98' && utf8str[3] == '\x8D') {
    utf8str[3] = '\xA2';
  }
  
   // Inverts 🍎 into 🍏
  if (utf8str[0] == '\xF0' && utf8str[1] == '\x9F' && utf8str[2] == '\x8D' && utf8str[3] == '\x8E') {
    utf8str[3] = '\x8F';
  }
}


// Modify the UTF-8 string `utf8str` to invert ALL of the character by calling your
// `emoji_invertChar` function on each character.
void emoji_invertAll(char *utf8str) {
  for (size_t i = 0; i < sizeof(utf8str); i++) {
    printf("%d \n", utf8str[i]);
    emoji_invertChar(&utf8str[i]);
  }
}


// Return a random emoji stored in new heap memory you have allocated.
char *emoji_random_alloc() {
  char *result = malloc(4);
  char byte1 = (rand() % 40) + 128;
  char byte2 = (rand() % 64) + 128;
  result[1] = '\xF0';
  result[2] = '\x9F';
  result[3] = byte1;
  result[4] = byte2;
  printf("result: %s \n", result);
  return result;
}
