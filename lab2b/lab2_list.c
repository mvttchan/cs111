//NAME: Matthew Chan
//EMAIL: matthew_2185@yahoo.com
//ID: 805291212

#include "SortedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <signal.h>

pthread_mutex_t* mutex;
int* spin_lock;

int opt_yield = 0;
int threads = 1;
int iterations = 1;
int list_count = 1;
int sync_flag = 0;
char* yieldopts;
char* syncopts = "none";
long long lock_wait = 0;

SortedList_t* list;
SortedListElement_t* elements;
int element_count;

#define ID_YIELD 0X03
#define IL_YIELD 0x05
#define DL_YIELD 0x06
#define IDL_YIELD 0x07

void segfault_handler() {
  fprintf(stderr, "Segfault found\n");
  exit(2);
}

void* thread_worker(void* startaddress) {
  int i;
  int length;
  int delete_value;
  SortedListElement_t* offset = startaddress;
  SortedListElement_t* delete_key;
  struct timespec start_time, end_time;
  int hash_val;
  //insert
  switch(sync_flag) {
  case 0:
    //unprotected
    for(i = 0; i < iterations; ++i) {
      hash_val = (*((offset[i].key))%list_count);
      SortedList_insert(&list[hash_val], &offset[i]);
    }
    for(i = 0; i < iterations; ++i) {
      hash_val = (*((offset[i].key))%list_count);
      if(SortedList_length(&list[hash_val]) == -1) {
	fprintf(stderr, "Corrupted list, unprotected length\n");
	exit(2);
      }
    }
    for(i = 0; i < iterations; ++i) {
      hash_val = (*((offset[i].key))%list_count);
      if((delete_key = SortedList_lookup(&list[hash_val], offset[i].key)) == NULL) {
	fprintf(stderr, "Corrupted list, unprotected look up\n");
	exit(2);
      }
      if(SortedList_delete(delete_key) != 0) {
	fprintf(stderr, "Corrupted list, unprotected delete\n");
	exit(2);
      }
    }
    break;
  case 1:
    //mutex
    for(i = 0; i < iterations; ++i) {
      hash_val = (*((offset[i].key))%list_count);
      clock_gettime(CLOCK_MONOTONIC, &start_time);
      pthread_mutex_lock(&mutex[hash_val]);
      clock_gettime(CLOCK_MONOTONIC, &end_time);
      lock_wait += ((end_time.tv_sec - start_time.tv_sec) * 1000000000) + (end_time.tv_nsec - start_time.tv_nsec);
      SortedList_insert(&list[hash_val], &offset[i]);
      pthread_mutex_unlock(&mutex[hash_val]);
    }
    for(i = 0; i < iterations; ++i) {
      hash_val = (*((offset[i].key))%list_count);
      clock_gettime(CLOCK_MONOTONIC, &start_time);
      pthread_mutex_lock(&mutex[hash_val]);
      clock_gettime(CLOCK_MONOTONIC, &end_time);
      lock_wait += ((end_time.tv_sec - start_time.tv_sec) * 1000000000) + (end_time.tv_nsec - start_time.tv_nsec);
      length = SortedList_length(&list[hash_val]);
      pthread_mutex_unlock(&mutex[hash_val]);
      if(length == -1) {
        fprintf(stderr, "Corrupted list, unprotected length\n");
        exit(2);
      }
    }
    for(i = 0; i < iterations; ++i) {
      hash_val = (*((offset[i].key))%list_count);
      clock_gettime(CLOCK_MONOTONIC, &start_time);
      pthread_mutex_lock(&mutex[hash_val]);
      clock_gettime(CLOCK_MONOTONIC, &end_time);
      lock_wait += ((end_time.tv_sec - start_time.tv_sec) * 1000000000) + (end_time.tv_nsec - start_time.tv_nsec);
      delete_key = SortedList_lookup(&list[hash_val], offset[i].key);
      //      pthread_mutex_unlock(&mutex);
      if(delete_key == NULL) {
        fprintf(stderr, "Corrupted list, unprotected look up\n");
        exit(2);
      }
      //pthread_mutex_lock(&mutex);
      delete_value = SortedList_delete(delete_key);
      //pthread_mutex_unlock(&mutex);
      if(delete_value != 0) {
        fprintf(stderr, "Corrupted list, unprotected delete\n");
        exit(2);
      }
      pthread_mutex_unlock(&mutex[hash_val]);
    }
    break;
  case 2:
    //spinlock
    for(i = 0; i < iterations; ++i) {
      hash_val = (*((offset[i].key))%list_count);
      clock_gettime(CLOCK_MONOTONIC, &start_time);
      while(__sync_lock_test_and_set(&spin_lock[hash_val], 1));
      clock_gettime(CLOCK_MONOTONIC, &end_time);
      lock_wait += ((end_time.tv_sec - start_time.tv_sec) * 1000000000) + (end_time.tv_nsec - start_time.tv_nsec);
      SortedList_insert(&list[hash_val], &offset[i]);
      __sync_lock_release(&spin_lock[hash_val]);
    }
    for(i = 0; i < iterations; ++i) {
      hash_val = (*((offset[i].key))%list_count);
      clock_gettime(CLOCK_MONOTONIC, &start_time);
      while(__sync_lock_test_and_set(&spin_lock[hash_val], 1));
      clock_gettime(CLOCK_MONOTONIC, &end_time);
      lock_wait += ((end_time.tv_sec - start_time.tv_sec) * 1000000000) + (end_time.tv_nsec - start_time.tv_nsec);
      length = SortedList_length(&list[hash_val]);
      __sync_lock_release(&spin_lock[hash_val]);
      if(length == -1) {
        fprintf(stderr, "Corrupted list, unprotected length\n");
        exit(2);
      }
    }
    for(i = 0; i < iterations; ++i) {
      hash_val = (*((offset[i].key))%list_count);
      clock_gettime(CLOCK_MONOTONIC, &start_time);
      while(__sync_lock_test_and_set(&spin_lock[hash_val], 1));
      clock_gettime(CLOCK_MONOTONIC, &end_time);
      lock_wait += ((end_time.tv_sec - start_time.tv_sec) * 1000000000) + (end_time.tv_nsec - start_time.tv_nsec);
      delete_key = SortedList_lookup(&list[hash_val], offset[i].key);
      //      __sync_lock_release(&spin_lock);
      if(delete_key == NULL) {
        fprintf(stderr, "Corrupted list, unprotected look up\n");
        exit(2);
      }
      //      while(__sync_lock_test_and_set(&spin_lock, 1));
      delete_value = SortedList_delete(delete_key);
      //      __sync_lock_release(&spin_lock);
      if(delete_value != 0) {
        fprintf(stderr, "Corrupted list, unprotected delete\n");
        exit(2);	
      }
      __sync_lock_release(&spin_lock[hash_val]);
    }
    break;
  default:
    fprintf(stderr, "Shouldn't reach this point\n");
    exit(2);
  }
  
  return NULL;
}

