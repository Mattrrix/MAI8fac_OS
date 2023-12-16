#include "function.h"

char * file_mmf_global;
int i_global = 0;

void writer(){
    int c;
    char* output_string=NULL;
    char* input_strint=NULL;
    int input_strint_size = 0; // переменная, хранящая текущий размер input_strint
    for (int i = i_global ; i < MAX_LEN; i++) {
        c = file_mmf_global[i];
        // Выделяем память для input_strint
        input_strint = realloc(input_strint, (input_strint_size + 2) * sizeof(char)); // +2 для символа c и завершающего нуля
        input_strint[input_strint_size] = c; // записываем символ
        input_strint[input_strint_size + 1] = '\0'; // добавляем завершающий нуль
        input_strint_size++; // увеличиваем размер
        if (c == '\n'){
            i_global = i + 1;
            break;
        }
    }
    if(string_invert(&output_string, input_strint, strlen(input_strint))==0){
        write(STDOUT_FILENO, " String_invert Error2! ", 24);
    } else{
        write(STDOUT_FILENO, output_string, input_strint_size*sizeof(char));
    }
}

void quit(){
	munmap(file_mmf_global, MAX_LEN);
    exit(0);
}

int main(int argc, const char *argv[]){

    int a = atoi(argv[1]);

	int shm_fd = 0;
	if (a == 1) {
		shm_fd = shm_open(MEMORY_NAME1, O_RDWR, S_IRUSR);
	}
	else {
		shm_fd = shm_open(MEMORY_NAME2, O_RDWR, S_IRUSR);
	}

    char *file_mmf =  mmap(NULL, MAX_LEN,  PROT_WRITE |PROT_READ , MAP_SHARED , shm_fd,0);
    
    if (file_mmf== (void*)-1)
        {
            perror("\nerror mapping fd1 to memory: \n");
            _exit(EXIT_FAILURE);
        }

    file_mmf_global = file_mmf;

    signal (SIGUSR1, writer);
	signal (SIGUSR2, quit);
	while (true);
}