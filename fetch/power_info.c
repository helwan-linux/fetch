#include <stdio.h>
#include <string.h>
#include <dirent.h>

/* -------- find battery dynamically -------- */
static void find_battery_path(char *path, size_t sz) {

    DIR *d = opendir("/sys/class/power_supply");
    if (!d) {
        path[0] = '\0';
        return;
    }

    struct dirent *e;

    while ((e = readdir(d))) {

        if (strncmp(e->d_name, "BAT", 3) == 0) {
            snprintf(path, sz,
                     "/sys/class/power_supply/%s",
                     e->d_name);
            closedir(d);
            return;
        }
    }

    closedir(d);
    path[0] = '\0';
}

/* -------- main -------- */
void get_battery_info(char *buffer) {

    char base[256];
    find_battery_path(base, sizeof(base));

    if (base[0] == '\0') {
        strcpy(buffer, "No Battery");
        return;
    }

    char cap_path[300], stat_path[300];
    int cap = -1;
    char status[64] = "Unknown";

    snprintf(cap_path, sizeof(cap_path), "%s/capacity", base);
    snprintf(stat_path, sizeof(stat_path), "%s/status", base);

    /* ---- capacity ---- */
    FILE *f1 = fopen(cap_path, "r");
    if (f1) {
        fscanf(f1, "%d", &cap);
        fclose(f1);
    }

    /* ---- status (FIXED) ---- */
    FILE *f2 = fopen(stat_path, "r");
    if (f2) {
        fgets(status, sizeof(status), f2);
        fclose(f2);
        status[strcspn(status, "\n")] = 0;
    }

    /* ---- output ---- */
    if (cap >= 0)
        snprintf(buffer, 64, "%d%% [%s]", cap, status);
    else
        strcpy(buffer, "Battery Unknown");
}
