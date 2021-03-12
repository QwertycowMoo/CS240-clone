#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "wallet.h"

/**
 * Initalizes an empty wallet.
 */
void wallet_init(wallet_t *wallet) {
  //fprintf(stderr, "initialzing wallet\n");
  wallet->lock = malloc(sizeof(pthread_mutex_t));
  wallet->head = NULL;
  wallet->tail = wallet->head;
  pthread_mutex_init(wallet->lock, NULL);
}

/**
 * Returns the amount of a given `resource` in the given `wallet`.
 */
int wallet_get(wallet_t *wallet, const char *resource) {
  //fprintf(stderr, "trying to get %s", resource);
  
  node_t* node = wallet->head;
  while(node != NULL) {
    if(strcmp(resource, node->resource) == 0) {
      //fprintf(stderr, "match for %s", node->resource);
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
  pthread_mutex_lock(wallet->lock);
  node_t* node = wallet->head;
  while(node != NULL) {
    if(strcmp(node->resource, resource) == 0) {
      //fprintf(stderr, "at %s node\n", resource);
      break;
    }
    node = (node_t*) node->next;
  }
  //pthread_mutex_unlock(wallet->lock)
  if (node == NULL) {
    //fprintf(stderr, "trying to create a node for %s\n", resource);
    if (wallet->head == NULL) {
      //pthread_mutex_lock(wallet->lock);
      //fprintf(stderr, "head is null \n");
      wallet->head = (node_t*) malloc(sizeof(node_t));
      wallet->tail = wallet->head;
      wallet->tail->next = NULL;
      node = wallet->head;
      node->value = 0;
      node->resource = malloc(sizeof(char) * 20); //20 char limit on the name of the resource
      strcpy(node->resource, resource);
      ///fprintf(stderr, "created %s node \n", resource);
      //pthread_mutex_unlock(wallet->lock); 
    } else {
      //we don't have this resource yet
      //pthread_mutex_lock(wallet->lock);
      wallet->tail->next = malloc(sizeof(node_t));
      wallet->tail = wallet->tail->next;
      wallet->tail->next = NULL;
      node = wallet->tail;
      node->value = 0;
      node->resource = malloc(sizeof(char) * 20); //20 char limit on the name of the resource
      strcpy(node->resource, resource);
      //fprintf(stderr, "created %s node", resource);
      //pthread_mutex_unlock(wallet->lock); 
      
      //value management is done after
    }
    
  }
  pthread_mutex_unlock(wallet->lock);
  if (delta < 0) {
    pthread_mutex_lock(wallet->lock);
    if (delta < node->value) {
      pthread_mutex_unlock(wallet->lock);
      //fprintf(stderr, "inside a loop for %s", node->resource);
      while(1) {
        pthread_mutex_lock(wallet->lock);
        if (node->value >= delta) {
          node->value = node->value + delta;
          pthread_mutex_unlock(wallet->lock);
	  break;
        }
        pthread_mutex_unlock(wallet->lock);
      }
    } else {
      node->value = node->value + delta;
      pthread_mutex_unlock(wallet->lock);
    }
  } else {
    pthread_mutex_lock(wallet->lock);
    node->value = node->value + delta;
    pthread_mutex_unlock(wallet->lock);
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
  pthread_mutex_destroy(wallet->lock);
  free(wallet->lock);
}
