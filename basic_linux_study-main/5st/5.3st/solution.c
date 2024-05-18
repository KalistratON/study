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
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	//printf("%i\n", atoi(argv[1]));
	addr.sin_port = htons(atoi(argv[1]));
	inet_aton("127.0.0.1", &addr.sin_addr);

	if(bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0)
		printf("bind is not work\n");

	int k = 0;
	int fd_child;

	char str[BUFSIZ];
	const char off[] = "OFF\n";
	listen(fd, 128);
	fd_child = accept(fd, NULL, NULL);
	while (1)
	{

		int ss = read(fd_child, str, BUFSIZ);
		str[ss] = '\0';
		
		if (strncmp(str, off, sizeof(off)) == 0)
			break;

		int i = 0;
		for(i = 0; i < ss; i++)
		{
			int j = 1;
			for (j = 1; j < ss - i; j++)
			{
				if (str[j-1] < str[j])
				{
					char temp = str[j-1];
					str[j-1] = str[j];
					str[j] = temp;
				}
			}
		}

		write(fd_child, str, ss);
		memset(str, 0, strlen(str));
	}
	close(fd);
	return 0;
}
