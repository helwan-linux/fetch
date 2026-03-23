#include <sys/stat.h>
#include <stdio.h>
#include <time.h>

void get_last_update(char *buffer) {
    struct stat attr;
    if (stat("/var/log/pacman.log", &attr) == 0) {
        strftime(buffer, 20, "%Y-%m-%d %H:%M", localtime(&attr.st_mtime));
    } else {
        sprintf(buffer, "Unknown");
    }
}
