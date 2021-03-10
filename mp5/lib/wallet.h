#pragma once

#include <pthread.h>

typedef struct wallet_t_ {
  int clover;
  int clover4;
  int tool;
  int gem;
  int apple;
  int dna;
  int blue;
  int orange;
  int green;
  int books;
  int grad;
} wallet_t;

void wallet_init(wallet_t *wallet);
int wallet_get(wallet_t *wallet, const char *resource);
void wallet_change_resource(wallet_t *wallet, const char *resource, const int delta);
void wallet_destroy(wallet_t *wallet);
int* find_matching(wallet_t *wallet, const char *resource);