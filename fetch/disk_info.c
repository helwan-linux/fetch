#include <sys/statvfs.h>
#include <stdio.h>

void get_disk_info(char *buffer) {
    struct statvfs ds;

    if (statvfs("/", &ds) != 0) {
        snprintf(buffer, 128, "Disk: N/A");
        return;
    }

    unsigned long long total = (unsigned long long)ds.f_blocks * ds.f_frsize;
    unsigned long long avail  = (unsigned long long)ds.f_bavail * ds.f_frsize;
    unsigned long long used   = total - avail;

    unsigned long total_gb = total / (1024ULL * 1024 * 1024);
    unsigned long used_gb  = used  / (1024ULL * 1024 * 1024);
    unsigned long free_gb  = avail / (1024ULL * 1024 * 1024);
    
    unsigned long percent = (total > 0) ? (unsigned long)((used * 100) / total) : 0;

    /* التنسيق الجديد يضيف المساحة الحرة (Free) */
    snprintf(buffer, 128, "%luG used / %luG total (%lu%%) | %luG free", 
             used_gb, total_gb, percent, free_gb);
}
