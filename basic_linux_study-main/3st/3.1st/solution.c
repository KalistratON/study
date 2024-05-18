#include <unistd.h>
#include <stdio.h>

int main() {
	char path[50];
	char pid [10];
	
	if(sprintf(pid, "%d", (int)getpid()) < 0) {
		printf("Error : Bad sprintf - 1");
		return -1;
	}

	
	if(sprintf(path, "/proc/%s/stat", pid) < 0) {
		printf("Error : Bad sprintf - 2\n");
		return -1;
	}

	FILE* file = fopen(path, "r");
	if(!file) {

		printf("Error : File");
		return -1;
	}

	int i = 0;
	while(fscanf(file, "%s", pid) != EOF && i < 6) {
		printf("%s\n", pid);
		++i;
	}
	return 0;
}
