#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char* argv[])
{
    DIR *dir;
    struct dirent *plik; 
    struct stat st;
    struct passwd *tf; 
    struct group *gf;
    char buf[512];
    if(argc==1) {argv[1]=".";}
    dir = opendir(argv[1]);
    printf("Typ | Uprawnienia | Ilość linków | UID | GID | Rozmiar | Nazwa \n");
    while((plik = readdir(dir)) != NULL) 
    {    
        sprintf(buf, "%s/%s", argv[1], plik->d_name);
        stat(buf, &st);
        switch (st.st_mode & S_IFMT) {
            case S_IFBLK:  printf("b    "); break;
            case S_IFCHR:  printf("c    "); break; 
            case S_IFDIR:  printf("d    "); break; 
            case S_IFIFO:  printf("p    "); break; 
            case S_IFLNK:  printf("l    "); break; 
            case S_IFSOCK: printf("s    "); break;
            default:       printf("-    "); break;
                }
        printf((st.st_mode & S_IRUSR) ? " r" : " -");
        printf((st.st_mode & S_IWUSR) ? "w" : "-");
        printf((st.st_mode & S_IXUSR) ? "x" : "-");
        printf((st.st_mode & S_IRGRP) ? "r" : "-");
        printf((st.st_mode & S_IWGRP) ? "w" : "-");
        printf((st.st_mode & S_IXGRP) ? "x" : "-");
        printf((st.st_mode & S_IROTH) ? "r" : "-");
        printf((st.st_mode & S_IWOTH) ? "w" : "-");
        printf((st.st_mode & S_IXOTH) ? "x    " : "-    ");
        printf("\t%d ", st.st_nlink);
	tf = getpwuid(st.st_uid);
        printf("\t  %s", tf->pw_name);
 	gf = getgrgid(st.st_gid);
        printf("\t%s ", gf->gr_name);
        printf("  %zu",st.st_size);        
	printf("\t  %s", plik->d_name);
	printf("\n");
    }
    closedir(dir);
}
