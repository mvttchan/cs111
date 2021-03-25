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
#include <sys/stat.h>
#include <netinet/in.h>
#include <poll.h>
#include <termios.h>
#include <getopt.h>
#include <unistd.h>
#include <signal.h>
#include <netdb.h>
#include <fcntl.h>
#include "zlib.h"

struct termios original_terminal;
z_stream c_stream;
z_stream d_stream;
const int MAX_BYTES = 256;

int client_connect(char* hostname, unsigned int port);
void set_terminal();
void restore_terminal();
void init_compress_stream();
void compress_stream(void* orig_buf, int orig_len, void* out_buf, int out_len);
void fini_compress_stream();
void init_decompress_stream();
int decompress_stream(void* orig_buf, int orig_len, void* out_buf, int out_len);
void fini_decompress_stream();

int main(int argc, char* argv[]) {
  int port = 0;
  int port_flag = 0;
  int log_flag = 0;
  int log_fd = 0;
  int compress_flag = 0;
  char c_buffer[MAX_BYTES];

  struct option options[] = {
    {"port", 1, NULL, 'p'},
    {"log", 1, NULL, 'l'},
    {"compress", 0, NULL, 'c'},
    {0,0,0,0}
  };

  int c;
  while((c = getopt_long(argc, argv, "", options, NULL)) != -1) {
    switch(c) {
    case 'p':
      port_flag = 1;
      port = atoi(optarg);
      break;
    case 'l':
      log_flag = 1;
      if(optarg == NULL) {
	fprintf(stderr, "Invalid log filename\n");
	exit(1);
      }
      log_fd = creat(optarg, 0777);
      if(log_fd < 0) {
	fprintf(stderr, "Unable to print log file\n");
	exit(1);
      }
      break;
    case 'c':
      compress_flag = 1;
      break;
    default:
      fprintf(stderr, "Unrecognized argument\r\n");
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

  set_terminal();
  int socket_fd = client_connect("localhost", port);
  
  struct pollfd pollfds[2];
  pollfds[0].fd = 0;
  pollfds[0].events = POLLIN + POLLHUP + POLLERR;
  pollfds[1].fd = socket_fd;
  pollfds[1].events = POLLIN + POLLHUP + POLLERR;
  
  char buffer[MAX_BYTES];
  char current_char;
  int bytes_read = 0;
  int index = 0;

  while(1) {
    poll(pollfds, 2, -1);
    if(pollfds[0].revents & POLLIN) {
      if((bytes_read = read(pollfds[0].fd, &buffer, MAX_BYTES)) < 0) {
	fprintf(stderr, "Could not read from keyboard \n");
	exit(1);
      }
      if(compress_flag) {
	compress_stream(buffer, bytes_read, c_buffer, MAX_BYTES);
	if(write(pollfds[1].fd, &c_buffer, (MAX_BYTES - c_stream.avail_out)) < 0) {
	  fprintf(stderr, "Failed to write compressed data to socket\n");
	  exit(1);
	}
      }
      for(index = 0; index < bytes_read; ++index) {
	current_char = buffer[index];
	if(current_char == 0x0D || current_char == 0x0A) {
	  if(write(1, "\r\n", 2) < 0) {
	    fprintf(stderr, "Failed to write new line and carriage return to screen\n");
	    exit(1);	  
	  }
	  if(!compress_flag) {
	    if(write(pollfds[1].fd, "\n", 1) < 0) {
	      fprintf(stderr, "Could not write new line to socket\n");
	      exit(1);
	    }
	  }
	}	
	else {
	  if(write(1, &current_char, 1) < 0) {
	    fprintf(stderr, "Failed to write new line and carriage return to screen\n");
	    exit(1);	  
	  }
	  if(!compress_flag) {
	    if(write(pollfds[1].fd, &current_char, 1) < 0) {
	      fprintf(stderr, "Failed to write new line and carriage return to screen\n");
	      exit(1);	  
	    }
	  }
	}
      }
      if(bytes_read && log_flag) {
	if(compress_flag) {
	  if(dprintf(log_fd, "SENT %d bytes: ", (MAX_BYTES - c_stream.avail_out)) < 0) {
	    fprintf(stderr, "Failed to write to compressed log from keyboard\n");
	    exit(1);
	  }
	  if(write(log_fd, &c_buffer, (MAX_BYTES - c_stream.avail_out)) < 0) {
	    fprintf(stderr, "Failed to write to compressed log from keyboard\n");
	    exit(1);
	  }
	  if(write(log_fd, "\n", 1) < 0) {
	    fprintf(stderr, "Failed to write to compressed log from keyboard\n");
	    exit(1);
	  }
	}
	else {
	  if(dprintf(log_fd, "SENT %d bytes: ", bytes_read) < 0) {
	    fprintf(stderr, "Failed to log from keyboard\n");
	    exit(1);
	  }
	  if(write(log_fd, &buffer, bytes_read) < 0) {
	    fprintf(stderr, "Failed to log from keyboard\n");
	    exit(1);
	  }
	  if(write(log_fd, "\n", 1) < 0) {
	    fprintf(stderr, "Failed to log from keyboard\n");
	    exit(1);
	  }
	} 
      }
    }
    if(pollfds[1].revents & POLLIN) {
      if((bytes_read = read(pollfds[1].fd, &buffer, MAX_BYTES)) < 0) {
	fprintf(stderr, "Client could not read from socket\n");
	exit(1);
      }
      if(!bytes_read) {
	exit(0);
      }
      if(bytes_read && log_flag) {
	//compress and not compress share same code
	if(dprintf(log_fd, "RECEIVED %d bytes: ", bytes_read) < 0) {
	  fprintf(stderr, "Failed to log from socket\n");
	  exit(1);
	}
	if(write(log_fd, &buffer, bytes_read) < 0) {
	  fprintf(stderr, "Failed to log from socket\n");
	  exit(1);
	}
	if(write(log_fd, "\n", 1) < 0) {
	  fprintf(stderr, "Failed to log from socket\n");
	  exit(1);
	}
      }   
      if(compress_flag) {
	memcpy(c_buffer, buffer, bytes_read);
	bytes_read = decompress_stream(c_buffer, bytes_read, buffer, MAX_BYTES);
      }
      for(index = 0; index < bytes_read; ++index) {
	current_char = buffer[index];
	if(current_char == 0x0A) {
	  if(write(1, "\r\n", 2) < 0) {
	    fprintf(stderr, "Could not write socket to display\n");
	    exit(1);
	  }
	}
	else {
	  if(write(1, &current_char, 1) < 0) {
	    fprintf(stderr, "Could not write socket to display\n");
	    exit(1);
	  }
	}
      }
    }
    if(pollfds[0].revents & (POLLHUP | POLLERR)) {
      fprintf(stderr, "Error from the keyboard\r\n");
      exit(1);
    }
    if(pollfds[1].revents & (POLLHUP | POLLERR)) {
      fprintf(stderr, "Network connection has ended\r\n");
      exit(0);
    }
  }   
}

int client_connect(char* hostname, unsigned int port) {
  int sockfd;
  struct sockaddr_in serv_addr;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "Creating client socket failed\n");
    exit(1);
  }
  struct hostent* server = gethostbyname(hostname);
  memset(&serv_addr, 0, sizeof(struct sockaddr_in));
  serv_addr.sin_family = AF_INET;
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  serv_addr.sin_port = htons(port);
  if(connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
    fprintf(stderr, "Failed to connect client to server\r\n");
    exit(1);
  }
  return sockfd;
}
  
void set_terminal() {
  struct termios new_terminal;
  if(tcgetattr(0, &new_terminal) < 0) {
    fprintf(stderr, "Could not retrieve original terminal\n");
    exit(1);
  }
  original_terminal = new_terminal;
  new_terminal.c_iflag = ISTRIP;
  new_terminal.c_oflag = 0;
  new_terminal.c_lflag = 0;
  if(tcsetattr(0, TCSANOW, &new_terminal) < 0) {
    fprintf(stderr, "Could not set new terminal\n");
    exit(1);
  }
  atexit(restore_terminal);
}

void restore_terminal() {
  if(tcsetattr(0, TCSANOW, &original_terminal) < 0) {
    fprintf(stderr, "Could not restore to original terminal state\n");
    exit(1);
  }
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
  do {
    deflate(&c_stream, Z_SYNC_FLUSH);
  } while(c_stream.avail_in > 0);
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
