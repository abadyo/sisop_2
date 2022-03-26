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


Japrun bekerja di sebuah perusahaan dibidang review industri perfilman, karena kondisi saat ini sedang pandemi Covid-19, dia mendapatkan sebuah proyek untuk mencari drama korea yang tayang dan sedang ramai di Layanan Streaming Film untuk diberi review. Japrun sudah mendapatkan beberapa foto-foto poster serial dalam bentuk zip untuk diberikan review, tetapi didalam zip tersebut banyak sekali poster drama korea dan dia harus memisahkan poster-poster drama korea tersebut tergantung dengan kategorinya. Japrun merasa kesulitan untuk melakukan pekerjaannya secara manual, kamu sebagai programmer diminta Japrun untuk menyelesaikan pekerjaannya.

Summary Soal:
1. Unzip dari zip file yang diberikan, lalu filter sampai yang keluar hanya poster drakor, hasil filter ditaruh di folder drakor
2. Setiap poster drakor memiliki kategori di nama file nya, buatlah folder kategori berdasarkan hal tersebut
3. Setiap poster dipindah ke kategorinya masing-masing dan diubah namanya menjadi nama drakornya saja.
4. Ada beberapa file yang mengandung 2 poster, pisahkan dan ditaruh seperti no. 3
5. Buatlah sebuah file `data.txt` di setiap folder kategori dimana file itu berisi nama poster dan tahun rilis dari poster dan harus berurut berdasarkan tahun rilis

## Penjelasan Code Soal 2

Kode diawali dengan unzip dimana unzip itu sendiri langsung memfilter file-file yang tidak perlu

```c
char *argv[ ] = {"unzip", "drakor.zip", "*.png", "-d", "drakor", NULL};
execv("/bin/unzip", argv);
```
Dengan menambahkan "*.png" proses unzip akan mengeluarkan file yang memiliki akhiran .png dimana yang memiliki ciri-ciri itu hanyalah 
poster yang ada di zip `drakor.zip`. Lalu dengan menambahkan "-d" dan "drakor" akan melakukan setiap file yang diunzip akan dimasukan
ke folder drakor. Setelah berhasil diunzip, akan dilanjutkan ke fungsi `REAL_PROCESS()`.

Memasuki fungsi `REAL_PROCESS()`, kami akan membuka direktori drakor yang baru saja dibuat untuk menelusuri semua gambar yang berisi
poster-poster drakor. 

```c
        while ((dir = readdir(d)) != NULL) {
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0 || strcmp(dir->d_name, "dummy.txt") == 0) continue;
            char filename[1005];
            snprintf(filename, sizeof filename, "%s", dir->d_name);
            //printf("%s\n", filename);
            char str[1005];
            strcpy(str, filename);

            char *token = strtok(str, ";");

            char drakor[55];
            snprintf(drakor, sizeof drakor, "%s", token);
            token = strtok(NULL, ";");
            //printf("drakor: %s\n" , drakor);

            char tahun[15];
            snprintf(tahun, sizeof tahun, "%s", token);
            token = strtok(NULL, ";._");
            //printf("tahun: %s\n" , tahun);

            char kategori[15];
            snprintf(kategori, sizeof kategori, "%s", token);
            token = strtok(NULL, ";");
            //printf("kategori: %s\n" , kategori);

            //create directory
            makedir(kategori);
            
            //copy files to category directory
            copyf(drakor, kategori, filename);
            
            snprintf(ls[i], sizeof ls[i], "%s;%s;%s", kategori, tahun, drakor);
            i++;
            //printf("write %s;%s;%s on dummy.txt\n", kategori, tahun, drakor);

            if(strlen(token) > 3){
                //printf("next up: %s\n", token);

                char drakor2[55];
                snprintf(drakor2, sizeof drakor2, "%s", token);
                token = strtok(NULL, ";");
                //printf("drakor2: %s\n" , drakor2);

                char tahun2[15];
                snprintf(tahun2, sizeof tahun2, "%s", token);
                token = strtok(NULL, ";._");
                //printf("tahun2: %s\n" , tahun2);

                char kategori2[15];
                snprintf(kategori2, sizeof kategori2, "%s", token);
                token = strtok(NULL, "_");
                //printf("kategori2: %s\n" , kategori2);

                //create directory
                makedir(kategori2);
                
                //copy files to category directory
                copyf(drakor2, kategori2, filename);

                snprintf(ls[i], sizeof ls[i], "%s;%s;%s", kategori2, tahun2, drakor2);
                i++;
                //printf("write %s;%s;%s on dummy.txt\n", kategori2, tahun2, drakor2);
            }

            printf("Deleting the poster %s\n", filename);
            del(filename);

        }
        closedir(d);
```

Dengan menggunakan `strtok` dengan delimiter `.;_` kita bisa mendapatkan nama, tahun rilis, serta kategori poster tersebut.
Setelah didapatkan informasi dari poster tersebut, kami membuat folder berdasarkan kategori, menyalin file dengan mengubah nama 
berdasarkan nama poster drakor, dan mencatat `data.txt` dengan tahun rilis. Setelah file disalin, kami membuat list string `ls`
dimana variabel itu akan menyimpan data kategori, tahun rilis, dan nama dengan format `kategori;tahun;nama` dimana dengan model
ini akan membantu dalam mengurutkan berdasarkan tahun rilis untuk menulis `data.txt`.

