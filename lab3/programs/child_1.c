#include "function.h"

int main(){

    int fd1= shm_open(MEMORY_NAME1, O_RDONLY, S_IRUSR | S_IWUSR);
    check_error(fd1 == -1, "Can't open shared memory file");
    res *addr1 = mmap(NULL, MEMORY_SIZE, PROT_READ, MAP_SHARED, fd1, 0);
    check_error(addr1 == (void*)-1, "Mmap error");

    while(true){
        char *input_strint=NULL;
        int s_len=inputing(&input_strint, fd1, 0); 

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
