# المترجمات
CC = gcc
AS = nasm

# الإعدادات: -no-pie ضروري لربط الأسمبلي بنجاح في التوزيعات الحديثة
CFLAGS = -Wall -O2 -no-pie
ASFLAGS = -f elf64

# قائمة ملفات الـ Objects (كل ميزة في ملف)
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

# الهدف الافتراضي
all: $(TARGET)

# ربط كل الوحدات لإنتاج البرنامج النهائي
$(TARGET): $(OBJ)
	@echo "Linking all modules for Helwan Linux..."
	$(CC) $(OBJ) -no-pie -o $(TARGET)
	@echo "Success! Run with ./helfetch"

# قاعدة بناء ملفات C
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# قاعدة بناء ملفات Assembly
%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

# التنظيف
clean:
	rm -f *.o $(TARGET)

# إعادة بناء شاملة
rebuild: clean all

.PHONY: all clean rebuild
