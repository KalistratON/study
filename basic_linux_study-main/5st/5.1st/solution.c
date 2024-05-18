#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>

int main(int argc, char* argv[])
{
	struct hostent* Host = gethostbyname(argv[1]);
	struct in_addr* a;
	size_t i = 0;
	while(Host->h_addr_list[i]) 
	{
		a = (struct in_addr*) Host->h_addr_list[i];
		printf("%s\n", inet_ntoa(*a));
		i++;
	}

	return 0;
}
