#include <stdio.h>

float get_cpu_temp() {
    FILE *f = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
    if (!f) return 0.0;
    int temp;
    fscanf(f, "%d", &temp);
    fclose(f);
    return temp / 1000.0; // تحويل من ملي درجة مئوية
}
