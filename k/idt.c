#include "idt.h"

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

extern void idt_load(ptr);


void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    
}

void init_idt(){

}






