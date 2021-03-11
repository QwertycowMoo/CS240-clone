#pragma once

#include <pthread.h>

typedef struct node_t {
  char* resource;
  int value;
  void* next;
  struct pthread_mutex_lock* lock;
} node_t;

typedef struct wallet_t_ {
  node_t* head;
  node_t* tail;
} wallet_t;

void wallet_init(wallet_t *wallet);
int wallet_get(wallet_t *wallet, const char *resource);
void wallet_change_resource(wallet_t *wallet, const char *resource, const int delta);
void wallet_destroy(wallet_t *wallet);
int* find_matching(wallet_t *wallet, const char *resource);
