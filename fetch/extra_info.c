#include <stdio.h>
#include <string.h>

// جلب العشوائية المتوفرة في النظام (Entropy)
void get_entropy(char *buffer) {
    FILE *f = fopen("/proc/sys/kernel/random/entropy_avail", "r");
    if (!f) return;
    int val;
    fscanf(f, "%d", &val);
    fclose(f);
    sprintf(buffer, "%d bits", val);
}

// جلب إصدار المايكروكود للمعالج
void get_microcode(char *buffer) {
    FILE *f = fopen("/proc/cpuinfo", "r");
    if (!f) return;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "microcode", 9) == 0) {
            char *ptr = strchr(line, ':');
            if (ptr) {
                sprintf(buffer, "%s", ptr + 2);
                buffer[strcspn(buffer, "\n")] = 0;
                break;
            }
        }
    }
    fclose(f);
}
