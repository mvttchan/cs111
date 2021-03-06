//NAME: Matthew Chan
//EMAIL: matthew_2185@yahoo.com
//ID: 805291212

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <errno.h>
#include <string.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <sys/wait.h>

struct termios original_terminal;
int pipe_to_shell[2];
int pipe_from_shell[2];
pid_t pid;

void set_terminal();
void restore_terminal();
void echo_to_terminal();
void create_pipes();

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

void echo_to_terminal() {
  const int MAX_BYTES = 1;
  char buffer[MAX_BYTES];
  
  int read_flag = read(0, buffer, sizeof(buffer));
  while(read_flag > 0) {
    char input = buffer[0];
    if(input == 0x04) {
      exit(0);
    }
    else if(input == 0x0D || input == 0x0A) {
      write(1, "\r\n", 2);
    }
    else {
      write(1, &input, 1);
    }
    if(read_flag == -1) {
      fprintf(stderr, "Failed to read input from file descriptor 0\n");
      exit(1);
    }
    read_flag = read(0, buffer, sizeof(buffer));
  }
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

int main(int argc, char* argv[]) {

  int shell_flag = 0;
  char* shell_program;

  struct option options[] = {
    {"shell", 1, NULL, 's'},
    {0,0,0,0}
  };

  int c;
  while((c = getopt_long(argc, argv, "", options, NULL)) != -1) {
    switch(c) {
    case 's':
      shell_flag = 1;
      shell_program = optarg;
      break;
    default:
      fprintf(stderr, "Unrecognized argument\n");
      exit(1);
    }
  }
  set_terminal();
  
  //Non shell mode
  if(shell_flag == 0) {
    echo_to_terminal();
  }

  //Shell mode
  create_pipes();
  if((pid = fork()) < 0) {
    fprintf(stderr,  "Failed to fork\n");
    exit(1);
  }
  if(pid == 0) {
    //close write to child and read from terminal
    close(pipe_to_shell[1]);
    close(pipe_from_shell[0]);

    dup2(pipe_to_shell[0], 0);
    dup2(pipe_from_shell[1], 1);
    dup2(pipe_from_shell[1], 2);
  
    close(pipe_to_shell[0]);
    close(pipe_from_shell[1]);

    execlp(shell_program, shell_program, NULL);
    //if program fails then this code runs
    fprintf(stderr, "Error executing shell program\n");
    exit(1);
  }
  else if(pid > 0) {
    //close read to child and write to terminal
    close(pipe_to_shell[0]);
    close(pipe_from_shell[1]);
    
    struct pollfd pollfds[2];
    pollfds[0].fd = 0;
    pollfds[0].events = POLLIN + POLLHUP + POLLERR;
    pollfds[1].fd = pipe_from_shell[0];
    pollfds[1].events = POLLIN + POLLHUP + POLLERR;
    int exit_shell = 0;

    while(!exit_shell) {
      poll(pollfds, 2, -1);

      //reads from keyboard
      if(pollfds[0].revents & POLLIN) {
	const int MAX_BYTES = 32;
	char buffer[MAX_BYTES];
	int bytes_read = read(0, buffer, MAX_BYTES);
	if(bytes_read < 0) {
	  fprintf(stderr, "Error reading file descriptor 0, parent process\n");
	  exit(1);
	}
	int i;
	for(i = 0; i < bytes_read; ++i) {
	  char current_char = buffer[i];
	  if(current_char == 0x04) {
	    close(pipe_to_shell[1]);
	  }
	  else if(current_char == 0x0D || current_char == 0x0A) {
	    write(1, "\r\n", 2);
	    write(pipe_to_shell[1], "\n", 1);
	  }
	  else if(current_char == 0x03) {
	    if(kill(pid, SIGINT) < 0) {
	      fprintf(stderr, "Could not send interrupt signal to child process, POLLIN code\n");
	      exit(1);
	    }
	  }
	  else {
	    write(1, &current_char, 1);
	    write(pipe_to_shell[1], &current_char, 1);
	  }
	}
      }

      //read shell's input
      if(pollfds[1].revents & POLLIN) {
	const int MAX_BYTES_SHELL = 256;
	char buffer_shell[MAX_BYTES_SHELL];

	int bytes_read_shell = read(pipe_from_shell[0], buffer_shell, MAX_BYTES_SHELL);
	if(bytes_read_shell < 0) {
	  fprintf(stderr, "Error reading input from shell, parent process\n");
	  exit(1);
	}
	int i_shell;
	for(i_shell = 0; i_shell < bytes_read_shell; ++i_shell) {
	  char shell_char = buffer_shell[i_shell];
	  if(shell_char == 0x04) {
	    write(1, "^D", 2);
	    exit_shell = 1;
	  }
	  else if(shell_char == 0x0A) {
	    write(1, "\r\n", 2);
	  }
	  else {
	    write(1, &shell_char, 1);
	  }
	}
      }
      if(pollfds[0].revents & (POLLHUP | POLLERR)) {
	//send interrupt to child process because keyboard said so
	if(kill(pid, SIGINT) < 0) {
	  fprintf(stderr, "Could not send interrupt signal to child process, revents code\n");
	  exit(1);
	}
      }
      if(pollfds[1].revents & (POLLHUP | POLLERR)) {
	//wait for child to finish processing then terminate
	int status;
	if(waitpid(pid, &status, 0) < 0) {
	  fprintf(stderr, "Error waiting for child process to terminate\n");
	  exit(1);
	}
	exit_shell = 1;
	fprintf(stderr, "SHELL EXIT SIGNAL=%d, STATUS=%d\r\n", (status & 0xff), WEXITSTATUS(status));
      }
    }
  }
  exit(0);
}
