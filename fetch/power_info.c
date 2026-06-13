#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

static long read_sys_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    long val;
    if (fscanf(f, "%ld", &val) != 1) val = -1;
    fclose(f);
    return val;
}

static void find_battery_path(char *path, size_t sz) {
    DIR *d = opendir("/sys/class/power_supply");
    if (!d) { path[0] = '\0'; return; }
    struct dirent *e;
    while ((e = readdir(d))) {
        if (strncmp(e->d_name, "BAT", 3) == 0) {
            snprintf(path, sz, "/sys/class/power_supply/%s", e->d_name);
            closedir(d); return;
        }
    }
    closedir(d); path[0] = '\0';
}

void get_battery_info(char *buffer) {
    char base[256];
    find_battery_path(base, sizeof(base));
    if (base[0] == '\0') { strcpy(buffer, "No Battery"); return; }

    char cap_path[300], stat_path[300], volt_path[300], thresh_path[300];
    snprintf(cap_path, sizeof(cap_path), "%s/capacity", base);
    snprintf(stat_path, sizeof(stat_path), "%s/status", base);
    snprintf(volt_path, sizeof(volt_path), "%s/voltage_now", base);
    snprintf(thresh_path, sizeof(thresh_path), "%s/charge_control_end_threshold", base);

    int cap = (int)read_sys_file(cap_path);
    long volt = read_sys_file(volt_path);
    long thresh = read_sys_file(thresh_path);

    char status[64] = "Unknown";
    FILE *f_stat = fopen(stat_path, "r");
    if (f_stat) {
        if (fgets(status, sizeof(status), f_stat))
            status[strcspn(status, "\n")] = 0;
        fclose(f_stat);
    }

    // التنسيق: النسبة [الحالة] | الجهد | حد الشحن (إذا كان مدعوماً)
    if (cap >= 0 && volt >= 0) {
        if (thresh > 0) {
            snprintf(buffer, 128, "%d%% [%s] | %.2fV | Limit: %ld%%", 
                     cap, status, (double)volt / 1000000.0, thresh);
        } else {
            snprintf(buffer, 128, "%d%% [%s] | %.2fV", cap, status, (double)volt / 1000000.0);
        }
    } else {
        strcpy(buffer, "Battery Unknown");
    }
}
