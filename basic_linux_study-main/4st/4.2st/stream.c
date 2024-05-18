#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	mkfifo("in1", 0777);
	mkfifo("in2", 0777);

	while(1) {};

	return 0;
}
