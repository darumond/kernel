.intel_syntax noprefix

.global idt_load
.global isr0
.global irq0
.extern fault_handler

isr0:
    PUSH 0
    PUSH 0
    jmp isr_common_stub

irq0:
    push 0            
    push 32
    jmp irq_common_stub

idt_load:
    mov eax, [esp+4]
    lidt [eax]
    sti
    ret



isr_common_stub:
    pushad
    push [esp+32]
    call fault_handler
    pop eax
    popad
    add esp, 8
    iret


.extern irq_handler
irq_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret