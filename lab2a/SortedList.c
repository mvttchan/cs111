//NAME: Matthew Chan
//EMAIL: matthew_2185@yahoo.com
//ID: 805291212

#include "SortedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

void SortedList_insert(SortedList_t *list, SortedListElement_t *element) {
  if(list == NULL || element == NULL) return;
  SortedListElement_t *current_node = list->next;
  while(current_node != list) {
    //if element's key is less than current node key, insert here
    if(element->key < current_node->key) {
      break;
    }
    current_node = current_node->next;
  }
  if(opt_yield & INSERT_YIELD) sched_yield();
  element->next = current_node;
  element->prev = current_node->prev;
  current_node->prev->next = element;
  current_node->prev = element;
}

int SortedList_delete(SortedListElement_t *element) {
  if(element == NULL || element->key == NULL || element->prev->next != element || element->next->prev != element) return 1;
  if(opt_yield & DELETE_YIELD) sched_yield();
  element->prev->next = element->next;
  element->next->prev = element->prev;
  return 0;
}

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key) {
  if(list == NULL || key == NULL) return NULL;
  SortedListElement_t *current_node = list;
  do {
    if(current_node->key == key) return current_node;
    if(opt_yield & LOOKUP_YIELD) sched_yield();
    current_node = current_node->next;
  } while(current_node != list);
  return NULL;
}

int SortedList_length(SortedList_t *list) {
  if(list == NULL) return -1;
  int length = 0;
  SortedListElement_t *current_node = list->next;
  while(current_node != list) {
    //no need to check node->next because we'll get to it
    if(current_node == NULL || current_node->prev == NULL) return -1;
    if(current_node->prev->next != current_node || current_node->next->prev != current_node) return -1;
    ++length;
    if(opt_yield & LOOKUP_YIELD) sched_yield();
    current_node = current_node->next;
  }
  return length;
}
