#include <sys/utsname.h>
#include <stdio.h>

void get_kernel_version(char *buffer) {
    struct utsname info;
    uname(&info);
    sprintf(buffer, "%s", info.release);
}
