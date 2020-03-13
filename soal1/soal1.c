#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int cekangka(char argument[]) {
    //cek value argument kudu angka 1-9
    //saya ga sanggup mikir kalo kaya crontab ada angka yg negatif
    for(int cek=0; cek<strlen(argument); cek++) {
        if(argument[cek] < '1' || argument[cek] > '9') {
            return 0;
        }
    }
    //printf("weee\n");
    return 1;
}

int apakahbintang(char argument[]) {
    if(strlen(argument) == 1) {
        if(argument[0] == '*') {
            //printf("masuk gan\n");
            return 1;
        }
    }
    return 0;
}

void jalankan(char path[]) {
    char *argact[] = {"bash", path, NULL};
    execv("/bin/bash", argact); 
}

void perdaemonanduniawi() {
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

    if ((chdir("/home/boodboy/SISOP/modul2/prak")) < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

int main(int argc, char** argv) { 
    if(argc != 5) {
        printf("format argumen kaga bener!\n");
        printf("jumlah argumen harus ada 5!\n");
        exit(EXIT_FAILURE);
    }
    else {
        int isi[4];

        printf("kamu memasukkan %d arguments: \n", argc); 
        //cek semua value argumen tampilin
        for(int index = 0; index < argc; index++) {
            printf("isi[%d]: %s\n", index, argv[index]);
        } 

        //buat angka ala2 cronnya
        for(int i=1; i<=3; i++) {
            if(cekangka(argv[i])) {
                isi[i]=atoi(argv[i]);//ubah char ke int
            }
            else if(apakahbintang(argv[i])) {
                if(i == 3) {
                    isi[i]=-24;
                }
                else isi[i]=-60;
            }
            else {
                printf("format argumen ke %d: %s ga bener!\n", i, argv[i]);
                printf("ada yg ga angka atau ga bintang(*)!\n");
                exit(EXIT_FAILURE);
            }
        } 

        int detik = isi[1];
        int menit = isi[2];
        int jam   = isi[3];

        if(detik > 59 || menit > 59 || jam > 23) {
            printf("format argumen ga bener!\n");
            printf("format detik(0-59), menit(0-59), jam(0-23)!\n");
            exit(EXIT_FAILURE);
        }

        perdaemonanduniawi();
        char lokasi[80];
        strcpy(lokasi,argv[4]);

        while(1) {
            time_t rawtime;
            struct tm *uinfo;

            time(&rawtime);
            uinfo = localtime(&rawtime);

            pid_t child_id;
            child_id = fork();

            if((uinfo->tm_sec == detik || detik == -60) 
            && (uinfo->tm_min == menit || menit == -60)
            && (uinfo->tm_hour == jam || jam == -24)) {
                if(child_id == 0){
                    //child
                    //printf("aw\n");
                    jalankan(lokasi);
                }
                else {
                    //parent
                }
            }
            sleep(1);
        }
    }
    return 0;
}
