//NAME: Matthew Chan
//EMAIL: matthew_2185@yahoo.com
//ID: matthew_2185@yahoo.com

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

long long sum = 0;
pthread_mutex_t mutex;
int spin_lock = 0;

int threads = 0;
int iterations = 0;
int opt_yield = 0;
int sync_flag = 0;
char* run_type = "none";

void add(long long *pointer, long long value) {
  long long sum = *pointer + value;
  if(opt_yield) sched_yield();
  *pointer = sum;
}

void* thread_worker() {
  int i;
  //unsynchronized
  if(sync_flag == 0) {
    for(i = 0; i < iterations; ++i) {
      add(&sum, 1);
    }
    for(i = 0; i < iterations; ++i) {
      add(&sum, -1);
    }
  }
  //mutex
  else if(sync_flag == 1) {
    for(i = 0; i < iterations; ++i) {
      pthread_mutex_lock(&mutex);
      add(&sum, 1);      
      pthread_mutex_unlock(&mutex);
    }
    for(i = 0; i < iterations; ++i) {
      pthread_mutex_lock(&mutex);
      add(&sum, -1);
      pthread_mutex_unlock(&mutex);
    }
  }
  //spin lock
  else if(sync_flag == 2) {
    for(i = 0; i < iterations; ++i) {
      while(__sync_lock_test_and_set(&spin_lock, 1));
      add(&sum, 1);
      __sync_lock_release(&spin_lock);
    }
    for(i = 0; i < iterations; ++i) {
      while(__sync_lock_test_and_set(&spin_lock, 1));
      add(&sum, -1);
      __sync_lock_release(&spin_lock);
    }
  }
  //compare and swap
  else if(sync_flag == 3){
    long long old_value, new_value;
    for(i = 0; i < iterations; ++i) {
      do {
	old_value = sum;
	new_value = old_value + 1;
	if(opt_yield) sched_yield();
      } while(__sync_val_compare_and_swap(&sum, old_value, new_value) != old_value);
    }
    for(i = 0; i < iterations; ++i) {
      do {
        old_value = sum;
        new_value = old_value + -1;
        if(opt_yield) sched_yield();
      } while(__sync_val_compare_and_swap(&sum, old_value, new_value) != old_value);
    }
  }
  else {
    fprintf(stderr, "Shouldn't reach this statement, error in flag value\n");
    exit(1);
  }
  return NULL;
}

int main(int argc, char* argv[]) {
  
  struct option options[] = {
    {"threads", 1, NULL, 't'},
    {"iterations", 1, NULL, 'i'},
    {"yield", 0, NULL, 'y'},
    {"sync", 1, NULL, 's'},
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
      opt_yield = 1;
      break;
    case 's':
      switch(optarg[0]) {
      case 'm':
	sync_flag = 1;
	break;
      case 's':
	sync_flag = 2;
	break;
      case 'c':
	sync_flag = 3;
	break;
      default:
	fprintf(stderr, "Only m, s, and c are allowed options\n");
	exit(1);
      }
      break;
    default:
      fprintf(stderr, "Unrecognized argument\n");
      exit(1);
    }
  }
  if(!iterations || !threads) {
    fprintf(stderr, "Must have more than 0 threads or iterations\n");
    exit(1);
  }

  //avoid lazy initialization to more accurately return end time
  struct timespec start_time, end_time;
  clock_gettime(CLOCK_MONOTONIC, &start_time);

  pthread_t* threads_id = malloc(threads * sizeof(pthread_t));
  int i;
  for(i = 0; i < threads; ++i) {
    if(pthread_create(&threads_id[i], NULL, thread_worker, NULL)) {
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
  clock_gettime(CLOCK_MONOTONIC, &end_time);
  free(threads_id);
  long long run_time = ((end_time.tv_sec - start_time.tv_sec) * 1000000000) + (end_time.tv_nsec - start_time.tv_nsec);
  int operation_count = threads * iterations * 2;
  

  if(opt_yield) {
    if(sync_flag == 0) run_type = "yield-none";
    else if(sync_flag == 1) run_type = "yield-m";
    else if(sync_flag == 2) run_type = "yield-s";
    else if(sync_flag == 3) run_type = "yield-c";
  }
  else {
    if(sync_flag == 0) run_type = "none";
    else if(sync_flag == 1) run_type = "m";
    else if(sync_flag == 2) run_type = "s";
    else if(sync_flag == 3) run_type = "c";
  }

  printf("add-%s,%d,%d,%d,%lld,%lld,%lld\n", run_type, threads, iterations, operation_count, run_time, run_time/operation_count, sum);
  exit(0);
}
