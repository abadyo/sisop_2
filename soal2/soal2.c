#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <stdio.h>
#include <wait.h>

void run_it(char bash[ ], char *argv[ ]){
    int status;
    pid_t child = fork();

    if(child == 0){
        execv(bash, argv);
    } else while(wait(&status) > 0);
}

void makedir(char kategori[ ]){

    char target[205];
    snprintf(target, sizeof target, "drakor/%s", kategori);
    char *argv[ ] = {"mkdir", "-p", target, NULL};
    
    run_it("/usr/bin/mkdir", argv);
}

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

void del(char fileName[ ]){
    char target[2005];
    snprintf(target, sizeof target, "drakor/%s", fileName);
    //printf("%s\n", target);

    char *argv[ ] = {"rm", target, NULL};
    char bash[ ] = "/usr/bin/rm";
    run_it(bash, argv);
}

void REAL_PROCESS(){
    DIR *d = opendir("drakor");
    struct dirent *dir;

    char ls[20][105];
    int i=0;
    //FILE *dummy = fopen("drakor/dummy.txt", "w+");

    if (d) {
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
            DIR *pDir = opendir(kategori);
            if(pDir == NULL) makedir(kategori);
            
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
                DIR *pDir = opendir(kategori);
                if(pDir == NULL) makedir(kategori);
                
                //copy files to category directory
                copyf(drakor, kategori, filename);

                snprintf(ls[i], sizeof ls[i], "%s;%s;%s", kategori2, tahun2, drakor2);
                i++;
                //printf("write %s;%s;%s on dummy.txt\n", kategori2, tahun2, drakor2);
            }

            printf("Deleting the poster %s\n", filename);
            del(filename);

        }
        closedir(d);
    }

    printf("all posters tracked, sorting...\n");
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
    strcpy(temp, "");

    for(it=0; it<20; it++) printf("%i - %s\n", it, ls[it]);

    printf("it should be sorted rn, \n");

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
        fprintf(data, "tahun: %s\n\n", tahun);
       // printf("success write data in txt\n");

        fclose(data);
        strcpy(temp, kategori);
    }
}

int main(){
    int status;
    pid_t child = fork();

    if(child == 0){
        char *argv[ ] = {"unzip", "drakor.zip", "*.png", "-d", "drakor", NULL};
        execv("/bin/unzip", argv);
    } else{
        while(wait(&status) > 0);
        REAL_PROCESS();

        return(0);
    }
}