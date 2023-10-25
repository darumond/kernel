.intel_syntax noprefix
.global gdt_load


idt_load:
    //Switching to protected mode
    mov eax, [esp+4]
    lidt [eax] //inform the processor that we filled the IDT
    ret