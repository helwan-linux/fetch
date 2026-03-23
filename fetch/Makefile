# إعدادات المترجمات
CC = gcc
AS = nasm

# أعلام المترجم (CFLAGS): 
# -Wall لبيان التحذيرات، -O2 للتحسين، -no-pie لحل مشكلة الربط مع الأسمبلي
CFLAGS = -Wall -O2 -no-pie
ASFLAGS = -f elf64

# اسم البرنامج النهائي
TARGET = helfetch

# قائمة ملفات الكائنات (Objects)
# يتم إضافة أي خدمة جديدة هنا وسيتكفل الماك ببنائها تلقائياً
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

# الهدف الرئيسي (Default Target)
all: $(TARGET)

# قاعدة ربط الملفات ببعضها لإنتاج البرنامج التنفيذي
$(TARGET): $(OBJ)
	@echo "Linking all modules to create $(TARGET)..."
	$(CC) $(OBJ) -no-pie -o $(TARGET)
	@echo "Build complete! Run it with: ./$(TARGET)"

# قاعدة ذكية لتحويل أي ملف .c إلى .o
%.o: %.c
	@echo "Compiling C module: $<"
	$(CC) $(CFLAGS) -c $< -o $@

# قاعدة ذكية لتحويل أي ملف .asm إلى .o
%.o: %.asm
	@echo "Assembling ASM module: $<"
	$(AS) $(ASFLAGS) $< -o $@

# تنظيف المجلد من ملفات البناء المؤقتة
clean:
	@echo "Cleaning up object files and executable..."
	rm -f *.o $(TARGET)
	@echo "Done."

# إعادة البناء من الصفر
rebuild: clean all

.PHONY: all clean rebuild
