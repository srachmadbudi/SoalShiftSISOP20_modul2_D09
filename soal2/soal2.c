#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void unduh() {
    
    
    char *argv[] = {"wget", "-o", tujuan, web, NULL};
	execv("/bin/wget", argv);
}

int main () {
	time_t rawtime;
   	struct tm *info;
   	char buffer[80];

   	time( &rawtime );

   	info = localtime( &rawtime );

   	strftime(buffer,80,"%Y-%m-%d_%H:%M:%S", info);
  	// printf("Formatted date & time : |%s|\n", buffer );

	pid_t child_id;
	child_id = fork();

	int status;

	if(child_id < 0) {
		exit(EXIT_FAILURE);
	}

	if(child_id == 0) {
		char *argv[] = {"mkdir", "-p", buffer, NULL};
		execv("/bin/mkdir", argv);
	}
	else {
		while ((wait(&status))>0);
        for(int download=1;download<=20;download++) {
		    if(fork()==0) {
                //unduh();
            }
            else {
                //parent
            }
        }
	}
   return(0);
}
