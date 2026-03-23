section .text
    global get_cpu_brand_asm

get_cpu_brand_asm:
    push rbx            ; الحفاظ على قيمة rbx
    mov rax, 0x80000002 ; الوظيفة الأولى لاسم المعالج
    cpuid
    mov [rdi], eax
    mov [rdi+4], ebx
    mov [rdi+8], ecx
    mov [rdi+12], edx
    
    mov rax, 0x80000003 ; الوظيفة الثانية
    cpuid
    mov [rdi+16], eax
    mov [rdi+20], ebx
    mov [rdi+24], ecx
    mov [rdi+28], edx
    
    mov rax, 0x80000004 ; الوظيفة الثالثة
    cpuid
    mov [rdi+32], eax
    mov [rdi+36], ebx
    mov [rdi+40], ecx
    mov [rdi+44], edx
    
    pop rbx
    ret
