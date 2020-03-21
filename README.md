# SoalShiftSISOP20_modul1_T12
`"Repository dibuat untuk memenuhi tugas praktikum mata kuliah sistem operasi tahun 2020."`

Anggota :  
**Muhammad Ilya Asha Soegondo** `[05311840000010]` [@ilyaasha24](https://github.com/ilyaasha24/)   
**Mohammad Ifaizul Hasan** `[05311840000029]` [@IzuruSakamaki](https://github.com/IzuruSakamaki/)  

Asisten :  
**Nandha Himawan** `[05111740000180]`  
## Daftar Isi
1. [Judul](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#soalshiftsisop20_modul1_t12)
2. [Daftar Isi](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#daftar-isi)
3. [Pendahuluan](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#pendahuluan)  
	3.1. [Prasyarat](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#prasyarat)
4. [Soal 1](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#soal-1)  
	4.1. [Penyelesaian](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#penyelesaian)
5. [Soal 2](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#soal-2)  
	5.1. [Penyelesaian](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#penyelesaian-1)
6. [Soal 3](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#soal-3)  
	6.1. [Penyelesaian](https://github.com/IzuruSakamaki/SoalShiftSISOP20_modul2_T12#penyelesaian-2)

## Pendahuluan
### Prasyarat
 - **Sebuah distribusi Linux** (misal: [Ubuntu](https://ubuntu.com/download/desktop), [Linux Mint](https://www.linuxmint.com/download.php)).  
 - **The GNU Compiler Collection** (gcc, libc6-dev).  
``
sudo apt-get install build-essential
``

## Soal 1
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:  

**a.	Program menerima 4 argumen berupa:**  
i.	Detik: 0-59 atau * (any value)  
ii.	Menit: 0-59 atau * (any value)  
iii.	Jam: 0-23 atau * (any value)  
iv.	Path file .sh  
**b.	Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai  
c.	Program hanya menerima 1 config cron  
d.	Program berjalan di background (daemon)  
e.	Tidak boleh menggunakan fungsi system()**  

Contoh:  
`./program \\* 34 7 /home/somi/test.sh`  
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap detik pada jam 07:34.

### Penyelesaian: 	
***a.***	Memasukkan library yang diperlukan.
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
```
***b.***	Memastikan bahwa argumen yang dimasukkan adalah 4 argumen. Jika tidak, program gagal dijalankan dengan error argumen salah.
```
if (argc != 5) {
    printf("Wrong Argument\n");
    exit(EXIT_FAILURE);
}
```
1.	`if (argc != 5)` Menjelaskan bahwa apabila total argumen tidak sama dengan 5 maka akan masuk kedalam fungsi `if`. Mengapa tidak 4? Karena nama file yang sedang kita jalankan juga dihitung sebagai argumen.

2.	`printf("Wrong Argument\n");` Menjelaskan bahwa ketika fungsi `if` telah dijalankan atau argumen tidak sama dengan 5 maka akan mencetak tulisan `Wrong Argument` .

3.	`exit(EXIT_FAILURE);` Menjelaskan bahwa program keluar karena gagal dijalankan.

***c.***	Mengecek argument. Jika salah, menampilkan kode errornya dan keluar.
```
if (!(((atoi(argv[1]) >= 0) && (atoi(argv[1]) < 60)) || ((strcmp(argv[1],"*")) == 0))) {
    printf("First Argument must between 0-59 or *\n");
    exit(EXIT_FAILURE);
}
if (!(((atoi(argv[2]) >= 0) && (atoi(argv[2]) < 60)) || ((strcmp(argv[2],"*")) == 0))){
    printf("Second Argument must between 0-59 or *\n");
    exit(EXIT_FAILURE);
}
if (!(((atoi(argv[3]) >= 0) && (atoi(argv[3]) < 24)) || ((strcmp(argv[3],"*")) == 0))){
    printf("Third Argument must between 0-23 or *\n");
    exit(EXIT_FAILURE);
}
```
1.	`if (!(((atoi(argv[1]) >= 0) && (atoi(argv[1]) < 60)) || ((strcmp(argv[1],"*")) == 0)))`  
`if (!(((atoi(argv[2]) >= 0) && (atoi(argv[2]) < 60)) || ((strcmp(argv[2],"*")) == 0)))`  
`if (!(((atoi(argv[3]) >= 0) && (atoi(argv[3]) < 24)) || ((strcmp(argv[3],"*")) == 0)))`  
Menjelaskan bahwa apabila argumen tidak sesuai ketentuan maka akan masuk kedalam fungsi `if`. Dikarenakan argumen sendiri berbentuk string maka harus dijadikan integer terlebih dahulu agar bisa dilakukan perbandingan. Disini kami menggunakan `atoi` untuk melakukannya. Sedangkan untuk membandingkan argumen dengan asterisk, kami menggunakan `strcmp` dalam memandingkannya. Apabila nilai argumen sama dengan asterisk maka akan bernilai 0, namun jika argumen bernilai lebih besar dari asterisk maka akan bernilai positif, dan apabila argumen bernilai lebih kecil dari asterisk maka akan bernilai negatif.

2.	`printf("First Argument must between 0-59 or *\n");`  
`printf("Second Argument must between 0-59 or *\n");`  
`printf("Third Argument must between 0-23 or *\n");`  
Menjelaskan bahwa ketika fungsi `if` telah dijalankan maka akan mencetak tulisan `First Argument must between 0-59 or *` atau `Second Argument must between 0-59 or *` atau `Third Argument must between 0-23 or *.`

3.	`exit(EXIT_FAILURE);` Menjelaskan bahwa program keluar karena gagal dijalankan.

***d.***	Menjalankan Daemon.
```
time_t t;
struct tm tm;
pid_t pid = fork(), sid;
if (pid < 0) exit(EXIT_FAILURE);
if (pid > 0) exit(EXIT_SUCCESS);
umask(0);
sid = setsid();
if (sid < 0) exit(EXIT_FAILURE);
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
```
1.	`time_t t;` `struct tm tm;` merupakan pendeklarasian waktu yang berguna untuk menyimpan epoch dan memformatnya.

2.	Dilanjutkan dengan mendeklarasikan *pid* dan *sid* nya sekaligus memulai Peranakan atau `fork()` dengan perintah `pid_t pid = fork(), sid;`

3.	Apabila fungsi `fork()` berhasil dijalankan `(pid > 0)` maka `exit(EXIT_SUCCESS);` dan apabila gagal `(pid < 0)` maka `exit(EXIT_FAILURE);`

4.	Ketika telah diketahui bahwa `fork()` berhasil dijalankan, maka kita `umask(0)` agar file dan direktori yang baru dibuat dapat dibaca, ditulis dan diturunkan untuk semua orang (permission direktori 0777 dan file 0666).

5.	Agar dapat diproses maka kita harus mendapatkan *sid* dari proses anak dengan perintah `sid = setsid();` yang kemudian kita cek apakah *sid* telah dibuat atau belum menggunakan perintah `if (sid < 0) exit(EXIT_FAILURE);`

6.	Dikarenakan kita akan menjalankan daemon maka kita harus menutup semua *standard streams* yaitu `STDIN_FILENO`, `STDOUT_FILENO`, `STDERR_FILENO` dengan cara:
`close(STDIN_FILENO);`
`close(STDOUT_FILENO);`
`close(STDERR_FILENO);`

***e.***	Menjalankan Shell Script.
```
while (1) {
    t = time(NULL);
    tm = *localtime(&t);
    if ((tm.tm_sec == atoi(argv[1]) || ((strcmp(argv[1],"*")) == 0)) && (tm.tm_min == atoi(argv[2]) || ((strcmp(argv[2],"*")) == 0)) && (tm.tm_hour == atoi(argv[3]) || ((strcmp(argv[3],"*") == 0)))) {
        if (fork()==0) execl("/bin/bash", "bash", argv[4], NULL);
    }
    sleep(1);
}
```
7.	`while (1)` menandakan perulangan tanpa henti.

8.	UNIX Epoch akan disimpan `t = time(NULL);` kemudian diformat pada acuan struktur pada tm berdasarkan waktu lokal kami sekarang berada.  
Atau dapat kita tuliskan `tm = *localtime(&t);`

9. `if ((tm.tm_sec == atoi(argv[1]) || ((strcmp(argv[1],"*")) == 0)) && (tm.tm_min == atoi(argv[2]) || ((strcmp(argv[2],"*")) == 0)) && (tm.tm_hour == atoi(argv[3]) || ((strcmp(argv[3],"*") == 0))))`
Merupakan sebuah pernyataan-pernyataan yang apabila terpenuhi akan masuk kedalam fungsi `if`.  
Hampir sama seperti fungsi `if` untuk mengecek argumen, kali ini fungsi `if` digunakan untuk mengecek kesamaan antara waktu lokal dengan argumen yang dimasukkan.

10.	Apabila fungsi `if` berjalan maka akan masuk kedalam fungsi peranakan dimana apabila `fork()` sama dengan 0 maka akan melakukan execute shell script.  
Dapat dituliskan sebagai berikut: `if (fork()==0) execl("/bin/bash", "bash", argv[4], NULL);`

11.	Setelah berhasil melakukan execute terhadap shell script, tak lupa untuk melakukan jeda sejenak selama satu detik agar proses tidak berulang dalam satu detik menggunakan `sleep(1)`.

## Soal 2
![foto](https://picsum.photos/1000)
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program

**a.	Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss].  
b.	Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss].  
c.	Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).  
d.	Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.  
e.	Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai (semua folder terisi gambar, terzip lalu di delete).**

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi. Buatlah program dalam mimpi Kiwa jadi nyata!

**Catatan:**  
**- Tidak boleh memakai system().**  
**- Program utama harus ter-detach dari terminal**  
**Hint:**  
**- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran tertentu**  
**- Epoch Unix bisa didapatkan dari time()**  

### Penyelesaian:
***a.*** Memasukkan library yang diperlukan.
```
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <wait.h>
```
***b.***	Memastikan bahwa jumlah argumen yang dimasukkan benar.
```
if (argc != 2) {
    printf("Wrong Argument\n");
    exit(EXIT_FAILURE);
}
```
1.	`if (argc != 2)` menjelaskan bahwa apabila total argumen tidak sama dengan 2 maka akan masuk kedalam fungsi `if`.
2.	`printf("Wrong Argument\n");` menjelaskan bahwa ketika fungsi `if` telah dijalankan atau argumen tidak sama dengan 2 maka akan mencetak tulisan `Wrong Argument` .
3.	`exit(EXIT_FAILURE);`  menjelaskan bahwa program keluar dan gagal dijalankan.
***c.***	Komparasi hasil dari masukan argumen.
```
if (strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "-b") != 0) {
    printf("Second Argument must specify mode (-a/-b)\n");
    exit(EXIT_FAILURE);
}
```
1.	Apabila argumen kedua atau `argv[1]` tidak sama dengan **–a** atau **-b** maka akan masuk kedalam fungsi `if`.
2.	Ketika fungsi `if` berjalan maka akan mencetak `Second Argument must specify mode (-a/-b)`.
3.	`exit(EXIT_FAILURE);`  Menjelaskan bahwa program keluar karena gagal dijalankan.
***d.***	Melakukan Deklarasi, Peranakan, dan memulai Daemon.
```
pid_t pid = fork(), sid;
time_t t, s;
struct tm *tm, *sm;
if (pid < 0) exit(EXIT_FAILURE);
if (pid > 0) exit(EXIT_SUCCESS);
umask(0);
sid = setsid();
if (sid < 0) exit(EXIT_FAILURE);
close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
```
1.	`time_t t, s; struct tm *tm, *sm;` merupakan pendeklarasian variabel dan struktur yang berguna untuk menyimpan dan memformat waktu.

2.	Dilanjutkan dengan mendeklarasikan *pid* dan *sid* nya sekaligus memulai Peranakan atau `fork()` dengan perintah `pid_t pid = fork(), sid;`

3.	Apabila fungsi `fork()` berhasil dijalankan `(pid > 0)` maka `exit(EXIT_SUCCESS);` dan apabila gagal `(pid < 0)` maka `exit(EXIT_FAILURE);`

4.	Ketika telah diketahui bahwa `fork()` berhasil dijalankan, maka kita `umask(0)` agar file dan direktori yang baru dibuat dapat dibaca, ditulis dan diturunkan untuk semua orang (permission direktori 0777 dan file 0666).

5.	Agar dapat diproses maka kita harus mendapatkan *sid* dari proses anak dengan perintah `sid = setsid();` yang kemudian kita cek apakah *sid* telah dibuat atau belum menggunakan perintah `if (sid < 0) exit(EXIT_FAILURE);`

6.	Dikarenakan kita akan menjalankan daemon maka kita harus menutup semua *standard streams* yaitu `STDIN_FILENO`, `STDOUT_FILENO`, `STDERR_FILENO` dengan cara
`close(STDIN_FILENO);`
`close(STDOUT_FILENO);`
`close(STDERR_FILENO);`
***e.***	Menambah program Killer
```
FILE *f;
f = fopen("killer.c", "w");
fprintf(f, "#include <unistd.h>\n#include <wait.h>\n\nint main() {\n  if (fork() == 0) {\n");
if (strcmp(argv[1], "-a") == 0) fprintf(f, "    execl(\"/usr/bin/pkill\", \"pkill\", \"-9\", \"-s\", \"%d\", NULL);\n", sid);
if (strcmp(argv[1], "-b") == 0) fprintf(f, "    execl(\"/usr/bin/kill\", \"kill\", \"-9\", \"%d\", NULL);\n", getpid());
fprintf(f, "  }\n  while(wait(NULL) > 0);\n  execl(\"/usr/bin/rm\", \"rm\", \"killer\", NULL);\n}");
fclose(f);
if ((pid = fork()) == 0) execl("/usr/bin/gcc", "gcc", "killer.c", "-o", "killer", NULL);
while(wait(NULL) != pid);
if (fork() == 0) execl("/usr/bin/rm", "rm", "killer.c", NULL);
int start = time(NULL)%30;
```
1.	Dimulai dengan mendeklarasikan file nya `FILE *f` kemudian membuka filenya dengan `fopen` dalam mode penulisan `w`.

2.	Penulisan dimulai dengan memasukkan library yang diperlukan yaitu <unistd.h> dan <wait.h>     

3.	Menulis `main` dan `fork`   

4.	Jika argumen kedua adalah **-a** maka tulis `execl(\"/usr/bin/pkill\", \"pkill\", \"-9\", \"-s\", \"%d\", NULL);` dengan `%d` berisi *sid* untuk memberhentikan semua proses `pkill` ber-*sid* tersebut.

5.	Jika argumen kedua adalah **-b** maka tulis `execl(\"/usr/bin/kill\", \"kill\", \"-9\", \"%d\", NULL);` menandakan bahwa yang diberhentikan hanya program utama (*parent*) dan proses setiap direktori tetap berjalan sampai selesai. Hal ini dapat dilakukan  dengan mengisi `%d` menjadi pid dari program utama (*parent*) tersebut `getpid()`.

6.	`while(wait(NULL) > 0);` untuk menunggu perubahan status anaknya yang lain, `execl(\"/usr/bin/rm\", \"rm\", \"killer\", NULL);` untuk memastikan bahwa `killer` akan dihapus dengan perintah `rm`.

7.	Setelah melakukan penulisan pada file `killer.c` maka harus kita tutup dengan `fclose(f);`

8.	`if ((pid = fork()) == 0) execl("/usr/bin/gcc", "gcc", "killer.c", "-o", "killer", NULL);` untuk meng-*compile* `killer.c` menjadi executable `killer` .

9.	`while(wait(NULL) != pid);` untuk menunggu *compiler* selesai kemudian menghapus file `killer.c` dengan `rm`.

10.	Lalu menyimpan modulo 30 dari Epoch sebagai penanda kapan mulainya fungsi berikutnya yang dijadwalkan setiap 30 detik. `int start = time(NULL)%30;`  

***f.***	Mengunduh File, dan melakukan zipping.
```
while (1) {
    if ((time(NULL)%30) == start) {
        t = time(NULL);
        tm = localtime(&t);
        char dir[50], tmpdir[150], url[50], file[50];
        strftime(dir, 50, "khusus/%Y-%m-%d_%H:%M:%S", tm);
        if (fork() == 0) execl("/usr/bin/mkdir", "mkdir", "-p", dir, NULL);      
        if (fork() == 0) {
            for (int i = 0; i < 20; i++) { // BE CAREFUL!!
                s = time(NULL);
                sm = localtime(&s);
                strcpy(tmpdir, dir);
                strftime(file, 50 ,"/%Y-%m-%d_%H:%M:%S" ,sm);
                strcat(tmpdir, file);
                sprintf(url, "https://picsum.photos/%ld", ((s % 1000) + 100));
                if (fork() == 0) execl("/usr/bin/wget", "wget", "-qbO", tmpdir, "-o", "/dev/null", url, NULL);
                sleep(5);
            }
            execl("/usr/bin/zip", "zip", "-rm", dir, dir, NULL);
        }
    }
    sleep(1);
}
```
1.	`while (1)` menandakan perulangan tanpa henti.

2.	Mengecek apakah sisa bagi 30 dari Epoch saat ini atau `time(NULL)%30` bernilai sama dengan variabel `start` untuk memulai mengunduh gambar  

3.	UNIX Epoch akan disimpan `t = time(NULL);` kemudian diformat pada acuan struktur pada tm berdasarkan waktu lokal kami sekarang berada.  
Atau dapat kita tuliskan `tm = *localtime(&t);`. Tak lupa juga untuk mendeklarasikan string yang akan digunakan. Ada 4 yang kita deklarasikan yaitu `dir[50]` sebagai variabel penyimpan nama direktori, `tmpdir[150]` sebagai variabel penyimpan `dir` sementara dan hasil penggabungannya dengan variabel `file`, `url[50]` sebagai variabel penyimpan link url, dan `file[50]` sebagai variabel penyimpan nama file.

4.	Memformat waktu sesuai format `"khusus/%Y-%m-%d_%H:%M:%S"` dari `tm` dan menyimpannya pada `dir` menggunakan `strftime`.

5. Membuat direktori beserta induknya dengan `mkdir -p` melalui `exec`. Direktori yang dibuat akan memiliki nama sesuai *timestamp* dan formatnya (YYYY-MM-DD_hh:mm:ss) serta membuat direktori induknya `khusus` apabila belum ada.

6. Melakukan perulangan sebanyak 20 kali untuk mengunduh gambar.

7. UNIX Epoch akan disimpan `s = time(NULL);` kemudian diformat pada acuan struktur pada tm berdasarkan waktu lokal kami sekarang berada.  
Atau dapat kita tuliskan `sm = *localtime(&t);`.
Digunakannya variabel yang berbeda untuk menghindari kerancuan.

8. Menyalin isi variabel `dir` ke variabel `tmpdir` menggunakan `strcpy`.

9. Memformat waktu sesuai format `"/%Y-%m-%d_%H:%M:%S"` dari `sm` dan menyimpannya pada `file` menggunakan `strftime`. Lalu menggabungkan isi variabel `tmpdir` dan `file` dan menyimpannya di variabel `tmpdir`.

10. Memformat url sesuai format "https://picsum.photos/(Epoch % 1000 + 100) kemudian disimpan ke variabel `url`.

11. Mengunduh file menggunakan `wget` dengan opsi `q`(*quiet*/senyap), `b`(*background*/latar belakang), `0`(*Output*/hasil sesuai isi variabel `tmpdir`), `o`(logfile dioper ke `"/dev/null"` untuk ditiadakan), dengan url sesuai isi variabel `url`.

12. `sleep(5);`. Memberi jeda waktu 5 detik untuk setiap pengunduhan.

13.	Ketika pengunduhan selesai maka akan dimulai pengarsipan direktori-direktori beserta isinya dalam direktori `khusus` dengan perintah `zip` melalui `exec` dan opsi `r`(*recursive*/rekursif) untuk mengarsipkan suatu direktori beserta isinya, `m`(*move*/pindah) untuk menghapus file-file dan direktori-direktori yang telah diarsipkan .

14. Memberi jeda waktu 1 detik pada tiap perulangan `while (1)` agar tidak terjadi penjalanan ganda dalam satu detik.

## Soal 3
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing).  

**a. Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu lima detik kemudian membuat direktori yang kedua bernama “sedaap”.  
b.	Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.  
c.	Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.  
d.	Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh: “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).**  

Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat program tersebut.  

**Catatan:**  
**- Tidak boleh memakai system().**  
**- Tidak boleh memakai function C mkdir() ataupun rename().**  
**- Gunakan exec dan fork**  
**- Direktori “.” dan “..” tidak termasuk**  

### Penyelesaian:  
***a.***	Memasukkan library yang diperlukan.  
```
#include <unistd.h>
```  
***b.***	Membuat direktori dan melakukan ekstraksi.  
```
if (fork() == 0) execl("/bin/mkdir", "mkdir", "-p","indomie", NULL);
if (fork() == 0) execl("/usr/bin/unzip", "unzip", "-oq","jpg.zip", NULL);
sleep(5);
if (fork() == 0) execl("/bin/mkdir", "mkdir", "-p","sedaap", NULL);
sleep(1);
```
1.	`if (fork() == 0) execl("/bin/mkdir", "mkdir", "-p","indomie", NULL);` menjelaskan untuk melakukan peranakan lalu melakukan execute perintah untuk membuat direktori atau `mkdir` bernama `indomie`.

2.	Selagi menunggu 5 detik, kami melakukan peranakan lalu melakukan ekstraksi terlebih dahulu dengan melakukan execute perintah ekstraksi atau `unzip`. Ekstraksi dapat dilakukan dengan perintah `execl("/usr/bin/unzip", "unzip", "-oq","jpg.zip", NULL);`

3.	`sleep(5);` menunjukkan bahwa harus menunggu 5 detik terlebih dahulu sebelum melakukan kegiatan selanjutnya.

4.	`if (fork() == 0) execl("/bin/mkdir", "mkdir", "-p","sedaap", NULL);` melakukan peranakan lalu membuat direktori atau `mkdir` bernama `sedaap`.

5.	`sleep(1);` menunjukkan bahwa harus menunggu sedetik sebelum melakukan kegiatan selanjutnya.

***c.***	Memindahkan file dan direktori sesuai ketentuan.  
```
if(fork() == 0) execl("/usr/bin/find", "find", "jpg/", "-mindepth", "1", "-type", "f", "-exec", "mv", "-t", "sedaap/", "{}", "+", (char*)NULL);
sleep(2);
if(fork() == 0) execl("/usr/bin/find", "find", "jpg/", "-mindepth", "1", "-type", "d", "-exec", "mv", "-t", "indomie/", "{}", "+", (char*)NULL);
```
1.	Sama seperti sebelumnya, disini juga melakukan peranakan dan `execl` untuk melakukan execute perintah pemindahan atau `mv`. Namun disini, harus dipisah terlebih dahulu mana yang bertipe file `"-type", "f",` dan mana yang bertipe direktori `"-type", "d",` dengan melakukan pencarian atau `find` dalam folder `jpg`. `-mindepth 1` digunakan agar folder `jpg` tidak dicari melainkan isi dari folder tersebut.

2.	Sebelum melakukan perpindahan kedua, dilakukan jeda selama 2 detik `sleep(2)` agar tidak terjadi kesalahan.

***d.***	Membuat dua file baru disetiap direktori.  
```
if(fork() == 0) execl("/usr/bin/find", "find", "indomie/", "-type", "d", "-exec", "touch", "{}/coba1.txt", ";", NULL);
sleep(3);
if(fork() == 0) execl("/usr/bin/find", "find", "indomie/", "-type", "d", "-exec", "touch", "{}/coba2.txt", ";", NULL);
```
1.	Pada proses terakhir ini dibuatlah suatu file kosong yaitu `coba1.txt` dan `coba2.txt` dengan menggunakan `touch` yang mana kita harus mencari terlebih dahulu dalam direktori indomie `"find", "indomie/"` semua yang bertipe direktori `"-type", "d"`.

2.	Sesuai dengan ketentuan di soal, sebelum membuat file `coba2.txt` akan dibuat suatu jeda selama 3 detik menggunakan `sleep(3)`.
