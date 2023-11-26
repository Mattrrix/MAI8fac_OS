#include "function.h"

int main(){

    int fd2 = shm_open(
        MEMORY_NAME2, 
        O_CREAT | O_RDWR, 
        0666);

    char* addr2 = NULL;

    if( (addr2 = (char*)mmap(
        NULL, 
        MAX_LEN, 
        PROT_READ, 
        MAP_SHARED, 
        fd2, 
        0)) == (void*)-1){
        perror("\nerror mapping fd1 to memory\n");
        _exit(EXIT_FAILURE);
    }

    if(addr2 == MAP_FAILED){
        perror("\nmmap1 failed\n");
        _exit(EXIT_FAILURE);
    }
    
    while(true){
        // printf("%s, addr2\n",addr2);
        char *input_strint=NULL;
        // input_strint = addr2;
        int s_len=inputing(&input_strint, fd2, 0); 
        char* output_string=NULL;

        if ((input_strint[0]=='-')){
            continue;
        // } else if(s_len<=0 ){
        //     break;
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