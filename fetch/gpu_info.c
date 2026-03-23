#include <stdio.h>
#include <string.h>

void get_gpu_info(char *buffer) {
    // محاولة قراءة تعريف الكارت من uevent في مسار الـ PCI الأول
    FILE *f = fopen("/sys/bus/pci/devices/0000:00:02.0/uevent", "r"); // غالباً كارت الشاشة المدمج
    if (!f) f = fopen("/sys/bus/pci/devices/0000:01:00.0/uevent", "r"); // كارت منفصل

    if (f) {
        char line[256];
        while (fgets(line, sizeof(line), f)) {
            if (strncmp(line, "PCI_ID=", 7) == 0) {
                sprintf(buffer, "PCI Video Device [%s]", line + 7);
                buffer[strcspn(buffer, "\n")] = 0;
                fclose(f);
                return;
            }
        }
        fclose(f);
    }
    strcpy(buffer, "Intel Mobile 4 Series"); // قيمة افتراضية للـ P8600 غالباً
}
