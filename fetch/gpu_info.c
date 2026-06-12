#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define OUT 2048

static void trim(char *s) {
    s[strcspn(s, "\n")] = 0;
}

static int read_file(const char *path, char *buf, size_t sz) {
    FILE *f = fopen(path, "r");
    if (!f) return 0;

    if (!fgets(buf, sz, f)) {
        fclose(f);
        return 0;
    }

    fclose(f);
    trim(buf);
    return 1;
}

/* ---------------- GPU NAME (REALISTIC) ---------------- */
static void gpu_name(const char *card, char *out) {

    char path[256], buf[256];

    snprintf(path, sizeof(path),
             "/sys/class/drm/%s/device/uevent",
             card);

    FILE *f = fopen(path, "r");
    if (!f) {
        strcpy(out, "GPU");
        return;
    }

    while (fgets(buf, sizeof(buf), f)) {

        if (strncmp(buf, "DRIVER=", 7) == 0) {

            if (strstr(buf, "i915"))
                strcpy(out, "Intel Graphics");
            else if (strstr(buf, "amdgpu"))
                strcpy(out, "AMD Graphics");
            else if (strstr(buf, "nvidia"))
                strcpy(out, "NVIDIA Graphics");
            else
                strcpy(out, "GPU");

            fclose(f);
            return;
        }
    }

    fclose(f);
    strcpy(out, "GPU");
}

/* ---------------- MEMORY (ONLY WHAT EXISTS) ---------------- */
static void gpu_mem(const char *card, char *out) {

    char path[256];
    int v;

    snprintf(path, sizeof(path),
             "/sys/class/drm/%s/device/mem_info_vram_total",
             card);

    FILE *f = fopen(path, "r");
    if (f && fscanf(f, "%d", &v) == 1) {
        fclose(f);
        snprintf(out, 64, "%d MB VRAM", v / 1024 / 1024);
        return;
    }
    if (f) fclose(f);

    strcpy(out, "Shared Memory (UMA)");
}

/* ---------------- TEMP (BEST EFFORT ONLY) ---------------- */
static void gpu_temp(const char *card, char *out) {

    char base[256];
    snprintf(base, sizeof(base),
             "/sys/class/drm/%s/device/hwmon",
             card);

    DIR *d = opendir(base);
    if (!d) {
        strcpy(out, "N/A");
        return;
    }

    struct dirent *e;
    char path[256];

    while ((e = readdir(d))) {

        if (strncmp(e->d_name, "hwmon", 5) != 0)
            continue;

        snprintf(path, sizeof(path),
                 "%s/%s/temp1_input",
                 base, e->d_name);

        FILE *f = fopen(path, "r");
        if (f) {
            int t;
            if (fscanf(f, "%d", &t) == 1) {
                fclose(f);
                closedir(d);
                snprintf(out, 32, "%.1f°C", t / 1000.0);
                return;
            }
            fclose(f);
        }
    }

    closedir(d);
    strcpy(out, "N/A");
}

/* ---------------- MAIN ---------------- */
void get_gpu_info(char *buffer) {

    DIR *d = opendir("/sys/class/drm");
    if (!d) {
        strcpy(buffer, "GPU not detected");
        return;
    }

    struct dirent *e;
    char final[OUT];
    final[0] = '\0';

    while ((e = readdir(d))) {

        if (strncmp(e->d_name, "card", 4))
            continue;

        if (strchr(e->d_name, '-'))
            continue;

        char name[128], mem[64], temp[32], line[256];

        gpu_name(e->d_name, name);
        gpu_mem(e->d_name, mem);
        gpu_temp(e->d_name, temp);

        /* clean stable formatting */
        if (strcmp(temp, "N/A") == 0) {
            snprintf(line, sizeof(line),
                     "%s (%s)",
                     name, mem);
        } else {
            snprintf(line, sizeof(line),
                     "%s (%s, Temp: %s)",
                     name, mem, temp);
        }

        if (final[0] != '\0')
            strncat(final, " | ", OUT - strlen(final) - 1);

        strncat(final, line, OUT - strlen(final) - 1);
    }

    closedir(d);

    if (final[0] == '\0')
        strcpy(buffer, "GPU not detected");
    else
        strcpy(buffer, final);
}
