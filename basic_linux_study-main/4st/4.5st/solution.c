#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[])
{
	const long SIZE = 1000 * sizeof(char);
	long long key_1, key_2;
	key_1 = atoll(argv[1]);
	key_2 = atoll(argv[2]);

	key_t KEY_1 = shmget((key_t)key_1, SIZE, IPC_CREAT | 0600);
	key_t KEY_2 = shmget((key_t)key_2, SIZE, IPC_CREAT | 0600);

	if (KEY_1 < 0 || KEY_2 < 0)
	{
		printf("ERROR : SHMGET");
		exit(1);

	}
	
	int* ptr_1 = (int*) shmat(KEY_1, NULL, 0);
	int* ptr_2 = (int*) shmat(KEY_2, NULL, 0);

	int* ext_ptr_1 = ptr_1;
	int* ext_ptr_2 = ptr_2;

	if (ptr_1 == (int*) -1 || ptr_2 == (int*) -1)
	{

		printf("ERROR : SHMAT");
		exit(1);

	}

	key_t key; 
    	if((key = ftok(".", 0)) < 0) {
        	printf("Can\'t generate key\n");
		exit(1);
	}


	key_t KEY = shmget((key_t)key, SIZE, IPC_CREAT | 0666);

	if (KEY < 0)
	{
		printf("ERROR : SHMGET : OUT");
		exit(1);

	}
	
	int* ptr = (int*) shmat(KEY, NULL, 0);
	int* ext_ptr = ptr;
	if (ptr == (int*) -1)
	{

		printf("ERROR : SHMAT : OUT");
		exit(1);

	}

	int i;
	for (i = 0; i < 100; i++)
	{
		ptr[i] = ptr_1[i] + ptr_2[i];
	//	printf("%d + %d == %d\n", ptr_1[i], ptr_2[i], ptr[i]);
	}
	shmdt(ext_ptr_1);
	shmdt(ext_ptr_2);
	shmdt(ext_ptr);
	printf("%lld\n", key);

	return 0;
}
