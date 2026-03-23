#include <stdio.h>
#include <string.h>

void get_mem_info(char *buffer) {
    // تعريف كل المتغيرات وتصفيرها لضمان عدم وجود قيم عشوائية
    long total = 0, free = 0, buffers = 0, cached = 0, reclaimable = 0;
    long s_total = 0, s_free = 0;
    
    FILE *f = fopen("/proc/meminfo", "r");
    if (!f) return;

    char line[256];
    // لفة واحدة تقرأ كل سطر وتشوف هو تبع إيه
    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "MemTotal: %ld kB", &total) == 1) continue;
        if (sscanf(line, "MemFree: %ld kB", &free) == 1) continue;
        if (sscanf(line, "Buffers: %ld kB", &buffers) == 1) continue;
        if (sscanf(line, "Cached: %ld kB", &cached) == 1) continue;
        if (sscanf(line, "SReclaimable: %ld kB", &reclaimable) == 1) continue;
        if (sscanf(line, "SwapTotal: %ld kB", &s_total) == 1) continue;
        if (sscanf(line, "SwapFree: %ld kB", &s_free) == 1) continue;
    }
    fclose(f);

    // الحسبة البرمجية الصحيحة (Used RAM = Total - (Free + Buffers + Cached + Reclaimable))
    long used = (total - free - buffers - cached - reclaimable) / 1024;
    long s_used = (s_total - s_free) / 1024;

    // طباعة النتيجة النهائية في الـ buffer
    sprintf(buffer, "%ld/%ld MiB (Swap: %ld/%ld MiB)", 
            used, total / 1024, s_used, s_total / 1024);
}
