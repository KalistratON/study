#include <stdio.h>

int main(int argc, char* argv[])
{
	char command[80];
	char temp;
	sprintf(command, "./%s %s", argv[1], argv[2]);

	size_t sum = 0;

	FILE* file = popen(command, "r");
	while(temp = fgetc(file), temp != EOF)
	{
		if (temp == '0')
			++sum;
	}
	printf("%ld\n", sum);
	pclose(file);
	return 0;
}
