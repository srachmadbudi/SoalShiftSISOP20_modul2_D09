# SoalShiftSISOP20_modul2_D09
```
Rachmad Budi Santoso    05111840000122
Khofifah Nurlaela       05111840000025
```

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
mana yang termasuk file. Caranya dengan menggunakan command `find`. Secara lengkapnya : 
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