Dalam kasus 2 poster dalam satu file dengan mengecek hasil `strtok` setelah strtok ketiga kali. Jika hasil `strtok` tersebut memiliki
panjang string yang lebih dari 3, maka file tersebut memiliki 2 poster.

```c
int it,jt;
char temp[105];
//Sort array using the Buuble Sort algorithm
for(it=0; it<20; it++){
    for(jt=0; jt<20-1-it; jt++){
        if(strcmp(ls[jt], ls[jt+1]) > 0){
            //swap ls[j] and ls[j+1]
            strcpy(temp, ls[jt]);
            strcpy(ls[jt], ls[jt+1]);
            strcpy(ls[jt+1], temp);
        }
    }
}
```

Untuk proses sorting kami menggunakan Bubble Sort Algorithm dimana kode ini didapatkan dari Template GeekForGeeks.

```c
for(it=1; it<20; it++){
    //printf("%s\n", ls[it]);
    char st[105];
    snprintf(st, sizeof st, "%s", ls[it]);
    //printf("%s\n", st);

    char *token = strtok(st, ";");

    char kategori[15];
    snprintf(kategori, sizeof kategori, "%s", token);
    token = strtok(NULL, ";");

    //printf("get kategori %s\n", kategori);

    char tahun[15];
    snprintf(tahun, sizeof tahun, "%s", token);
    token = strtok(NULL, ";");

    //printf("get tahun %s\n", tahun);

    char drakor[55];
    snprintf(drakor, sizeof drakor, "%s", token);
    token = strtok(NULL, ";");

    //printf("get drakor %s\n", drakor);

    char path[35];
    snprintf(path, sizeof path, "drakor/%s/data.txt", kategori);
    //printf("get path %s\n", path);

    FILE *data;
    data = fopen(path, "a+");
    //printf("open txt file success\n");
    if(strcmp(temp, kategori) != 0){
        //printf("write kategori %s as header\n", kategori);
        fprintf(data, "kategori: %s\n\n", kategori);
    }
    fprintf(data, "nama: %s\n", drakor);
    fprintf(data, "rilis: tahun %s\n\n", tahun);
    // printf("success write data in txt\n");

    fclose(data);
    strcpy(temp, kategori);
}
```

Untuk bagian ini khusus untuk menulis `data.txt` untuk setiap kategori. Dengan memperhatikan kategori terlebih dahulu, saat mencapai
awal dari kategori, akan dibuatkan "kategori: `nama kategori`". Dengan menggunakan `strtok` dengan delimiter `;` bisa didapatkan kembali 
kategori, tahun rilis, dan nama. Dengan begitu kita bisa menulis nama drakor dan tahun rilis.

**Penjelasan Fungsi Tambahan**

1. `run_it(char bash[ ], char *argv[ ])`
```c
void run_it(char bash[ ], char *argv[ ]){
    int status;
    pid_t child = fork();

    if(child == 0){
        execv(bash, argv);
    } else while(wait(&status) > 0);
}
```

Fungsi ini akan melakukan fork lalu melakukan execv berdasarkan `*argv[ ]` dan  `bash[ ]` agar fork yang dilakukan tidak mengganggu proses 
yang sedang berjalan.

2. `makedir(char kategori [ ])`
```c
void makedir(char kategori[ ]){

    char target[205];
    snprintf(target, sizeof target, "drakor/%s", kategori);
    char *argv[ ] = {"mkdir", "-p", target, NULL};
    
    run_it("/usr/bin/mkdir", argv);
}
```

Fungsi ini akan membuat direktori berdasarkan string yang diberikan. Untuk disini stringnya adalah `kategori[ ]`.

3. `copyf(char nama[ ], char kategori[ ], char fileName[ ] )`
```c
void copyf(char nama[ ], char kategori[ ], char fileName[ ] ) {

    char target[2005];
    char new_file[2005];
    snprintf(target, sizeof target, "drakor/%s", fileName);
    snprintf(new_file, sizeof new_file, "drakor/%s/%s.png", kategori, nama);

    //printf("%s\n", target);
    //printf("%s\n", new_file);
    
    char *argv[ ] = {"cp", target, new_file, NULL};
    char bash[ ] = "/usr/bin/cp";
    run_it(bash, argv);
}
```

Fungsi ini akan menyalin file berdasarkan `fileName[ ]` ke dalam `kategori[ ]` dengan nama `nama[ ]`.

4. `del(char fileName[ ])`
```c
void del(char fileName[ ]){
    char target[2005];
    snprintf(target, sizeof target, "drakor/%s", fileName);
    //printf("%s\n", target);

    char *argv[ ] = {"rm", target, NULL};
    char bash[ ] = "/usr/bin/rm";
    run_it(bash, argv);
}
```
Fungsi ini akan menghapus file berdasarkan `fileName[ ]`.

## Kendala Yang Dihadapi Soal 2
Kendala yang kami hadapi, kami sering menjumpai segmentation error. Hal ini dijumpai karena kami mengunjungi direktori yang masih belum dibuat.

Saat melakukan `strtok`, karena delimiter yang diberikan kurang, maka terciptalah direktori dengan nama (null).

## Screenshot Hasil Run Soal 2

4 ss masuk nanti setelah bwt direktori gambar

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
