#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>

int main(int arg, char **argument) {
  if(arg != 2){
	printf("Argument not valid");
	exit(0);
  }
  pid_t pid, sid;        // Variabel untuk menyimpan PID

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  FILE *fp;
  int stat;
  fp = fopen("/home/elaaaaaaa/Soal2/killer.sh", "w+");
  if(strcmp(argument[1], "-a") == 0)
  {
	fprintf(fp, "#!/bin/bash\nkill -9 %d\nrm killer", getpid());
  }
  if(strcmp(argument[1], "-b") == 0)
  {
	fprintf(fp, "#!/bin/bash\nkill %d\nrm killer", getpid());
  }

  
  if(fork() == 0)
  {
     if(fork() == 0)
     {
	char *args[] = {"chmod", "u+x", "/home/elaaaaaaa/Soal2/killer.sh", NULL};
	execv("/bin/chmod", args);
     }
     else
     {
	while(wait(&stat) > 0);
	char *args[] = {"mv", "/home/elaaaaaaa/Soal2/killer.sh", "killer", NULL};
	execv("/bin/mv", args);
     }
  }

  fclose(fp);

 
  while (1) {
  int status;

  if(fork() == 0)
  {
	time_t rawtime;
  	struct tm *info;
  	time(&rawtime);
  	char buff[32], folder[80];
  	info = localtime(&rawtime);
  	strftime(buff, sizeof(buff), "%Y-%m-%d_%H:%M:%S", info);
	strcpy(folder, "/home/elaaaaaaa/Soal2/");
	strcat(folder, buff);

	if(fork() == 0)
	{
	   //buat folder
	   char *args[] = {"mkdir", "-p", folder, NULL};
	   execv("/bin/mkdir", args);
	}
	else
	{
	   while(wait(&status) > 0);
	   printf("berhasil buat directory");
	   if(fork() == 0)
	   {
		//download 2 gambar dari link
		chdir(folder);
		int i;
		for(i=0; i<20; i++)
		{
		   if(fork() == 0)
		   {
			time_t fileTime;
  			struct tm *infotime;
  			time(&fileTime);
  			char file[512];
  			infotime = localtime(&fileTime);
  			strftime(file, sizeof(file), "%Y-%m-%d_%H:%M:%S", infotime);
			int t = (int) time(NULL);
			t = (t%1000) + 100;

			char url[512];
			sprintf(url, "http://picsum.photos/%d", t);

			char *args[] = {"wget", "-O", file, url, NULL};
			execv("/usr/bin/wget", args);
		   }
		   sleep(5);
		}
		exit(0);
	   }
	   else
	   {
		//menzip folder		
		while(wait(&status) > 0);
		char zipFile[512];
		sprintf(zipFile, "%s.zip", folder);
		char *args[] = {"zip", "-rm", zipFile, folder, NULL};
		execv("/usr/bin/zip", args);
	   }
	}
     }
     else 
     {
	sleep(30);
     }
    
  }
}
