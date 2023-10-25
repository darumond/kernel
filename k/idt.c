#include "idt.h"

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

extern void idt_load(ptr);

void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
}

void init_idt()
{
    idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_ptr.base = &idt;

    memset(&idt, 0, sizeof(idt_entry_t) * 256);

    idt_load(&idt_ptr);
}
