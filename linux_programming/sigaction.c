#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch (int sig) {
	printf("OUCH!\n");
}

int main (void) {
	struct sigaction act;

	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;

	sigaction (SIGINT, &act, 0);

	while (1) {
		printf("Hello\n");
		sleep(1);
	}
}
