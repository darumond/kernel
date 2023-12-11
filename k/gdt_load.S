.intel_syntax noprefix
.global gdt_load


gdt_load:
    //Switching to protected mode
    mov eax, [esp+4]
    lgdt [eax] //inform the processor that we filled the GDT

    mov eax , 0x1
    mov cr0 , eax //Set PE (Protection Enable) to 1

    mov ax, 0x10
    movw ds, ax //data selector
    movw es, ax //additional data segments available for the system programmer
    movw gs, ax //additional data segments available for the system programmer
    movw ss, ax //stack selector

    mov ax, 0x08
    movw fs, ax //additional data segments available for the system programmer

    JMP 0x08:.flush // setting code segment by far jump

.flush:
    RET