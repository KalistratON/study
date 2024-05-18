#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	const long SIZE = 1000 * sizeof(char);
	key_t key_1, key_2;
	key_1 = 456764;
	key_2 = 456768;

	int KEY_1 = shmget(key_1, SIZE, IPC_CREAT | 0666);
	int KEY_2 = shmget(key_2, SIZE, IPC_CREAT | 0666);

	if (KEY_1 < 0 || KEY_2 < 0)
	{
		printf("ERROR : SHMGET");
		exit(1);

	}
	
	int* ptr_1 = (int*) shmat(KEY_1, NULL, 0);
	int* ptr_2 = (int*) shmat(KEY_2, NULL, 0);

	int* ext_ptr_1 = ptr_1;
	int* ext_ptr_2 = ptr_2;

	if (ptr_1 == (char*) -1 || ptr_2 == (char*) -1)
	{

		printf("ERROR : SHMAT");
		exit(1);

	}

	int i;
	for (i = 0; i < 100; i++)
	{
		ptr_1[i] = i;
		ptr_2[i] = i;
	}

	while(1) {}

	return 0;
}
