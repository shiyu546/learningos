#define _GNU_SOURCE
#include<stdio.h>

// #define _GNU_SOURCE
#include<pthread.h>


void* func(void *arg){
	while(1){
        pthread_yield();
	}
}

int main()
{
    pthread_t thread_ids[2];
    for(int i=0;i<2;++i){
        pthread_create(&thread_ids[i],NULL,func,NULL);
    }

    for(int i=0;i<2;++i){
        pthread_join(thread_ids[i],NULL);
    }
}


