# soal-shift-sisop-modul-2-ITA13-2022

Modul 2

## Ginshin impict

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
