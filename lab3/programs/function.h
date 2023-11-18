#ifndef function_h
#define function_h
#include <stdio.h>
#include <fcntl.h> //files
#include <stdlib.h> //malloc, srand, rand
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h> //pid_t, ftruncate
#include <signal.h> // kill
#include <time.h> //time(NULL)
#include <sys/mman.h>
#include "stddef.h"
#include <string.h>
#include <sys/stat.h>

#define MAX_LEN 255 // max length for file's names and strings/files in 3rd lab
#define SIGTERM 15
#define MEMORY_NAME1 "fd_virt1"
#define MEMORY_NAME2 "fd_virt2"


int inputing(char **output_name, int fd, int endl_status);
void pipe_creation(int *fd);
int process_creation();
bool string_invert(char **output_string, char* input_string, int len);
int probability();

#endif
