#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "add_int.h"
#include "capitalize.h"
#include "emoji.h"

void part1() {
  int r;
  int *p1 = malloc(sizeof(int)), *p2 = malloc(sizeof(int));

  r = add_ints(4, 2);
  printf("add_ints: 4 + 2 = %d\n", r);

  *p1 = 42;
  r = add_intMixed(p1, 8);
  printf("add_intMixed: 42 + 8 = %d\n", r);

  *p1 = -3;
  *p2 = 6;
  r = add_intPtrs(p1, p2);
  printf("add_intPtrs: -3 + 6 = %d\n", r);

  int *ptr = add_ints_alloc(3, 5);
  printf("add_ints_alloc: 3 + 5 = %d\n", *ptr);
  free(ptr);

  free(p1);
  free(p2);
}

void part2() {
  char *s = malloc(100);

  strcpy(s, "hello!");
  printf("capitalize: \"%s\" -> ", s);
  capitalize(s);
  printf("\"%s\"\n", s);

  strcpy(s, "HI!");
  printf("capitalize: \"%s\" -> ", s);
  capitalize(s);
  printf("\"%s\"\n", s);

  strcpy(s, "hello");
  printf("capitalizeAll: \"%s\" -> ", s);
  capitalizeAll(s);
  printf("\"%s\"\n", s);

  strcpy(s, "hi cs240");
  printf("capitalizeAll: \"%s\" -> ", s);
  capitalizeAll(s);
  printf("\"%s\"\n", s);

  strcpy(s, "the quick brown fox jumped over the lazy red dog.");
  printf("capitalizeAll_alloc: \"%s\" -> ", s);
  char *s_alloc = capitalizeAll_alloc(s);
  printf("\"%s\"\n", s_alloc);
  free(s_alloc);

  free(s);
}

void part3() {
  char *s = malloc(100);

  const char *fav = emoji_favorite();
  printf("emoji_favorite: %s\n", fav);


  int ct;
  strcpy(s, "hi\xF0\x9F\x8E\x89");
  ct = emoji_count(s);
  printf("emoji_count: \"%s\" -> %d\n", s, ct);

  strcpy(s, "\xF0\x9F\x92\x96 \xF0\x9F\x92\xBB \xF0\x9F\x8E\x89");
  ct = emoji_count(s);
  printf("emoji_count: \"%s\" -> %d\n", s, ct);


  strcpy(s, "\xF0\x9F\x98\x8A");
  printf("emoji_invertChar: \"%s\" -> ", s);
  emoji_invertChar(s);
  printf("\"%s\"\n", s);

  strcpy(s, "\xF0\x9F\x92\x96 \xF0\x9F\x92\xBB \xF0\x9F\x8E\x89 \xF0\x9F\x98\x8A");
  printf("emoji_invertAll: \"%s\" -> ", s);
  emoji_invertAll(s);
  printf("\"%s\"\n", s);


  for (int i = 0; i < 10; i++) {
    char *s_alloc = emoji_random_alloc();
    printf("emoji_radnom_alloc (#%d): \"%s\"\n", (i+1), s_alloc);
    free(s_alloc);
  }

  free(s);
}


int main() {
  #ifdef PART1
  part1();
  #endif /* PART1 */

  #ifdef PART2
  part2();
  #endif /* PART2 */

  #ifdef PART3
  part3();
  #endif /* PART3 */
}
