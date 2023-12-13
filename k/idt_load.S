.intel_syntax noprefix

.global idt_load
.global irq0
.extern fault_handler


.macro ISR_NOERR code
    .global isr\code
    isr\code:
        CLI
        PUSH 0
        PUSH \code
        JMP isr_common
.endm

.macro ISR_ERR code
    .global isr\code
    isr\code:
        CLI
        PUSH \code
        JMP isr_common
.endm

ISR_NOERR 0
ISR_NOERR 1
ISR_NOERR 2
ISR_NOERR 3
ISR_NOERR 4
ISR_NOERR 5
ISR_NOERR 6
ISR_NOERR 7

ISR_ERR 8
ISR_NOERR 9 
ISR_ERR 10
ISR_ERR 11
ISR_ERR 12
ISR_ERR 13
ISR_ERR 14
ISR_NOERR 15
ISR_NOERR 16
ISR_NOERR 17
ISR_NOERR 18
ISR_NOERR 19
ISR_NOERR 20
ISR_NOERR 21
ISR_NOERR 22
ISR_NOERR 23
ISR_NOERR 24
ISR_NOERR 25
ISR_NOERR 26
ISR_NOERR 27
ISR_NOERR 28
ISR_NOERR 29
ISR_NOERR 30
ISR_NOERR 31


irq0:
    push 0            
    push 32
    jmp irq_common_stub

idt_load:
    mov eax, [esp+4]
    lidt [eax]
    sti
    ret

isr_common:
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

