#include <stdio.h>
#include <sys/select.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int Read(int fd)
{
	char buf[100];
	int bytes = read(fd, buf, 100);
	buf[bytes] = '\0';
	int sum = 0;
	int i;
	for (i = 0; i < bytes; i++)
		sum += (int)buf[i] - (int)'0';
	return sum;

}

int main()
{
	int file1 = open("in1", O_RDONLY | O_NONBLOCK);
	int file2 = open("in2", O_RDONLY | O_NONBLOCK);
	
	struct timeval  tv;	
	tv.tv_sec = 5;
	tv.tv_usec = 0;


	if (!(file1 && file2)) {
		printf("Error with files\n");
		return -1;
	}

	fd_set SET;
	int sum = 0;
	int flag1 = 1;
	int flag2 = 1;
	
	while(1) 
	{

		FD_ZERO(&SET);

		if(flag1 + flag2 == 0)
		{
			printf("%d\n", sum);
                        return 0;

		}

		if (flag1)
			FD_SET(file1, &SET);
		if (flag2)
			FD_SET(file2, &SET);

		int result = select(file1 > file2 ? file1 + 1 : file2 + 1, &SET, NULL, NULL, &tv);
		
		if(result)
		{
			if(FD_ISSET(file1, &SET)) 
				sum += Read(file1);
			else
			{
				FD_CLR(file1, &SET);
				close(file1);
				flag1 = 0;
			}		
			if(FD_ISSET(file2, &SET))
				sum += Read(file2);		
			else
			{
				FD_CLR(file2, &SET);
				close(file2);
				flag2 = 0;
			}		

		}
		else
		{
			printf("%d\n", sum);
			return 0;
		}
	}
}
