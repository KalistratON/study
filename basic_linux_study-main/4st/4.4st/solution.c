#include <unistd.h>

#include <stdio.h>

#include <stdlib.h>
#include <signal.h>
void foo(int fd)
{
	exit(0);
}


int main() {

    pid_t pid; // new pid


    pid = fork(); // forking our main program


    if (pid > 0) // let the parent finish
        exit(0);


    chdir("/"); // changing to root dir


    if (setsid() < 0) // setting new session id
        exit(0);
	
    signal(SIGURG, foo);

    printf("%d\n", getpid());


    close(0); // close stdin, stdout, stderr

    close(1);

    close(2);

    

    while(1) {}; // this was unexpected, but as someone said - what kinds of daemon is it 

                 // if it dies. Makes sense. 

    return 0;

}

