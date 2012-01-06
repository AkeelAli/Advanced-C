#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "dbg.h"

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

int main(void) {
	void *handle;
	void (*addvec)(int *, int *, int *, int);
	char *error;

	/* Dynamically load shared library that contains addvec() */
	handle = dlopen("./libvector.so", RTLD_LAZY);
	if (!handle) {
		log_err("%s", dlerror());
		exit(1);
	}

	/* Get a pointer to the addvec() function we just loaded */
	addvec = dlsym(handle, "addvec");
	if ((error = dlerror()) != NULL) {
		log_err("%s", error);
		exit(1);
	}

	/* Now we can call addvec() just like any other function */
	addvec(x, y, z, 2);
	printf("z = [%d %d]\n", z[0], z[1]);

	/* Unload the shared library */
	if (dlclose(handle) < 0) {
		log_err("%s", dlerror());
		exit(1);
	}

	return 0;
}
