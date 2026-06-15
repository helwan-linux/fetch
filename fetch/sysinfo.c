#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_info(const char *path, const char *label) {
    FILE *fp = fopen(path, "r");
    if (!fp) return;

    char buffer[128];
    if (fgets(buffer, sizeof(buffer), fp)) {
        buffer[strcspn(buffer, "\n")] = 0;
        // لا تطبع إذا كانت القيمة فارغة أو تحتوي على سلسلة نصية تشير للخطأ
        if (strlen(buffer) > 0 && strcmp(buffer, "To be filled by O.E.M.") != 0) {
            printf("\033[1;34m%-15s\033[0m: %s\n", label, buffer);
        }
    }
    fclose(fp);
}

int main() {
    
    get_info("/sys/class/dmi/id/sys_vendor", "Manufacturer");
    get_info("/sys/class/dmi/id/product_name", "Model");
    return 0;
}
