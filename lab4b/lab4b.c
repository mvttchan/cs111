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

#define B 4275
#define R0 100000.0

int period = 1;
char scale = 'F';
FILE* log_file = 0;
int stop = 0;
int log_flag = 0;
mraa_gpio_context button;
mraa_aio_context temperature;
time_t minute = 0;

float convert_temper_reading(int reading) {
  float R = 1023.0/((float) reading) - 1.0;
  R = R0 * R;
  float C = 1.0/(log(R/R0)/B + 1/298.15) - 273.15;
  float F = (C * 9) / 5 + 32;
  if(scale == 'F') return F;
  else return C;
}

void print_to_log(char* str) {
	fprintf(log_file, "%s\n", str);
	fflush(log_file);
}

void print_current_time() {
  struct timespec ts;
  struct tm *tm;
  clock_gettime(CLOCK_REALTIME, &ts);
  tm = localtime(&(ts.tv_sec));
  printf("%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
  if (log_flag) {
	  fprintf(log_file, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
	  fflush(log_file);
  }
}

void do_when_pushed() {
  print_current_time();
  printf("SHUTDOWN\n");
  if (log_flag) {
	  fprintf(log_file, "SHUTDOWN\n");
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
  printf("%.1f\n", temp);
  if (log_flag) {
	  fprintf(log_file, "%.1f\n", temp);
	  fflush(log_file);
  }
}

void handle_input(char* input) {
	int input_length = strlen(input);
	input[input_length - 1] = '\0';
	//Put this^ in the README file, that shit is the worst
  if(strcmp(input, "SCALE=F") == 0) {
    //printf("SCALE=F\n");
    if(log_flag) print_to_log("SCALE=F");
  }
  else if(strcmp(input, "SCALE=C") == 0) {
    //printf("SCALE=C\n");
    if(log_flag) print_to_log("SCALE=C");
  }
  else if(strcmp(input, "STOP") == 0) {
    //printf("STOP\n");
    if(log_flag) print_to_log("STOP");
    stop = 1;
  }
  else if(strcmp(input, "START") == 0) {
    //printf("START\n");
    if(log_flag) print_to_log("START");
    stop = 0;
  }
  else if(strcmp(input, "OFF") == 0) {
    //printf("OFF\n");
    if(log_flag) print_to_log("OFF");
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
	if (period > 59) {
		struct timespec ts;
		struct tm* tm;
		clock_gettime(CLOCK_REALTIME, &ts);
		tm = localtime(&(ts.tv_sec));
		minute = tm->tm_min + (period / 60);
	}
  }
  else if(*input == 'L') {
    if(strstr(input, "LOG") == NULL) return;
    //printf("%s\n", input);
	if (log_flag) {
		fprintf(log_file, "%s\n", input);
		fflush(log_file);
	}
  }
  else {
	  //printf("%s\n", input);
	  if (log_flag) print_to_log(input);
  }
}

int main(int argc, char* argv[]) {
  
  struct option options[] = {
    {"period", 1, NULL, 'p'},
    {"scale", 1, NULL, 's'},
    {"log", 1, NULL, 'l'},
    {0,0,0,0}
  };

  int c;
  while((c = getopt_long(argc, argv, "", options, NULL)) != -1) {
    switch(c) {
    case 'p':
      period  = atoi(optarg);
      break;
    case 's':
      scale = optarg[0];
      if(scale == 'F' || scale == 'C') break;
      fprintf(stderr, "Scale can only be F or C\n");
      exit(1);
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
    default:
      fprintf(stderr, "Error in arguments, supports period scale and log only\n");
      exit(1);
    }
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
  

  struct pollfd pollfds = {0, POLLIN, 0};
  char* input;
  input = (char*)malloc(24 * sizeof(char));
  if(input == NULL) {
    fprintf(stderr, "No more memory to allocate, torrent more RAM\n");
    exit(1);
  }

  struct timespec ts;
  struct tm* tm;
  time_t next = 0;
  while(1) {
	clock_gettime(CLOCK_REALTIME, &ts);
	tm = localtime(&(ts.tv_sec));
	//if the period changes to 100 seconds it doesn't log proper, at least it doesn't hang
    if(!stop && tm->tm_sec >= next) {
		if (period < 60) {
			print_temperature();
			next = (tm->tm_sec + period) % 60;
		}
		else {
			if (minute == tm->tm_min) {
				print_temperature();
				next = (tm->tm_sec + period) % 60;
			}
		}
    } 
    if(poll(&pollfds, 1, (period * 1000)) < 0) {
      fprintf(stderr, "Error polling input\n");
      exit(1);
    }
    if(pollfds.revents & POLLIN) {
      fgets(input, 24, stdin);
      handle_input(input);
    }
  }
  
  mraa_gpio_close(button);
  mraa_aio_close(temperature);
  
  exit(0);
}
