//NAME:  Matthew Chan
//EMAIL: matthew_2185@yahoo.com
//ID:    805291212

#ifdef DUMMY
#define MRAA_GPIO_IN 0
#define MRAA_GPIO_EDGE_RISING 0
typedef int mraa_aio_context;
typedef int mraa_gpio_context;

mraa_aio_context mraa_aio_init(__attribute__((unused)) int p) {
	return 0;
}
mraa_gpio_context mraa_gpio_init(__attribute__((unused)) int p) {
	return 0;
}
int mraa_aio_read(__attribute__((unused)) mraa_aio_context c) {
	return 650;
}
void mraa_aio_close(__attribute__((unused)) mraa_aio_context c) {
}
void mraa_gpio_dir(__attribute__((unused)) mraa_gpio_context c, __attribute__((unused)) int butt) {
}
void mraa_gpio_isr(__attribute__((unused)) mraa_gpio_context c, __attribute__((unused)) int butt, __attribute__((unused)) void(*fptr)(void*), __attribute__((unused)) void* args) {
}
void mraa_deinit() {
}
void mraa_gpio_close(__attribute__((unused)) mraa_gpio_context c) {
}
#else
#include <mraa.h>
#endif
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <poll.h>
#include <time.h>
#include <ctype.h>
#include <math.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <netdb.h>

#define B 4275
#define R0 100000.0

int period = 1;
int f_scale = 1;
FILE* log_file = 0;
int stop = 0;
int log_flag = 0;
mraa_gpio_context button;
mraa_aio_context temperature;
time_t minute = 0;
char* id = NULL;
char* hostname = NULL;
int port = 0;
int socketfd;

float convert_temper_reading(int reading) {
  float R = 1023.0/((float) reading) - 1.0;
  R = R0 * R;
  float C = 1.0/(log(R/R0)/B + 1/298.15) - 273.15;
  float F = (C * 9) / 5 + 32;
  if(f_scale == 1) return F;
  else return C;
}

void print_to_log(char* str) {
	fprintf(log_file, "%s", str);
	fflush(log_file);
}

void print_current_time() {
  struct timespec ts;
  struct tm *tm;
  clock_gettime(CLOCK_REALTIME, &ts);
  tm = localtime(&(ts.tv_sec));
  //dprintf(socketfd, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
  printf("%02d:%02d:%02d \n", tm->tm_hour, tm->tm_min, tm->tm_sec);
  /*
  if (log_flag) {
	  fprintf(log_file, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
	  fflush(log_file);
  }
  */
}

void do_when_pushed() {
  //print_current_time();
  //dprintf(socketfd, "SHUTDOWN\n");
	struct timespec ts;
	struct tm *tm;
	clock_gettime(CLOCK_REALTIME, &ts);
	tm = localtime(&(ts.tv_sec));
	dprintf(socketfd, "%02d:%02d:%02d SHUTDOWN\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
  if (log_flag) {
	  fprintf(log_file, "%02d:%02d:%02d SHUTDOWN\n", tm->tm_hour, tm->tm_min, tm->tm_sec);
	  fflush(log_file);
  }
  exit(0);
}

void print_temperature() {
  print_current_time();
  //dummy value
  //BE SURE TO FIX THIS ASSHOLE
  float temp = mraa_aio_read(temperature);
  temp = convert_temper_reading(temp);
  dprintf(socketfd, "%.1f\n", temp);
  if (log_flag) {
	  fprintf(log_file, "%.1f\n", temp);
	  fflush(log_file);
  }
}

void print_current_temperature() {
	struct timespec ts;
	struct tm *tm;
	clock_gettime(CLOCK_REALTIME, &ts);
	tm = localtime(&(ts.tv_sec));
	float temp = mraa_aio_read(temperature);
	temp = convert_temper_reading(temp);
	dprintf(socketfd, "%02d:%02d:%02d %.1f\n", tm->tm_hour, tm->tm_min, tm->tm_sec, temp);
	if (log_flag) {
		fprintf(log_file, "%02d:%02d:%02d %.1f\n", tm->tm_hour, tm->tm_min, tm->tm_sec, temp);
		fflush(log_file);
	}
}

void handle_input(char* input, int length) {
  //int input_length = strlen(input);
  input[length + 1] = '\0';
  //Put this^ in the README file, that shit is the worst
  //cant use strcmp because the cmp reads past the intended length
  //problem is if a user puts a valid string inside a garbage one
  //if(strcmp(input, "SCALE=F") == 0) {
  if(strstr(input, "SCALE=F") != NULL) {
    //printf("SCALE=F\n");
    if(log_flag) print_to_log("SCALE=F\n");
    f_scale = 1;
  }
  else if(strstr(input, "SCALE=C") != NULL) {
    //printf("SCALE=C\n");
    if(log_flag) print_to_log("SCALE=C\n");
    f_scale = 0;
  }
  else if(strstr(input, "STOP") != NULL) {
    //dprintf(socketfd,"STOP\n");
    if(log_flag) print_to_log("STOP\n");
    stop = 1;
  }
  else if(strstr(input, "START") != NULL) {
    //dprintf(socketfd, "START\n");
    if(log_flag) print_to_log("START\n");
    stop = 0;
  }
  else if(strstr(input, "OFF") != NULL) {
    //dprintf(socketfd, "OFF\n");
    if(log_flag) print_to_log("OFF\n");
    stop = 1;
    do_when_pushed();
  }
  else if(*input == 'P') {
    if(strstr(input, "PERIOD=") == NULL) return;
    /*
      int length = strlen(input) - 1;
      int i = 7;
      if(input[i] == 0) return;
      while(i < length) {
      if(!isdigit(input[i])) return;
      ++i;
      }
    */
    int temp =  atoi(&input[7]);
    if(!temp) return;
    period = temp;
    //printf("PERIOD=%d\n", period);
    if (log_flag) {
      fprintf(log_file, "PERIOD=%d\n", period);
      fflush(log_file);
    }
    /*useless because i just changed it to not need minute
      if (period > 59) {
      struct timespec ts;
      struct tm* tm;
      clock_gettime(CLOCK_REALTIME, &ts);
      tm = localtime(&(ts.tv_sec));
      minute = tm->tm_min + (period / 60);
      }
    */
  }
  else if(*input == 'L') {
    if(strstr(input, "LOG") == NULL) return;
    //printf("%s\n", input);
    if (log_flag) {
      fprintf(log_file, "%s", input);
		fflush(log_file);
    }
  }
  else {
    //printf("%s\n", input);
    if (log_flag) print_to_log(input);
  }
}

int client_connect(char* host_name, unsigned int port) {
  struct sockaddr_in serv_addr;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  struct hostent* server = gethostbyname(host_name);
  memset(&serv_addr, 0, sizeof(struct sockaddr_in));
  serv_addr.sin_family = AF_INET;
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);
  serv_addr.sin_port = htons(port);
  connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr));
  //sockfd.setblocking(0);
  return sockfd;
}

