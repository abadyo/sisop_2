#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>

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

int main() {
    char *nama;
    nama=(char *)malloc(10*sizeof(char));
    nama=getlogin();
    char unziplocation[100] = "./modul2/animal";
    char filedarat[100] = "./modul2/darat";
    char fileair[100] = "./modul2/air";
    
    // printf("%s", unziplocation);

    // char *argvdownload[] =  {"wget", "https://drive.google.com/file/d/1dALdiL3T-7MXdScMCXn-SDBo5lMhH-vJ/view?usp=sharing", NULL};
    char *argvmkdirmodul[] = {"mkdir", "modul2", NULL};
    char *argvmkdirdarat[] = {"mkdir", "modul2/darat", NULL};
    char *argvmkdirair[] = {"mkdir", "modul2/air", NULL};
    char *argvunziphewan[] =  {"unzip", "animal.zip", "-d", "modul2", NULL};

    // a
    // garputunggu("/bin/wget", argvmkdirmodul);

    garputunggu("/bin/mkdir", argvmkdirmodul);
    garputunggu("/bin/mkdir", argvmkdirdarat);
    sleep(3);
    garputunggu("/bin/mkdir", argvmkdirair);

    // b
    garputunggu("/usr/bin/unzip", argvunziphewan);

    // c
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

    // d
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

    // e
    // char *argvtouch[] = {"touch", "modul2/list.txt", NULL};
    // garputunggu("/usr/bin/touch", argvtouch);
    
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

    

// nmap -A -T4 -v -p-- ip add -oN nama file 


}
