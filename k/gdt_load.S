.intel_syntax noprefix
.global gdt_flush


gdt_flush:
    //Switching to protected mode
    mov eax, [esp+4]
    lgdt [eax] //inform the processor that we filled the GDT

    mov ax, 0x10
    movw ds, ax //data selector
    movw es, ax //additional data segments available for the system programmer
    movw fs, ax //additional data segments available for the system programmer
    movw gs, ax //additional data segments available for the system programmer
    movw ss, ax

    JMP 0x08:.flush

.flush:
    RET