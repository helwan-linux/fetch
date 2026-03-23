#include <stdio.h>
#include <sys/sysinfo.h>

void get_uptime_info(char *buffer) {
    struct sysinfo info;
    sysinfo(&info);
    int h = info.uptime / 3600;
    int m = (info.uptime % 3600) / 60;
    sprintf(buffer, "%d hours, %d mins", h, m);
}
