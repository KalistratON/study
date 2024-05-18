#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

int main()
{
	int i;
	pid_t pid;
	if(pid = fork(), pid == -1)
		return -1;
	else if (pid)
		exit(EXIT_SUCCESS);

	if (setsid() == -1)
		return -1;

	if (chdir("/") == -1)
		return -1;

	pid = getpid();
	char path[60];

	sprintf(path, "/proc/%i/fd", pid);

	printf("%s\n", path);
	FILE* file = fopen(path, "r");

	if(!file){
		printf("Error : file");
		return -1;
	}

	
	printf("%d\n", getpid());
	for(i = 0; i < 10000; i++) {
		close(i);
	}


	open("/dev/null", O_RDWR);
	dup(0);
	dup(0);

	while(1) {};

	return 0;
}
