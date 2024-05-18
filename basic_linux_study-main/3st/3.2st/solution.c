 #define _DEFAULT_SOURCE
       #include <dirent.h>
       #include <stdio.h>
       #include <stdlib.h>
	#include <string.h>


       	int main()
       	{
       	   struct dirent **namelist;
           int n;

           n = scandir("/proc", &namelist, NULL, alphasort);
           if (n == -1) {
               	perror("scandir");
               	exit(EXIT_FAILURE);
           }

	   char str [50];
	   sprintf(str, "%s", "abc");
	   
	   int count = 0;
           while (n--) {

		char path [50];
		char name [50];
		sprintf(path, "/proc/%s/comm", namelist[n]->d_name);			
		
		FILE* file = fopen(path, "r");
		if(file && (fscanf(file, "%s", name) >= 0)) {
			//printf("%s\t\t : %s\n", path, name);
			if (!strcmp(name, "genenv"))
				count++;
		}
               	free(namelist[n]);
           }
           free(namelist);
	   printf("%d\n", count);
           exit(EXIT_SUCCESS);
       	}

