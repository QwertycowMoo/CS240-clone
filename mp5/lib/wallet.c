#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wallet.h"

pthread_mutex_t lock;
/**
 * Initalizes an empty wallet.
 */
void wallet_init(wallet_t *wallet) {
  fprintf(stderr, "initialzing wallet\n");
  wallet->head = NULL;
  wallet->tail = wallet->head;
}

/**
 * Returns the amount of a given `resource` in the given `wallet`.
 */
int wallet_get(wallet_t *wallet, const char *resource) {
  node_t* node = wallet->head;
  while(node) {
    if(strcmp(resource, node->resource) == 0) {
      return node->value;
    }
    node = (node_t*) node->next;
  }
  return 0;
}

/**
 * Modifes the amount of a given `resource` in a given `wallet by `delta`.
 * - If `delta` is negative, this function MUST NOT RETURN until the resource can be satified.
 *   (Ths function MUST WAIT until the wallet has enough resources to satisfy the request;
 *    there are several ways to accomplish this waiting and it does not have to be fancy.)
 */
void wallet_change_resource(wallet_t *wallet, const char *resource, const int delta) {
  node_t* node = wallet->head;
  while(node != NULL) {
    //pthread_mutex_lock(&lock);
    if(strcmp(node->resource, resource) == 0) {
      //fprintf(stderr, "at %s node\n", resource);
      //pthread_mutex_unlock(&lock);
      break;
    }
    node = (node_t*) node->next;
    //pthread_mutex_unlock(&lock);
  }
  if (node == NULL) {
    //fprintf(stderr, "trying to create a node for %s\n", resource);
    if (wallet->head == NULL) {
      pthread_mutex_lock(&lock);
      //fprintf(stderr, "head is null \n");
      wallet->head = (node_t*) malloc(sizeof(node_t));
      wallet->tail = wallet->head;
      wallet->tail->next = NULL;
      node = wallet->head;
      node->value = 0;
      node->resource = malloc(sizeof(char) * 20); //20 char limit on the name of the resource
      strcpy(node->resource, resource);
      //fprintf(stderr, "created %s node \n", resource);
      pthread_mutex_unlock(&lock); 
    } else {
      //we don't have this resource yet
      pthread_mutex_lock(&lock);
      wallet->tail->next = malloc(sizeof(node_t));
      wallet->tail = wallet->tail->next;
      wallet->tail->next = NULL;
      node = wallet->tail;
      node->value = 0;
      node->resource = malloc(sizeof(char) * 20); //20 char limit on the name of the resource
      strcpy(node->resource, resource);
      //fprintf(stderr, "created %s node", resource);
      pthread_mutex_unlock(&lock); 
      
      //value management is done before
    }
    
  }
  if (delta < 0) {
    if (delta < node->value) {
      while(1) {
        if (node->value >= delta) {
          pthread_mutex_lock(&lock);
          node->value = node->value + delta;
          pthread_mutex_unlock(&lock);
        }
      }
    } else {
      pthread_mutex_lock(&lock);
      node->value = node->value + delta;
      pthread_mutex_unlock(&lock);
    }
  } else {
    pthread_mutex_lock(&lock);
    node->value = node->value + delta;
    pthread_mutex_unlock(&lock);
  }

  //fprintf(stderr, "%s now hasd %d \n", node->resource, node->value);
}

/**
 * Destroys a wallet, freeing all associated memory.
 */
void wallet_destroy(wallet_t *wallet) {
  node_t* to_free = wallet->head;
  while(to_free) {
    node_t* temp = to_free->next;
    free(to_free->resource);
    free(to_free);
    to_free = temp;
  }
}
