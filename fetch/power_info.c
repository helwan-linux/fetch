#include <stdio.h>

void get_battery_info(char *buffer) {
    FILE *f_cap = fopen("/sys/class/power_supply/BAT0/capacity", "r");
    FILE *f_stat = fopen("/sys/class/power_supply/BAT0/status", "r");
    
    if (!f_cap || !f_stat) {
        sprintf(buffer, "N/A (Desktop)");
        if(f_cap) fclose(f_cap);
        if(f_stat) fclose(f_stat);
        return;
    }

    int cap;
    char stat[32];
    fscanf(f_cap, "%d", &cap);
    fscanf(f_stat, "%s", stat);
    
    sprintf(buffer, "%d%% [%s]", cap, stat);
    
    fclose(f_cap);
    fclose(f_stat);
}
