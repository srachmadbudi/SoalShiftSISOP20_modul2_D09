# SoalShiftSISOP20_modul2_D09
```
Rachmad Budi Santoso    05111840000122
Khofifah Nurlaela       05111840000025
```
## soal1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut: <br/>
(a) Program menerima 4 argumen berupa: <br/>
i. Detik: 0-59 atau * (any value) <br/>
ii. Menit: 0-59 atau * (any value) <br/>
iii. Jam: 0-23 atau * (any value) <br/>
iv. Path file .sh  <br/>
(b) Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai <br/>
(c) Program hanya menerima 1 config cron <br/>
(d) Program berjalan di background (daemon) <br/>
(e) Tidak boleh menggunakan fungsi system() <br/>

### Jawaban
```
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
```

## soal2
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, 
suatu hari Kiwa iseng membuat sebuah program. <br/>
(a) Pertama-tama, Kiwa  membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder 
dengan nama timestamp [YYYY-mm-dd_HH:ii:ss]. <br/>

Untuk membuat suatu folder menggunakan perintah berikut.
```
if(child_id == 0) {
   char *argv[] = {"mkdir", "-p", buffer, NULL};
   execv("/bin/mkdir", argv);
}
```
Agar folder yang dibuat diberi dengan nama timestamp, digunakan perintah berikut.
```
time_t rawtime;
struct tm *info;
time(&rawtime);
char buff[32], folder[80];
info = localtime(&rawtime);
strftime(buff, sizeof(buff), "%Y-%m-%d_%H:%M:%S", info);
strcpy(folder, "/home/elaaaaaaa/Soal2/");
strcat(folder, buff);
```
Dimana : <br/>
`time( &rawtime )` merupakan variable dengan type data time. <br/>
`info = localtime( &rawtime )` untuk mendapatkan timestamp dari komputer. <br/>
`strftime(buffer,80,"%Y-%m-%d_%H:%M:%S", info)` untuk mengisi variable `buffer` dengan timestamp yang didapat sesuai format
[YYYY-mm-dd_HH:ii:ss]. <br/>

(b) Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 
detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama 
dengan format timestamp [YYYYmm-dd_HH:ii:ss]. <br/>
Untuk mendownload gambar dari link yang tersedia menggunakan perintah berikut:
```
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
```

(c) Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan 
.zip). <br/>

```
char zipFile[512];
sprintf(zipFile, "%s.zip", folder);
char *args[] = {"zip", "-rm", zipFile, folder, NULL};
execv("/usr/bin/zip", args);
```

(d) Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut mengenerate sebuah program "killer" yang siap di 
run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete 
dirinya sendiri. <br/>

```
fprintf(fp, "#!/bin/bash\nkill -9 %d\nrm killer", getpid());
```

(e) Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. Untuk mengaktifkan MODE_A, program harus 
dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama 
akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program 
utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu 
di delete). <br/>

```
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
```

### Kendala
Program killer untuk menterminasi semua operasi program tersebut tidak berjalan ketika dijalankan dengan argumen -a.

## soal3
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus 
dikerjakan secara bersamaan (multiprocessing). <br/>
(a) Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu 
lima detik kemudian membuat direktori yang kedua bernama “sedaap”. <br/>
Membuat direktori 'indomie'.
```
if((child_id_1=fork()) == 0){
	char *argv[] = {"/bin/mkdir","-p", "/home/elaaaaaaa/Modul2/indomie", NULL};
	execv(argv[0], argv);
  }
```
Lima detik setelah membuat direktori 'sedaap'. Untuk menjeda selama 5 detik digunakan system call `sleep`.
```
if((child_id_2=fork()) == 0){
	sleep(5);
	char *argv[] = {"/bin/mkdir","-p", "/home/elaaaaaaa/Modul2/sedaap", NULL};
	execv(argv[0], argv);
   }
```

(b) Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, 
ternyata tidak hanya itu tugasnya. 
```
if((child_id_3=fork()) == 0){
	sprintf(zipfile, "/home/elaaaaaaa/Modul2/jpg.zip");
	char *argv[] = {"/usr/bin/unzip", zipfile, NULL};
	execv(argv[0], argv);
   }
```

(c) Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus  
dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus 
dipindahkan ke “/home/[USER]/modul2/indomie/”. 
```
  if((child_id_4=fork()) == 0){
	char *argv[] = {"/usr/bin/find", "/home/elaaaaaaa/Modul2/jpg", "-mindepth", "1", "-maxdepth", "1", "-type", "d", "-exec", "mv","-t", "/home/elaaaaaaa/Modul2/indomie", "{}", ";", NULL};
	execv(argv[0], argv);
   }
```
Untuk memindahkan semua direktori yang ada di jpg ke direktori indomie, kita harus mengelompokkan dulu mana yang termasuk direktori dan 
mana yang termasuk file. Caranya dengan menggunakan command `find`. Secara lengkapnya : <br/>
`find /home/elaaaaaaa/modul2/jpg -maxdepth 1 -mindepth 1 -type d -exec mv '{}' /home/elaaaaaaa/modul2/indomie/ \;`
`/home/elaaaaaaa/modul2/jpg` merupakan root directory. <br/>
`-maxdepth 1` artinya hanya memproses di root directory. <br/>
`-mindepth 1` artinya memproses semua direktori yang ada di root directory kecuali root directory.<br/>
`-type d` untuk menyeleksi yang merupakan direktori. <br/>
`-exec mv ` perintah untuk memindahkan direktori. <br/>
`'{}'` artinya untuk setiap direktori yang ada di root directory. <br/>
`/home/elaaaaaaa/modul2/indomie/` merupakan direktori tujuan. <br/>

```
  if((child_id_5=fork()) == 0){
	char *argv[] = {"/usr/bin/find", "/home/elaaaaaaa/Modul2/jpg", "-mindepth", "1", "-maxdepth", "1", "-type", "f", "-exec", "mv","-t", "/home/elaaaaaaa/Modul2/sedaap", "{}", ";", NULL};
	execv(argv[0], argv);
   }
```
Untuk memindahkan semua file yang ada di direktori jpg ke direktori sedaap, kita harus mengelompokkan dulu mana yang termasuk file. 
Caranya dengan menggunakan command `find`. Caranya sama seperti memindahkan direktori, perbedaannya hanya ada di `-type f`. <br/>

(d) Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi 
nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh:“/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”)
<br/>
Untuk membuat file pada suatu direktori, saya menggunakan command line `touch`.
```
if((child_id_6=fork()) == 0){
	char *argv[] = {"/usr/bin/find", "/home/elaaaaaaa/Modul2/indomie", "-mindepth", "1", "-type", "d", "-exec", "touch", "{}/coba1.txt",";", NULL};
    	execv(argv[0], argv);
 }
```
Tiga detik setelahnya membuat file `coba2.txt` untuk setiap direktori yang ada pada direktori indomie. Untuk menjeda selama 3 detik 
digunakan system call `sleep`.
```
if((child_id_7=fork()) == 0){
	sleep(3);	//menjeda selama 3 detik
	char *argv[] = {"/usr/bin/find", "/home/elaaaaaaa/Modul2/indomie", "-mindepth", "1", "-type", "d", "-exec", "touch", "{}/coba2.txt",";", NULL};
    	execv(argv[0], argv);
  }
```