int main(int argc, char* argv[]) {
  
  struct option options[] = {
    {"period", 1, NULL, 'p'},
    {"scale", 1, NULL, 's'},
    {"log", 1, NULL, 'l'},
    {"id", 1, NULL, 'i'},
    {"host", 1, NULL, 'h'},
    {0,0,0,0}
  };
  
  int c;
  while((c = getopt_long(argc, argv, "", options, NULL)) != -1) {
    switch(c) {
    case 'p':
      period  = atoi(optarg);
      break;
    case 's':
      f_scale = optarg[0];
      if (optarg[0] == 'F') {
	f_scale = 1;
	break;
      }
      else if(optarg[0] == 'C') {
	f_scale = 0;
	break;
      }
      else {
	fprintf(stderr, "Scale can only be F or C\n");
	exit(1);
      }
    case 'l':      
      log_flag = 1;
      if(optarg == NULL) {
	fprintf(stderr, "Invalid log filename\n");
	exit(1);
      }
      log_file = fopen(optarg, "w+");
      if(log_file == NULL) {
	fprintf(stderr, "Unable to print log file\n");
	exit(1);
      }
      break;
    case 'i':
      if(strlen(optarg) != 9) {
	fprintf(stderr, "ID should be 9 digits/characters long\n");
	exit(1);
      }
      id = optarg;
      break;
    case 'h':
      hostname = optarg;
      break;
    default:
      fprintf(stderr, "Error in arguments, supports period scale and log only\n");
      exit(1);
    }
  }
  port = atoi(argv[optind]);
  if(port <= 0) {
    fprintf(stderr, "Invalid port number\n");
    exit(1);
  }
  if(hostname == NULL) {
    fprintf(stderr, "Hostname is null\n");
    exit(1);
  }
  socketfd = client_connect(hostname, port);
  dprintf(socketfd, "ID=%s\n", id);
  if(log_flag) {
    fprintf(log_file, "ID=%s\n", id);
    fflush(log_file);
  }
  
  button = mraa_gpio_init(73);
  temperature = mraa_aio_init(0);
  //I'd include the below code if not for the warnings for Dummy compiling
  /*
    if(button == NULL || temperature == NULL) {
    fprintf(stderr, "Error initializing button and temperature sensor\n");
    mraa_deinit();
    exit(1);
    }
  */
  mraa_gpio_dir(button, MRAA_GPIO_IN);
  mraa_gpio_isr(button, MRAA_GPIO_EDGE_RISING, &do_when_pushed, NULL);
  

  struct pollfd pollfds = {socketfd, POLLIN, 0};
  int bytes_read;
  int i;
  int parser = 0;
  char* input;
  char* process;
  input = (char*)malloc(256 * sizeof(char));
  process = (char*)malloc(256 * sizeof(char));
  if(input == NULL) {
    fprintf(stderr, "No more memory to allocate, torrent more RAM\n");
    exit(1);
  }
  
  struct timespec ts;
  //struct tm* tm;
  time_t next = 0;
  while (1) {
    clock_gettime(CLOCK_REALTIME, &ts);
    //tm = localtime(&(ts.tv_sec));
    //if the period changes to 100 seconds it doesn't log proper, at least it doesn't hang
    if (!stop && ts.tv_sec >= next) {
      //if (period < 60) {
      //print_current_time();
      print_current_temperature();
      next = ts.tv_sec + period;
      //}
      /*
	else {
		if (minute == tm->tm_min) {
		print_current_time();
		print_current_temperature();
		next = (tm->tm_sec + period) % 60;
		}
      */
    }
    if (poll(&pollfds, 1, 0) < 0) {
      fprintf(stderr, "Error polling input\n");
      exit(1);
    }
    if (pollfds.revents & POLLIN) {
      //fgets doesnt work here
      //fgets(input, 24, stdin);
      bytes_read = read(socketfd, input, 256);
      for (i = 0; i < bytes_read; ++i) {
	char c = input[i];
	if (parser >= 255) parser = 0;
	if (c == '\n') {
	  process[parser] = '\n';
	  handle_input(process, parser);
	  //memset(&process, '\0', sizeof(process));
	  parser = 0;
	}
	else {
	  process[parser] = c;
	  ++parser;
	}
      }
    }
  }
  
  mraa_gpio_close(button);
  mraa_aio_close(temperature);
  
  exit(0);
}
