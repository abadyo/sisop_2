# soal-shift-sisop-modul-2-ITA13-2022

Modul 2

## Ginshin impict
Summary soal:
1. Download zip yang diberikan, lalu extract, lalu buat directory gacha_gacha
2. Gacha dipilih random, jumlah percobaan % 10 => buat file dengan format nama hH:mM:sS_gacha_jumlahgacha.txt dengan isi text berupa gacha random antara weapon dan character. percobaan ganjil => character, percobaan genap => weapon. Penulisan di text tersebut dengan format jumlahGacha_tipe_rarity_name_sisaPrimogems. nama dan rarity diambil dengan library json-c, dan primogems di define di awal dengan nilai 79000 dan tiap gacha dilakukan -160. Dan jika percobaan % 90 => buat folder dengan nama total_gacha_totalGachaDilakukan. dan isi folder berupa file gacha yang dibagikan tiap 10 kali. masing-masing file dengan dormat text sebelumnya.
3. Gacha dilakukan : 30 Maret jam 04:44, 3 jam kemudian, pada hari yang sama, akan dilakukan zip folder gacha_gacha dengan nama not_safe_for_wibu dengan password satuduatiga dan semua folder sebelumnya dihapus hingga menyisakan zip tersebut.
4. Semua proses dijalankan sekali, aka pakai daemon.

**Pre-process**

Mendefinisikan fungsi fork
```c
```

## Drakor

## Conan ngurusin kebun binatang fsr
Summary soal:
1. Buat folder modul2, didalamnya buat folder darat, 3 detik kemudian, buat folder air.
2. Extract zip animal, masukan folder animal ke dalam folder modul2.
3. gambar dengan tulisan darat -> masukkan ke folder darat, gambar dengan tulisan air -> masukkan ke folder air, tidak keduanya -> hapus.
4. Semua gambar bertulisan bird di dalam folder darat dihapus.
5. Semua gambar di dalam folder air di masukkan ke dalam list.txt dengan format \{nama user\}\_\{UID file\}\_\{nama file\}.

**Pre-process**

Mendefinisikan fungsi fork
```C
void garputunggu(char bash[], char *arg[]){
    int status;
    pid_t child;
    child = fork();
    if(child == 0){
        execv(bash, arg);
    }
    else{
        ((wait(&status))>0);
    }
}

void mv_garputunggu(char bash[], char nm_file[], char tujuan[]) {
    int status;
    pid_t child;
    child = fork();
    if(child == 0){
        execlp(bash, bash, nm_file, tujuan, NULL);
    }
    else{
        ((wait(&status))>0);
    }
}

void rm_garputunggu(char bash[], char nm_file[]) {
    int status;
    pid_t child;
    child = fork();
    if(child == 0){
        execlp(bash, bash, nm_file, NULL);
    }
    else{
        ((wait(&status))>0);
    }
}
```

### a
membuat folder dengan memanfaatkan fork() dan exec(), dimana pembuatan folder air ditunggu 3 detik.
```c
char *argvmkdirmodul[] = {"mkdir", "modul2", NULL};
char *argvmkdirdarat[] = {"mkdir", "modul2/darat", NULL};
char *argvmkdirair[] = {"mkdir", "modul2/air", NULL};

garputunggu("/bin/mkdir", argvmkdirmodul);
garputunggu("/bin/mkdir", argvmkdirdarat);
sleep(3);
garputunggu("/bin/mkdir", argvmkdirair);
```

### b
Proses seperti di atas, memanggil fungsi 'garputunggu'
```C
char *argvunziphewan[] =  {"unzip", "animal.zip", "-d", "modul2", NULL};
garputunggu("/usr/bin/unzip", argvunziphewan);
```

### c
memindah foto-foto dari folder ke animal ke foldernya masing-masing sesuai nama, gunakan berikut:
1. Pilih directory animal
2. Read semua file di dalam dir
3. cek tiap nama file, kalau ada tulisan darat, pindah ke dir darat, begitu juga dengan yang air
4. Tidak ada keduanya? hapus
```C
DIR *dp;
struct dirent *ep;

dp = opendir(unziplocation);
if(dp != NULL) {
    while((ep = readdir(dp))) {
        if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0 && strstr(ep->d_name, "darat")) {
            char awal[100] = "modul2/animal/";
            strcat(awal, ep->d_name); 
            // printf("%s\n", awal);
            // char *argvhewandarat[] =  {"mv", awal,"modul2/darat", NULL};
            // sleep(1);
            // garputunggu("usr/bin/mv", argvhewandarat);
            mv_garputunggu("mv", awal, "modul2/darat");
        } else if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0 && strstr(ep->d_name, "air")) {
            char awal[100] = "modul2/animal/";
            strcat(awal, ep->d_name); 
            // printf("%s\n", awal);
            // char *argvhewandarat[] =  {"mv", awal,"modul2/darat", NULL};
            // sleep(1);
            // garputunggu("usr/bin/mv", argvhewandarat);
            mv_garputunggu("mv", awal, "modul2/air");
        } else {
            if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0) {
                char awal[100] = "modul2/animal/";
                strcat(awal, ep->d_name); 
                // char *argvrm[] = {"rm", , NULL};
                rm_garputunggu("rm", awal);
            }
            
        }
    }
    (void) closedir (dp);
} else  perror ("Couldn't open the directory");
```

### d
Semua bird di dalam dir darat harus dihapus. gunakan langkah dengan yang sama, jika ada tulisan bird, hapus.
```C
DIR *darat;

darat = opendir(filedarat);
if(darat != NULL) {
    while((ep = readdir(darat))) {
        if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0 && strstr(ep->d_name, "bird")) {
            char awal[100] = "modul2/darat/";
            strcat(awal, ep->d_name); 
            rm_garputunggu("rm", awal);
        }
    }
    (void) closedir (darat);
} else  perror ("Couldn't open the directory");
```

### e
semua isi di dir ikan dibuat list dengan format user_UID_namafile.
```C
DIR *air;

air = opendir(fileair);
FILE *list_hewan = fopen("./modul2/air/list.txt", "w");

struct stat fs;
int r;

if(air != NULL) {
        while((ep = readdir(air))) {
        if (strcmp(ep->d_name, ".") != 0 && strcmp(ep->d_name, "..") != 0 && strstr(ep->d_name, "jpg")) {
            char awal[100] = "modul2/air/";
            strcat(awal, ep->d_name);
            r = stat(awal, &fs);
            char baca = '_', tulis = '_', jalan= '_';
            if( fs.st_mode & S_IRUSR ) baca = 'r';
            if( fs.st_mode & S_IWUSR ) tulis = 'w';
            if( fs.st_mode & S_IXUSR ) jalan = 'x';
            fprintf(list_hewan, "%s_%c%c%c_%s\n", nama, baca, tulis, jalan, ep->d_name);
        }
    }
    (void) closedir (air);
} else  perror ("Couldn't open the directory");

fclose(list_hewan);
```
