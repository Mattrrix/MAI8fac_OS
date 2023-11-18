#include "function.h"

int main(){

    write(STDOUT_FILENO, "Enter the first filename with file extension(.txt or .doc or .rtf): \n", 67);

    char *Filename_1=NULL;

    if(inputing(&Filename_1 ,STDIN_FILENO, 0)<=0){
        perror("Trying to create 0-value string: ");
        exit(-1);
    }

    int f1_output=open(Filename_1, O_WRONLY | O_CREAT, 0777);

    if(f1_output==-1){
        fprintf(stderr, "Can't open the file:  %s", Filename_1);
        exit(-1);
    }

    int fd1 = shm_open(
        MEMORY_NAME1, 
        O_CREAT | O_RDWR, 
        0666);

     if (ftruncate(fd1, MAX_LEN) == -1) {
        perror("\nftruncate1 error:\n");
        exit(EXIT_FAILURE);
    }
    
    char* addr1 = NULL;

    if( (addr1 = (char*)mmap(
        NULL, 
        MAX_LEN, 
        PROT_WRITE | PROT_READ, 
        MAP_SHARED, 
        fd1, 
        0)) == (void*)-1){
        perror("\nerror mapping fd1 to memory\n");
        _exit(EXIT_FAILURE);
    }

    if(addr1 == MAP_FAILED){
        perror("\nmmap1 failed\n");
        _exit(EXIT_FAILURE);
    }

    pid_t pid_1 = process_creation();
    if (pid_1 == 0){
        // the 1st child

        if(dup2(f1_output, STDOUT_FILENO)==-1){
            perror("dup2 error: ");
            exit(-1);
        }

        if(dup2(f1_output, STDERR_FILENO)==-1){
            perror("dup2 error: ");
            exit(-1);
        }
          
        if(execl("./child_1", "./child_1", NULL)==-1){
            perror("execl error: ");
            exit(-1);
        }

    }else { 
        // parent
        write(STDOUT_FILENO, "\nEnter the second filename with file extension(.txt or .doc or .rtf): ", 71);
        char *Filename_2=NULL;

        if(inputing(&Filename_2 ,STDIN_FILENO, 0)<=0){
            perror("Trying to create 0-value string: ");
            exit(-1);
        }
        
        int f2_output=open(Filename_2, O_WRONLY | O_CREAT, 0777);
        if(f2_output==-1){
            fprintf(stderr, "Can't open the file:  %s", Filename_2);
            exit(-1);
        }

        int fd2 = shm_open(
            MEMORY_NAME2, 
            O_CREAT | O_RDWR, 
            0666);

        if (ftruncate(fd2, MAX_LEN) == -1) {
            perror("\nftruncate2 error:\n");
            exit(EXIT_FAILURE);
        }

        char* addr2 = NULL;

        if( (addr2 = (char*)mmap(
            NULL, 
            MAX_LEN, 
            PROT_WRITE | PROT_READ, 
            MAP_SHARED, 
            fd2, 
            0))== (void*)-1)
        {
            perror("\nerror mapping fd1 to memory: \n");
            _exit(EXIT_FAILURE);
        }

        if(addr2 == MAP_FAILED){
            perror("\nmmap failed:\n");
            _exit(EXIT_FAILURE);
        }

        pid_t pid_2=process_creation();
        if(pid_2==0){
            //the 2nd child
            close(f1_output);

            if(dup2(f2_output, STDOUT_FILENO)==-1){
                perror("dup2 error: ");
                exit(-1);
            }
            if(dup2(f2_output, STDERR_FILENO)==-1){
                perror("dup2 error: ");
                exit(-1);
            }
            
            if(execl("./child_2", "./child_2", NULL)==-1){
                perror(" execl error: ");
                exit(-1);
            }

        } else{ 
            // parent
            if(write(STDOUT_FILENO, "Enter something you want: ", 27) == -1){
                        perror("write error: ");
                        exit(-1);
                    }
            while(true){
                char*s=NULL;
                char str[1] = "-";
                int s_len=inputing(&s, STDIN_FILENO, 1);

                if(s_len==-1){
                    break;
                }

                int prob_res=probability();

                if (prob_res==1){

                    strcpy(addr1, s);
                    // printf("%s, addr1\n",addr1);
                    strcpy(addr2, str);
                    // printf("%s, addr2\n",addr2);

                }else{
                    
                    strcpy(addr2, s);
                    // printf("%s, addr2\n",addr2);
                    strcpy(addr1, str);
                    // printf("%s, addr1\n",addr1);

                }
            }
            if(munmap(addr1, MAX_LEN) == -1){
                perror("mumap1 error:");
                _exit(EXIT_FAILURE);
            }
            if(munmap(addr2, MAX_LEN) == -1){
                perror("mumap2 error:");
                _exit(EXIT_FAILURE);
            }
            if(shm_unlink(MEMORY_NAME1) == -1){
                perror("shm_unlink error:");
                _exit(EXIT_FAILURE);
            }
            if(shm_unlink(MEMORY_NAME2) == -1){
                perror("shm_unlink error:");
                _exit(EXIT_FAILURE);
            }
            close(fd1);
            close(fd2);
            close(f1_output);
            close(f2_output);
        	kill(pid_1, SIGTERM);
            kill(pid_2, SIGTERM);
            write(STDOUT_FILENO, "\nProgramm was ended successfully!\n", 35);
        }
    }
}

