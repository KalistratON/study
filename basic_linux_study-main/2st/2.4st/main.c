#include <stdio.h>

int main()
{
	char name[100];
	printf("What is your name? __");
	scanf("%s", name);
	return printf("Hello %s\n", name);
}
