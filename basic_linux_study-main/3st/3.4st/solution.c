#include <unistd.h>
#include <stdio.h>
#include <string.h>

int countChildren(FILE* file, char* ppid, int count)
{
        //printf("count : %d\n", count);
        //printf("current ppid : %s\n", ppid);

        char path [50];

        if(sprintf(path, "/proc/%s/task/%s/children", ppid, ppid) < 0) {
                //printf("Error : sprintf");
                return -1;
        }

        if (file = fopen(path, "r"), !file) {
                //printf("Error : file");
                return count;
        }

        while(fscanf(file, "%s", ppid) != EOF) {
                //printf("while : ppid : %s", ppid);
                count += 1;
                count = countChildren(file, ppid, count);
        }
        return count;
}

int main(int argc, char* argv[]) {

        char ppid[50];
        FILE* file;

        sscanf(argv[1], "%s", ppid);


        printf("%i\n", countChildren(file, ppid, 0) + 1);
        return 0;
}

