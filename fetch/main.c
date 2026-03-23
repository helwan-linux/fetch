#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// تعريف كل الدوال الخارجية من الملفات المنفصلة
extern int count_pacman_pkgs();
extern float get_cpu_temp();
extern void get_kernel_version(char *buffer);
extern void get_cpu_brand_asm(char *buffer);
extern void get_cpu_features_asm(char *buffer);
extern void get_mem_info(char *buffer);
extern void get_disk_info(char *buffer);
extern void get_uptime_info(char *buffer);
extern void get_gpu_info(char *buffer);
extern void get_battery_info(char *buffer);

// الدوال الجديدة المتقدمة
void get_entropy(char *buffer) {
    FILE *f = fopen("/proc/sys/kernel/random/entropy_avail", "r");
    if (f) {
        int val;
        if (fscanf(f, "%d", &val) == 1) sprintf(buffer, "%d bits", val);
        fclose(f);
    } else strcpy(buffer, "N/A");
}

void get_microcode(char *buffer) {
    FILE *f = fopen("/proc/cpuinfo", "r");
    if (f) {
        char line[256];
        while (fgets(line, sizeof(line), f)) {
            if (strncmp(line, "microcode", 9) == 0) {
                char *ptr = strchr(line, ':');
                if (ptr) {
                    strcpy(buffer, ptr + 2);
                    buffer[strcspn(buffer, "\n")] = 0;
                    fclose(f);
                    return;
                }
            }
        }
        fclose(f);
    }
    strcpy(buffer, "Unknown");
}

int main() {
    char cpu[49], kernel[64], features[128], mem[64], disk[64];
    char uptime[64], gpu[64], bat[64], entropy[32], microcode[32];
    
    // جلب البيانات من كل الوحدات
    get_cpu_brand_asm(cpu);
    get_kernel_version(kernel);
    get_cpu_features_asm(features);
    get_mem_info(mem);
    get_disk_info(disk);
    get_uptime_info(uptime);
    get_gpu_info(gpu);
    get_battery_info(bat);
    get_entropy(entropy);
    get_microcode(microcode);

    // تنظيف النصوص
    gpu[strcspn(gpu, "\n")] = 0;
    char *trimmed_cpu = cpu;
    while (*trimmed_cpu == ' ') trimmed_cpu++;

    // واجهة العرض النهائية - "مسطرة" حلوان لينكس
    printf("\n");
    printf("\033[1;34m       _   _      \033[1;33m OS:       \033[0mHelwan Linux\n");
    printf("\033[1;34m      | | | |     \033[1;33m Kernel:   \033[0m%s\n", kernel);
    printf("\033[1;34m      | |_| |     \033[1;33m Uptime:   \033[0m%s\n", uptime);
    printf("\033[1;34m      |  _  |     \033[1;33m Packages: \033[0m%d (pacman)\n", count_pacman_pkgs());
    printf("\033[1;34m      | | | |     \033[1;33m RAM:      \033[0m%s\n", mem);
    printf("\033[1;34m      | | | |     \033[1;33m Disk:     \033[0m%s\n", disk);
    printf("\033[1;34m      |_| |_|     \033[1;33m CPU:      \033[0m%s\n", trimmed_cpu);
    printf("\033[1;34m                  \033[1;33m GPU:      \033[0m%s\n", gpu);
    printf("\033[1;34m                  \033[1;33m Features: \033[0m%s\n", features[0] ? features : "Standard x86_64");
    printf("\033[1;34m                  \033[1;33m Microcode:\033[0m %s\n", microcode);
    printf("\033[1;34m                  \033[1;33m Entropy:  \033[0m%s\n", entropy);
    printf("\033[1;34m                  \033[1;33m Battery:  \033[0m%s\n", bat);
    printf("\033[1;34m                  \033[1;33m Temp:     \033[0m%.1f°C\n", get_cpu_temp());
    
    // لوحة الألوان المحترفة
    printf("\n                  ");
    for (int i = 0; i < 8; i++) printf("\033[4%dm   ", i); 
    printf("\033[0m\n                  ");
    for (int i = 0; i < 8; i++) printf("\033[10%dm   ", i);
    printf("\033[0m\n\n");

    return 0;
}
