#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main(){
   pid_t child_id_1, child_id_2, child_id_3, child_id_4, child_id_5,
	child_id_6, child_id_7;
   int status;
   char zipfile[50];
   char dir_name[300];
   DIR *d;
   struct dirent *dir;

   if((child_id_1=fork()) == 0){
	char *argv[] = {"/bin/mkdir","-p", "/home/elaaaaaaa/Modul2/indomie", NULL};
	execv(argv[0], argv);
	printf("Error 1");
   }

   while ((wait(&status))>0);
   if((child_id_2=fork()) == 0){
	sleep(5);
	char *argv[] = {"/bin/mkdir","-p", "/home/elaaaaaaa/Modul2/sedaap", NULL};
	execv(argv[0], argv);
	printf("Error 2");
   }

   while ((wait(&status))>0);
   if((child_id_3=fork()) == 0){
	sprintf(zipfile, "/home/elaaaaaaa/Modul2/jpg.zip");
	char *argv[] = {"/usr/bin/unzip", zipfile, NULL};
	execv(argv[0], argv);
	printf("Error 3");
   }

   while ((wait(&status))>0);
   if((child_id_4=fork()) == 0){
	char *argv[] = {"/usr/bin/find", "/home/elaaaaaaa/Modul2/jpg", "-mindepth", "1", "-maxdepth", "1", "-type", "d", "-exec", "mv","-t", "/home/elaaaaaaa/Modul2/indomie", "{}", ";", NULL};
	execv(argv[0], argv);
	printf("Error 4");
   }

   while ((wait(&status))>0);
   if((child_id_5=fork()) == 0){
	char *argv[] = {"/usr/bin/find", "/home/elaaaaaaa/Modul2/jpg", "-mindepth", "1", "-maxdepth", "1", "-type", "f", "-exec", "mv","-t", "/home/elaaaaaaa/Modul2/sedaap", "{}", ";", NULL};
	execv(argv[0], argv);
	printf("Error 5");
   }

   while ((wait(&status)) > 0);
   if((child_id_6=fork()) == 0){
	char *argv[] = {"/usr/bin/find", "/home/elaaaaaaa/Modul2/indomie", "-mindepth", "1", "-type", "d", "-exec", "touch", "{}/coba1.txt",";", NULL};
    	execv(argv[0], argv);
	/*d = opendir("/home/elaaaaaaa/Modul2/indomie");
	if (d){
	   while ((dir = readdir(d)) != NULL){
		sprintf(dir_name, "/home/elaaaaaaa/Modul2/indomie/%s/coba1.txt", dir->d_name);
		char *argv[] = {"/usr/bin/touch", dir_name , NULL};
    		execv(argv[0], argv);
		printf("erorr_text1");
	   }
	   closedir(d);
	} */
   } 

     while ((wait(&status)) > 0);
     if((child_id_7=fork()) == 0){
	sleep(3);
	char *argv[] = {"/usr/bin/find", "/home/elaaaaaaa/Modul2/indomie", "-mindepth", "1", "-type", "d", "-exec", "touch", "{}/coba2.txt",";", NULL};
    	execv(argv[0], argv);
	/*d = opendir("/home/elaaaaaaa/Modul2/indomie");
	if (d){
	   while ((dir = readdir(d)) != NULL){
		sprintf(dir_name, "/home/elaaaaaaa/Modul2/indomie/%s/coba2.txt", dir->d_name);
		char *argv[] = {"/usr/bin/touch", dir_name , NULL};
		execv(argv[0], argv);
		printf("erorr_text2");
	   }
	   closedir(d);
	}*/
   }
  while ((wait(&status)) > 0);
  return 0;
}
