#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	
	char path[50];
	char pid[50];	
	
	sscanf(argv[1], "%s", pid);
	if(sprintf(path, "/proc/%s/stat", pid) < 0) {
		printf("Error : Bad sprintf - 1\n");
		return -1;
	}

	printf("%s\n", pid);
	while(strcmp(pid, "1")) {
		
		FILE* file = fopen(path, "r");
		if(!file)
			return -1;
		
		while(fscanf(file, "%s", pid) != EOF && strcmp(pid, "S") && strcmp(pid, "R")) {
			
		}

		fscanf(file, "%s", pid);
		sprintf(path, "/proc/%s/stat", pid);
		printf("%s\n", pid);
		fclose(file);
	}
	return 0;
}
