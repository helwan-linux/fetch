section .text
    global get_clock_cycles_asm

get_clock_cycles_asm:
    rdtsc           ; تضع النتيجة في edx:eax
    shl rdx, 32
    or rax, rdx     ; دمج النتيجة في سجل واحد 64 بت
    ret
