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
  int count;
  for(size_t i = 0; i < strlen(utf8str); i++) {
    if (utf8str[i] >= 3 && utf8str[i] <= 1000) {
      //"\xF0\x9F\x00\x00"  "\xF0\x9F\xA7\xBF"
      count++;
    }
  }
  return count;
}


// Modify the UTF-8 string `utf8str` to invert ONLY the FIRST UTF-8 character (which may be up to 4 bytes)
// in the string if the first character is an emoji.  At a minimum:
// - Invert "😊" U+1F60A ("\xF0\x9F\x98\x8A") into a non-smiling face.
// - Choose at least five more emoji to invert.
void emoji_invertChar(char *utf8str) {

}


// Modify the UTF-8 string `utf8str` to invert ALL of the character by calling your
// `emoji_invertChar` function on each character.
void emoji_invertAll(char *utf8str) {

}


// Return a random emoji stored in new heap memory you have allocated.
char *emoji_random_alloc() {
  return "";
}
