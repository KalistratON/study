#include <stddef.h>
#include <string.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

char* concat(char* str1, char* str2)
{
	char* result = malloc(strlen(str1) + strlen(str2) + 1);
	strcpy(result, str1);
	strcat(result, str2);
	return result;
}

int main(int argc, char* argv[])
{
	void* file = dlopen(argv[1], RTLD_LAZY);
	if(!file)
		printf("Error: %s", dlerror());

	int (*function)(int) = (int(*)(int))dlsym(file, argv[2]);
	
	if(!function)
		printf("Error: %s", dlerror());

	printf("%i\n", function(atoi(argv[3])));
	dlclose(file);
	return 0;
}
