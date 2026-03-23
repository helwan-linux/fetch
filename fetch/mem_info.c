#include <stdio.h>

void get_mem_info(char *buffer) {
    long total, free, buffers, cached, reclaimable;
    FILE *f = fopen("/proc/meminfo", "r");
    if (!f) return;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "MemTotal: %ld kB", &total) == 1) continue;
        if (sscanf(line, "MemFree: %ld kB", &free) == 1) continue;
        if (sscanf(line, "Buffers: %ld kB", &buffers) == 1) continue;
        if (sscanf(line, "Cached: %ld kB", &cached) == 1) continue;
        if (sscanf(line, "SReclaimable: %ld kB", &reclaimable) == 1) continue;
    }
    fclose(f);

    long used = (total - free - buffers - cached - reclaimable) / 1024;
    sprintf(buffer, "%ld MiB / %ld MiB", used, total / 1024);
}
