#include "function.h"

int main(){

    int fd2 = shm_open(
        MEMORY_NAME2, 
        O_RDONLY, 
        S_IRUSR | S_IWUSR);

    char* addr2 = (char*)mmap(
        NULL, 
        MAX_LEN, 
        PROT_READ, 
        MAP_SHARED, 
        STDIN_FILENO, 
        0);
    if(addr2 == MAP_FAILED){
        perror("\n(child2)nmmap: there is a problem\n");
        _exit(EXIT_FAILURE);
    }

    while(true){
        char *input_strint=NULL;
        int s_len=inputing(&input_strint, STDIN_FILENO, 0); 
        char* output_string=NULL;

        if ((input_strint[0]=='-')){
            continue;
        } else if(s_len<=0 ){
            break;
        } else{
            if(string_invert(&output_string, input_strint, s_len)==0){
                write(STDOUT_FILENO, " String_invert Error2! ", 24);
                break;
            } else{
                write(STDOUT_FILENO, output_string, s_len*sizeof(char));
            }
        }
    }
    return 0;
}