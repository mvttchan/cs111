//NAME:  Matthew Chan
//EMAIL: matthew_2185@yahoo.com
//ID:    805291212

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <poll.h>
#include <termios.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include "zlib.h"

int pipe_to_shell[2];
int pipe_from_shell[2];
pid_t pid;
z_stream c_stream;
z_stream d_stream;
const int MAX_BYTES = 512;

int server_connect(unsigned int port);
void create_pipes();
void signal_handler(int signal);
void init_compress_stream();
void compress_stream(void* orig_buf, int orig_len, void* out_buf, int out_len);
void fini_compress_stream();
void init_decompress_stream();
int decompress_stream(void* orig_buf, int orig_len, void* out_buf, int out_len);
void fini_decompress_stream();

int main(int argc, char* argv[]) {
  signal(SIGPIPE, signal_handler);
  signal(SIGINT, signal_handler);

  int port = 0;
  int port_flag = 0;
  int compress_flag = 0;
  char* shell_program = "/bin/bash";
  char* arguments[2];
  char c_buffer[MAX_BYTES];
  
  struct option options[] = {
    {"port", 1, NULL, 'p'},
    {"shell", 1, NULL, 's'},
    {"compress", 0, NULL, 'c'},
    {0,0,0,0}
  };

  int c;
  while((c = getopt_long(argc, argv, "p", options, NULL)) != -1) {
    switch(c) {
    case 'p':
      port_flag = 1;
      port = atoi(optarg);
      break;
    case 's':
      shell_program = optarg;
      break;
    case 'c':
      compress_flag = 1;
      break;
    default:
      fprintf(stderr, "Unrecognized argument, can only use --port\n");
      exit(1);
    }
  }

  if(!port_flag) {
    fprintf(stderr, "Must provide port number\n");
    exit(1);
  }
  if(compress_flag) {
    init_compress_stream();
    init_decompress_stream();
  }

  int socket_fd = server_connect(port);
  create_pipes();

  if((pid = fork()) < 0) {
    fprintf(stderr, "Fork failed\n");
    exit(1);
  }
  
  //child process
  if(pid == 0) {
    close(pipe_to_shell[1]);
    close(pipe_from_shell[0]);

    dup2(pipe_to_shell[0], 0);
    dup2(pipe_from_shell[1], 1);
    dup2(pipe_from_shell[1], 2);

    close(pipe_to_shell[0]);
    close(pipe_from_shell[1]);

    arguments[0] = shell_program;
    arguments[1] = NULL;

    //change this to support shell option
    if(execvp(shell_program, arguments) < 0) {
      fprintf(stderr, "Shell process failed\n");
      exit(1);
    }
  }
  
  //parent process
  close(pipe_to_shell[0]);
  close(pipe_from_shell[1]);

  struct pollfd pollfds[2];
  pollfds[0].fd = socket_fd;
  pollfds[0].events = POLLIN + POLLHUP + POLLERR;
  pollfds[1].fd = pipe_from_shell[0];
  pollfds[1].events = POLLIN + POLLHUP + POLLERR;
  int exit_flag = 0;

  while(!exit_flag) {
    poll(pollfds, 2, -1);
    if(pollfds[0].revents & POLLIN) {
      char buffer[MAX_BYTES];
      int bytes_read = read(pollfds[0].fd, &buffer, MAX_BYTES);
      if(bytes_read < 0) {
	fprintf(stderr, "Error reading file descriptor socket_fd\n");
	exit(1);
      }
      if(compress_flag) {
	bytes_read = decompress_stream(buffer, bytes_read, c_buffer, MAX_BYTES);
	memcpy(buffer, c_buffer, bytes_read);
      }
      int i;
      char current_char;
      for(i = 0; i < bytes_read; ++i) {
	current_char = buffer[i];
	if(current_char == 0x04) {
	  close(pipe_to_shell[1]);
	}
	else if(current_char == 0x0D || current_char == 0x0A) {
	  if(write(pipe_to_shell[1], "\n", 2) < 0) {
	    fprintf(stderr, "Could not write new line to shell\n");
	    exit(1);
	  }
	}
	else if(current_char == 0x03) {
	  if(kill(pid, SIGINT) < 0) {
	    fprintf(stderr, "Could not send interrupt signal to shell process\n");
	    exit(1);
	  }
	}
	else {
	  if(write(pipe_to_shell[1], &current_char, 1) < 0) {
	    fprintf(stderr, "Could not write to shell\n");
	    exit(1);
	  }
	}
      }
    }
    if(pollfds[1].revents & POLLIN) {
      const int MAX_BYTES_SHELL = 512;
      char buffer_shell[MAX_BYTES_SHELL];

      int bytes_read_shell = read(pipe_from_shell[0], &buffer_shell, MAX_BYTES_SHELL);
      if(bytes_read_shell < 0) {
	fprintf(stderr, "Error reading input from shell\n");
	exit(1);
      }
      if(compress_flag) {
	compress_stream(buffer_shell, bytes_read_shell, c_buffer, MAX_BYTES_SHELL);
	if(write(pollfds[0].fd, &c_buffer, (MAX_BYTES_SHELL - c_stream.avail_out)) < 0) {
	  fprintf(stderr, "Could not write compressed data to socket\n");
	  exit(1);
	}
      }
      else {
	if(write(pollfds[0].fd, &buffer_shell, bytes_read_shell) < 0) {
	  fprintf(stderr, "Could not write back to socket\n");
	  exit(1);
	}
      }
    }
    if(pollfds[0].revents & (POLLHUP | POLLERR)) {
      close(pipe_to_shell[1]);
      int status_0;
      if(waitpid(pid, &status_0, 0) < 0) {
	fprintf(stderr, "Error waiting for shell process to terminate\n");
	exit(1);
      }
      exit_flag = 1;
      fprintf(stderr, "SHELL EXIT SIGNAL=%d, STATUS=%d\r\n", (status_0 & 0xff), WEXITSTATUS(status_0));
    }
    if(pollfds[1].revents & (POLLHUP | POLLERR)) {
      int status_1;
      if(waitpid(pid, &status_1, 0) < 0) {
	fprintf(stderr, "Error waiting for shell process to terminate\n");
	exit(1);
      }
      exit_flag = 1;
      fprintf(stderr, "SHELL EXIT SIGNAL=%d, STATUS=%d\r\n", (status_1 & 0xff), WEXITSTATUS(status_1));
    }
  }
  exit(0);
}

