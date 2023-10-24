#include "gdt.h"

extern void gdt_flush(uint32_t ptr);

static gdt_entry_t gdt_entries[5];
static gdt_ptr_t gdt_ptr;

void init_gdt()
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 6) - 1;
    gdt_ptr.base = (uint32_t)&gdt_entries;
    setGate(0, 0, 0, 0, 0);                
    setGate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    setGate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    setGate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    setGate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_flush((uint32_t)&gdt_ptr);
}

void setGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit= (limit & 0xFFFF);
    gdt_entries[num].flags = (limit >> 16) & 0x0F;

    gdt_entries[num].flags |= gran & 0xF0;
    gdt_entries[num].access = access;
}