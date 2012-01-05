/* binary semaphore used to signal to a thread that input is available */
/* signaling semaphores are initialized to 0 (i.e locked) and need to get a post to signal another thread waiting on the semaphore */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "dbg.h"

void *thread_function(void *arg);

sem_t bin_sem;

#define WORK_SIZE 1024
char work_area[WORK_SIZE];

int main(void) {
	int res;
	pthread_t a_thread;
	void *thread_result;
	
	check(sem_init(&bin_sem, 0, 0) == 0, "sem_init failed");
	
	check(pthread_create(&a_thread, NULL, thread_function, NULL) == 0, "pthread_create failed");
	
	printf("Input some text. Enter 'end' to finish\n");
	while(strncmp("end", work_area, 3) != 0) {
		fgets(work_area, WORK_SIZE, stdin);
		sem_post(&bin_sem);
	}
	
	printf("\nWaiting for thread to finish...\n");
	check(pthread_join(a_thread, &thread_result) == 0, "pthread_join failed");
	
	printf("Thread joined\n");
	
	sem_destroy(&bin_sem);
	
	return 0;
	
error:
	if (thread_result) free(thread_result);
	return 1;
}

void *thread_function(void *arg) {
	sem_wait(&bin_sem);
	
	while(strncmp("end", work_area, 3) != 0) {
		printf ("You input %d characters\n", strlen(work_area) -1);
		sem_wait(&bin_sem);
	}
	pthread_exit(NULL);
}