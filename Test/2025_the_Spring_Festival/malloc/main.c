#include <stdio.h>
#include <stdlib.h>

int main()
{
	size_t size = 1024;
	void *ptr = malloc(size);


	if (ptr == NULL) {
		perror("malloc failed");
		return EXIT_FAILURE;
	}

	printf("Memory allocated at: %p\n", ptr);
	return EXIT_SUCCESS;
}


