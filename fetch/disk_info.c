#include <sys/statvfs.h>
#include <stdio.h>

void get_disk_info(char *buffer) {
    struct statvfs ds;
    if (statvfs("/", &ds) == 0) {
        unsigned long total = (ds.f_blocks * ds.f_frsize) / (1024 * 1024 * 1024);
        unsigned long free = (ds.f_bfree * ds.f_frsize) / (1024 * 1024 * 1024);
        unsigned long used = total - free;
        sprintf(buffer, "%luG / %luG (%lu%%)", used, total, (used * 100) / total);
    }
}
