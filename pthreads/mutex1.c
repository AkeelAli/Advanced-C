/* using mutex to protect shared variables used for syncing */

/* this is not a good way of signaling, as polling is involved
	use a semaphore instead */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include "dbg.h"

#define WORK_SIZE 1024
char work_area[WORK_SIZE];
int time_to_exit = 0;
/* mutex protecting time_to_exit and work_area */
/* writing/reading to/from these two variables requires mutex lock */
pthread_mutex_t work_mutex;

void *thread_function(void *);

int main(void) {
	pthread_t a_thread;
	
	void *thread_result;

	check(pthread_mutex_init(&work_mutex, NULL) == 0, "Mutex init failed");
	
	check(pthread_create(&a_thread, NULL, thread_function, NULL) == 0, "Thread creation failed");
	
	pthread_mutex_lock(&work_mutex);
	printf("Input some text. Enter 'end' to finish\n");
	while (!time_to_exit) {
		fgets(work_area, WORK_SIZE, stdin);
		pthread_mutex_unlock(&work_mutex);
		
		/* wait until other thread reads our data from work_area and signals it with \0 */
		while(1) {
			pthread_mutex_lock(&work_mutex);
			if (work_area[0] != '\0') {
				pthread_mutex_unlock(&work_mutex);
				sleep(1);
			}
			else
				break;
		}
	}
	
	pthread_mutex_unlock(&work_mutex);
	printf("\nWaiting for thread to finish...\n");
	check(pthread_join(a_thread, &thread_result) == 0, "Thread join failed");
	
	printf("Thread joined\n");
	pthread_mutex_destroy(&work_mutex);
	exit(0);
	
error:
	exit(1);
}

void *thread_function(void *arg) {
	sleep(1);
	pthread_mutex_lock(&work_mutex);
	while(strncmp("end", work_area, 3) != 0) {
		/* process data in work_area and then signal finished processing by writing \0 to work_area */
		printf("You input %d, characters\n", strlen(work_area) -1);
		work_area[0] = '\0';
		pthread_mutex_unlock(&work_mutex);
		sleep(1);
		pthread_mutex_lock(&work_mutex);
		while (work_area[0] == '\0') {
			pthread_mutex_unlock(&work_mutex);
			sleep(1);
			pthread_mutex_lock(&work_mutex);
		}
	}
	
	time_to_exit = 1;
	work_area[0] = '\0';
	pthread_mutex_unlock(&work_mutex);
	pthread_exit(0);
}