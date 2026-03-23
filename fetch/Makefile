# Helwan Linux Fetch Makefile
CC = gcc
AS = nasm
CFLAGS = -Wall -O2 -no-pie
ASFLAGS = -f elf64

# قائمة الكائنات (Objects)
OBJ = main.o \
      cpu_info.o \
      os_info.o \
      pkg_info.o \
      hw_extra.o \
      bus_info.o \
      cpu_features.o \
      mem_info.o \
      disk_info.o \
      time_info.o \
      gpu_info.o \
      power_info.o

TARGET = helfetch

# القاعدة الافتراضية
all: $(TARGET)

# الربط النهائي
$(TARGET): $(OBJ)
	@echo "Linking all high-performance modules..."
	$(CC) $(OBJ) -no-pie -o $(TARGET)
	@echo "Done! helfetch is ready."

# تجميع ملفات C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# تجميع ملفات الأسمبلي
%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

# التنظيف وإعادة البناء
clean:
	rm -f *.o $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
