#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


int main(int argc,char *argv[])
{
    int pipe_pread_cwrite[2];
    int pipe_pwrite_cread[2];

    pid_t cpid;

    const int MSG_LENGTH=5;

    char msg[MSG_LENGTH];

    if(pipe(pipe_pread_cwrite)==-1){
        perror("pipe create 1");
        exit(EXIT_FAILURE);
    }

    if(pipe(pipe_pwrite_cread)==-1){
        perror("pipe create 2");
        exit(EXIT_FAILURE);
    }

    cpid=fork();

    if(cpid==-1){
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if(cpid==0){
        //child process
        close(pipe_pread_cwrite[0]);
        close(pipe_pwrite_cread[1]);

        while(1){
            int length = read(pipe_pwrite_cread[0],msg,MSG_LENGTH);
            if(length>0){
                printf("child read msg from parent,content is %s\n",msg);
            }
            strcpy(msg,"pong");
            write(pipe_pread_cwrite[1],msg,MSG_LENGTH-1);
            sleep(1);
        }
    }else{
        close(pipe_pread_cwrite[1]);
        close(pipe_pwrite_cread[0]);
        while(1){
            strcpy(msg,"ping");
            write(pipe_pwrite_cread[1],msg,strlen(msg));
            sleep(1);
            int length=read(pipe_pread_cwrite[0],msg,MSG_LENGTH);
            if(length>0){
                printf("parent read msg from child,content is %s\n",msg);
            }
        }

    }
    return 0;
}
