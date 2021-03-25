//Matthew Chan
//805291212
//matthew_2185@yahoo.com

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void redirect_input(char* file) {
  int ifd = open(file, O_RDONLY);
  if(ifd < 0) {
    fprintf(stderr, "Could not open input file %s: %s\n", file, strerror(errno));
    exit(2);
  }
  close(0);
  dup(ifd);
  close(ifd);
  return;
}

void redirect_output(char* file) {
  //Read and write permissions, otherwise you cant read output to compare
  int ofd = creat(file, 0666);
  if(ofd < 0) {
    fprintf(stderr, "Could not open output file %s: %s\n", file, strerror(errno));
    exit(3);
  }
  close(1);
  dup(ofd);
  close(ofd);
  return;
}

void cause_segfault() {
  char* pointer = NULL;
  *pointer = 'a';
  return;
}

void err_handler(int input_sig) {
  if(input_sig == SIGSEGV) {
    fprintf(stderr, "Segmentation fault found\n");
    exit(4);
  }
}

int main(int argc, char* argv[]) {
  int input_flag, output_flag, segfault_flag;
  char* input_file;
  char* output_file;

  input_flag = 0;
  output_flag = 0;
  segfault_flag = 0;
  input_file = NULL;
  output_file = NULL;

  static struct option options[] = {
    {"input", 1, NULL, 'i'},
    {"output", 1, NULL, 'o'},
    {"segfault", 0, NULL, 's'},
    {"catch", 0, NULL, 'c'},
    {0,0,0,0}
  };

  int c;

  while((c = getopt_long(argc, argv, "", options, NULL)) != -1) {
    switch(c) {
    case 'i':
      input_flag = 1;
      input_file = optarg;
      break;
    case 'o':
      output_flag = 1;
      output_file = optarg;
      break;
    case 's':
      segfault_flag = 1;
      break;
    case 'c':
      signal(SIGSEGV, err_handler);
      break;
    default:
      fprintf(stderr, "Incorrect options\n");
      exit(1);
    }
  }
  if(segfault_flag){
    cause_segfault();
  }
  if(input_flag) {
    redirect_input(input_file);
  }
  if(output_flag) {
    redirect_output(output_file);
  }

  int bytes_read;
  char buffer;
  bytes_read = read(0, &buffer, sizeof(char));
  while(bytes_read) {
    if (!write(1, &buffer, bytes_read)) {
      fprintf(stderr, "Error writing to output: %s\n", strerror(errno));
      exit(3);
    }
    bytes_read = read(0, &buffer, sizeof(char));
  }

  exit(0);
}
