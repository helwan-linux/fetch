section .text
    global get_cpu_features_asm

get_cpu_features_asm:
    push rbx
    push rdi
    
    mov r8, rdi             ; Tracking pointer
    mov byte [r8], 0        ; Init empty string

    ; Get Standard Features
    mov eax, 1
    cpuid
    mov r10d, ecx           ; Features in ECX
    mov r11d, edx           ; Features in EDX

    ; SSE4.2 (Bit 20 of ECX)
    test r10d, (1 << 20)
    jz .skip_sse42
    lea rsi, [rel str_sse42] ; استخدام rel للإشارة للعناوين النسبية
    mov edx, len_sse42
    call append_string
.skip_sse42:

    ; AES (Bit 25 of ECX)
    test r10d, (1 << 25)
    jz .skip_aes
    lea rsi, [rel str_aes]
    mov edx, len_aes
    call append_string
.skip_aes:

    ; AVX (Bit 28 of ECX)
    test r10d, (1 << 28)
    jz .skip_avx
    lea rsi, [rel str_avx]
    mov edx, len_avx
    call append_string
.skip_avx:

    ; Get Extended Features
    mov eax, 7
    xor ecx, ecx
    cpuid
    ; SHA (Bit 29 of EBX)
    test ebx, (1 << 29)
    jz .skip_sha
    lea rsi, [rel str_sha]
    mov edx, len_sha
    call append_string
.skip_sha:

    pop rdi
    pop rbx
    ret

append_string:
    cmp byte [rdi], 0
    je .copy
    mov byte [rdi], ','
    inc rdi
    mov byte [rdi], ' '
    inc rdi
.copy:
    mov rcx, rdx
    rep movsb
    mov byte [rdi], 0 ; Null terminate
    ret

section .rodata
    str_sse42  db "SSE4.2"
    len_sse42  equ $ - str_sse42
    str_aes    db "AES"
    len_aes    equ $ - str_aes
    str_avx    db "AVX"
    len_avx    equ $ - str_avx
    str_sha    db "SHA"
    len_sha    equ $ - str_sha
