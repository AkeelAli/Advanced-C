#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int signal_triggered = 0;

void ouch (int sig) {
	signal_triggered = 1;
}

int main() {
    
	signal (SIGINT, &ouch);
	
	while(1) {
		printf("Hello World!\n");
		sleep(1);
		if (signal_triggered) {
			printf("triggerd!\n");
			signal_triggered = 0;
		}
	}
}