void create_pipes() {
  if(pipe(pipe_to_shell) < 0) {
    fprintf(stderr, "Error creating pipes to shell\n");
    exit(1);
  }
  if(pipe(pipe_from_shell) < 0) {
    fprintf(stderr, "Error creating pipes from shell\n");
    exit(1);
  }
}

void signal_handler(int signal) {
  if(signal == SIGINT) {
    kill(pid, SIGINT);
  }
  if(signal == SIGPIPE) {
    exit(0);
  }
}

int server_connect(unsigned int port) {
  struct sockaddr_in server_address, client_address;
  unsigned client_length = sizeof(struct sockaddr_in);
  int listenfd = socket(AF_INET, SOCK_STREAM, 0), returnfd = 0;
  memset(&server_address, 0, sizeof(struct sockaddr_in));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port);
  bind(listenfd, (struct sockaddr *) &server_address, sizeof(server_address));
  listen(listenfd, 5);
  returnfd = accept(listenfd, (struct sockaddr *) &client_address, &client_length);
  return returnfd;
  //unsure if i need to close sockets here
}

void init_compress_stream() {
  int ret = 0;
  c_stream.zalloc = Z_NULL, c_stream.zfree = Z_NULL, c_stream.opaque = Z_NULL;
  ret = deflateInit(&c_stream, Z_DEFAULT_COMPRESSION);
  if(ret != Z_OK) {
    fprintf(stderr, "Failed to initialize compression stream\n");
    exit(1);
  }
  atexit(fini_compress_stream);
}

void compress_stream(void* orig_buf, int orig_len, void* out_buf, int out_len) {
  c_stream.next_in = orig_buf, c_stream.avail_in = orig_len;
  c_stream.next_out = out_buf, c_stream.avail_out = out_len;
  while(c_stream.avail_in > 0) {
    deflate(&c_stream, Z_SYNC_FLUSH);
  }
}

void fini_compress_stream() {
  deflateEnd(&c_stream);
}

void init_decompress_stream() {
  int ret = 0;
  d_stream.zalloc = Z_NULL, d_stream.zfree = Z_NULL, d_stream.opaque = Z_NULL;
  ret = inflateInit(&d_stream);
  if(ret != Z_OK) {
    fprintf(stderr, "Failed to initialize decompression stream\n");
    exit(1);
  }
  atexit(fini_decompress_stream);
}

int decompress_stream(void* orig_buf, int orig_len, void* out_buf, int out_len) {
  d_stream.next_in = orig_buf, d_stream.avail_in = orig_len;
  d_stream.next_out = out_buf, d_stream.avail_out = out_len;
  while(d_stream.avail_in > 0) {
    inflate(&d_stream, Z_SYNC_FLUSH);
  }
  return out_len - d_stream.avail_out;
}

void fini_decompress_stream() {
  inflateEnd(&d_stream);
}
