#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	printf("%i\n", atoi(argv[1]));
	addr.sin_port = htons(atoi(argv[1]));
	inet_aton("127.0.0.1", &addr.sin_addr);

	if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		printf("bind is not work\n");

	char str[BUFSIZ];
	const char off[] = "OFF\n";
	while (1)
	{
		size_t len = read(fd, str, BUFSIZ);

		if (strncmp(str, off, sizeof(off)) == 0)
			return 0;

		printf("%s\n", str);
		memset(str, 0, strlen(str));
		printf("%s\n", str);
	}


	return 0;
}
