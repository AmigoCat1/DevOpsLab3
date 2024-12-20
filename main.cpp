#include <iostream>
#include "FuncCosh.h"
#include <sys/wait.h>

void sigchldHandler(int s)
{
	printf("Caught signal SIGCHLD\n");

	pid_t pid;
	int status;

	while ((pid = waitpid(-1,&status,WNOHANG)) > 0)
	{
		if (WIFEXITED(status)) printf("\nChild process terminated");
	}
}

void sigintHandler(int s)
{
	printf("Caught signal %d. Starting graceful exit procedure\n",s);

	pid_t pid;
	int status;
	while ((pid = waitpid(-1,&status,0)) > 0)
	{
		if (WIFEXITED(status)) printf("\nChild process terminated");
	}
	
	if (pid == -1) printf("\nAll child processes terminated");

	exit(EXIT_SUCCESS);
}

int CreateHTTPserver();

int main() {

    signal(SIGCHLD, sigchldHandler);	
    signal(SIGINT, sigintHandler);
    FuncCosh func;
    //double x;
    //int n;

    //std::cout << "Enter x and n: ";
    //std::cin >> x >> n;

    //std::cout << "Result function FuncCosh: " << func.calculate(x, n) << std::endl;

    //std::cout << "Start HTTP server" << std::endl;
    CreateHTTPserver();

    return 0;
}
