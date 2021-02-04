#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Modify the string `s` to capitalize the first letter of the string if the first letter of `s`
// is lower case.  Otherwise, do nothing.
void capitalize(char *s) {
  //65 is A, 65 + 32 = 97 is a
  if (s[0] >= 97 && s[0] <= 122) {
    s[0] -= 32;
  }
}


// Modify the string `s` to capitalize ALL of the lower case letters in `s`.  If the letter
// is not lower case, do nothing.  (You can assume you will be given only ASCII characters.)
void capitalizeAll(char *s) {
  size_t len = sizeof(s) / sizeof(char);
  for(size_t i = 0; i < len; i++) {
    if (s[i] >= 97 && s[i] <= 122) {
      s[i] -= 32;
    }
  }
}


// Return a new string (allocated in heap memory that you allocate) that transforms `s` in
// the same way as `capitalizeAll`.  (In this function, `s` cannot be modified directly and
// must be done in the new memory you will allocate.)
char *capitalizeAll_alloc(const char *s) {
  size_t len = strlen(s);
  char *result = malloc(sizeof(char) * len);
  for(size_t i = 0; i < len; i++) {
    if (s[i] >= 97 && s[i] <= 122) {
      result[i] = s[i] - 32;
    } else {
      result[i] = s[i];
    }
  }
  return result;
}