int main(int argc, char* argv[]) {

  signal(SIGSEGV, segfault_handler);
  int index_yield = 0;
  int len;
  struct option options[] = {
    {"threads", 1, NULL, 't'},
    {"iterations", 1, NULL, 'i'},
    {"yield", 1, NULL, 'y'},
    {"sync", 1, NULL, 's'},
    {"lists", 1, NULL, 'l'},
    {0,0,0,0}
  };

  int c;
  while((c = getopt_long(argc, argv, "", options, NULL)) != -1) {
    switch(c) {
    case 't':
      threads = atoi(optarg);
      break;
    case 'i':
      iterations = atoi(optarg);
      break;
    case 'y':
      //      opt_yield = 1;
      len = strlen(optarg);
      if(len > 3) {
	fprintf(stderr, "Yield can only have idl options\n");
	exit(1);
      }
      for(index_yield = 0; index_yield < len; ++index_yield) {
	switch(optarg[index_yield]) {
	case 'i':
	  opt_yield |= INSERT_YIELD;
	  break;
	case 'd':
	  opt_yield |= DELETE_YIELD;
	  break;
	case 'l':
	  opt_yield |= LOOKUP_YIELD;
	  break;
	default:
	  fprintf(stderr, "Yield only recognizes idl arguments\n");
	  exit(1);
	}
      }
      break;
    case 's':
      switch(optarg[0]) {
      case 'm':
	sync_flag = 1;
	syncopts = "m";
	break;
      case 's':
	sync_flag = 2;
	syncopts = "s";
	break;
      default:
	fprintf(stderr, "Only m and s are recognized sync options\n");
	exit(1);
      }
      break;
    case 'l':
      list_count = atoi(optarg);
      break;
    default:
      fprintf(stderr, "Unrecognized argument\n");
      exit(1);
    }
  }

  int index_lock;
  if(sync_flag == 1) {
    mutex = malloc(list_count * sizeof(pthread_mutex_t));
    for(index_lock = 0; index_lock < list_count; ++index_lock) {
      pthread_mutex_init(&mutex[index_lock], NULL);
    }
  }
  else if(sync_flag == 2) {
    spin_lock = malloc(list_count * sizeof(int));
    for(index_lock = 0; index_lock < list_count; ++index_lock) {
      spin_lock[index_lock] = 0;
    }
  }

  //initialize list heads
  int index_list;
  list = malloc(sizeof(SortedList_t) * list_count);
  for(index_list = 0; index_list < list_count; ++index_list) {
    list[index_list].next = &list[index_list];
    list[index_list].prev = &list[index_list];
    list[index_list].key = NULL;
  }

  element_count = threads * iterations;
  elements = malloc(element_count * sizeof(SortedListElement_t));

  srand(time(NULL));
  int index_element;
  for(index_element = 0; index_element < element_count; ++index_element) {
    char* random_key = malloc(2 * sizeof(char));
    random_key[0] = (rand() % 26) + 'a';
    random_key[1] = '\0';

    elements[index_element].key = random_key;
    elements[index_element].prev = NULL;
    elements[index_element].next = NULL;
  }

  pthread_t* threads_id = malloc(threads * sizeof(pthread_t));

  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  int i;  
  //Change all this
  for(i = 0; i < threads; ++i) {
    if(pthread_create(&threads_id[i], NULL, thread_worker, (void*) (elements + (iterations * i)))) {
      fprintf(stderr, "Failed to create thread: %d\n", i);
      exit(1);
    }
  }
  for(i = 0; i < threads; ++i) {
    if(pthread_join(threads_id[i], NULL)) {
      fprintf(stderr, "Error joining thread: %d\n", i);
      exit(1);
    }
  }
  //up to here
  //printf("reach this statement\n");
  clock_gettime(CLOCK_MONOTONIC, &end_time);


  for(i = 0; i < list_count; ++i) {
    if(SortedList_length(&list[i]) != 0) {
      fprintf(stderr, "Corrupted list, end of process\n");
      exit(2);
    }
  }
  long long run_time = ((end_time.tv_sec - start_time.tv_sec) * 1000000000) + (end_time.tv_nsec - start_time.tv_nsec);
  int operation_count = threads * iterations * 3;

  switch(opt_yield) {
  case INSERT_YIELD:
    yieldopts = "i";
    break;
  case DELETE_YIELD:
    yieldopts = "d";
    break;
  case LOOKUP_YIELD:
    yieldopts = "l";
    break;
  case ID_YIELD:
    yieldopts = "id";
    break;
  case IL_YIELD:
    yieldopts = "il";
    break;
  case DL_YIELD:
    yieldopts = "dl";
    break;
  case IDL_YIELD:
    yieldopts = "idl";
    break;
  default:
    yieldopts = "none";
    break;
  }

  printf("list-%s-%s,%d,%d,%d,%d,%lld,%lld,%lld\n", yieldopts, syncopts, threads, iterations, list_count, operation_count, run_time, run_time/operation_count, lock_wait/operation_count);

  for(index_element = 0; index_element < element_count; ++index_element) {
    free((void*)elements[index_element].key);
  }
  free(threads_id);
  free(elements);
  free(list);

  exit(0);
}
