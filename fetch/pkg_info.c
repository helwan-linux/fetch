// تعديل بسيط داخل pkg_info.c
#include <dirent.h>
#include <stdio.h>

int count_pacman_pkgs() {
    DIR *folder = opendir("/var/lib/pacman/local");
    if (folder == NULL) return -1; 

    int count = 0;
    struct dirent *res;
    while ((res = readdir(folder))) {
        if (res->d_type == DT_DIR && res->d_name[0] != '.') count++;
    }
    closedir(folder);
    return count - 1; 
}
