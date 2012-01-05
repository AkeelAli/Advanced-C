#include "dbg.h"
#include <stdlib.h>
#include <stdio.h>

void main() {
	debug("I have Brown Hair.");
	
	debug("I am %d years old.", 37);
	
	log_err("Broken.");
	log_err("there exists %d problems.", 0, "space");
	
	check((1 == 0), "failed 1==0");
	
error:
	printf("in error\n");
}

/* check this site for more on how to make good use of dbg.h macros: 
http://c.learncodethehardway.org/book/learn-c-the-hard-waych21.html#x26-10500021 */