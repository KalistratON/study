#include <signal.h>
#include <stdlib.h>
#include <stdio.h>

int i = 0;
int j = 0;

void SR(int sig)
{
	if (sig == SIGUSR1)
		i++;
	if (sig == SIGUSR2)
		j++;
	if (sig == SIGTERM)
	{
		printf("%d %d", i, j);
		exit(0);
	}
}

int main()
{
	signal(SIGUSR1, SR);
	signal(SIGUSR2, SR);
	signal(SIGTERM, SR);

	while(1) {}
}
