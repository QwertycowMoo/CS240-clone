#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wallet.h"


/**
 * Initalizes an empty wallet.
 */
void wallet_init(wallet_t *wallet) {
  //pthread_mutex_init(&wallet->lock, NULL);
  wallet->clover = 0;
  wallet->clover4 = 0;
  wallet->tool = 0;
  wallet->gem = 0;
  wallet->apple = 0;
  wallet->dna = 0;
  wallet->blue = 0;
  wallet->orange = 0;
  wallet->green = 0;
  wallet->books = 0;
  wallet->grad = 0;
  printf("Wallet pointer: %p \n", wallet);
  }
/**
  *
  */
int* find_matching(wallet_t *wallet, const char *resource) {
  if (strcmp(resource, "clover") == 0) {
    return &wallet->clover;
  } else if (strcmp(resource, "four-leaf-clover") == 0){
    return &wallet->clover4;
  }
  else if (strcmp(resource, "tools") == 0){
    return &wallet->tool;
  }
  else if (strcmp(resource, "gem") == 0){
    return &wallet->gem;
  }
  else if (strcmp(resource, "green-apple") == 0){
    return &wallet->apple;
  }
  else if (strcmp(resource, "dna") == 0){
    return &wallet->dna;
  }
 else if (strcmp(resource, "green-book") == 0){
    return &wallet->green;
  }
  else if (strcmp(resource, "blue-book") == 0){
    return &wallet->blue;
  }
  else if (strcmp(resource, "orange-book") == 0){
    return &wallet->orange;
  }
  else if (strcmp(resource, "books") == 0){
    return &wallet->books;
  }
  else if (strcmp(resource, "degree!") == 0){
    return &wallet->grad;
  }
  return NULL;
}
/**
 * Returns the amount of a given `resource` in the given `wallet`.
 */
int wallet_get(wallet_t *wallet, const char *resource) {
  //we need a dictionary we're just gonna loop through all the possible things and string compare I don't feel like doing a dictionary implementation
  return *find_matching(wallet, resource);
}

/**
 * Modifes the amount of a given `resource` in a given `wallet by `delta`.
 * - If `delta` is negative, this function MUST NOT RETURN until the resource can be satified.
 *   (Ths function MUST WAIT until the wallet has enough resources to satisfy the request;
 *    there are several ways to accomplish this waiting and it does not have to be fancy.)
 */
void wallet_change_resource(wallet_t *wallet, const char *resource, const int delta) {
  if (delta < 0) {
    if (wallet_get(wallet, resource) < delta) {
      //wait
      // pthread_mutex_lock(&wallet->lock, NULL);
      //this is the hard part
    } else {
      *find_matching(wallet, resource) = *find_matching(wallet, resource) + delta;
    }
  } else {
    *find_matching(wallet, resource) = *find_matching(wallet, resource) + delta;
  }
}

/**
 * Destroys a wallet, freeing all associated memory.
 */
void wallet_destroy(wallet_t *wallet) {
  printf("Wallet pointer: %p", wallet);
}
