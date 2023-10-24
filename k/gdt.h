#ifndef GDT_H
#define GDT_H
#include <k/types.h>
#include <stdio.h>
#include <string.h>
#include "stdint.h"
// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
   uint16_t limit;
   uint16_t base_low;
   uint8_t base_middle;
   uint8_t access;
   uint8_t flags;
   uint8_t base_high;
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
   uint16_t limit;               // The upper 16 bits of all selector limits.
   unsigned int base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

void init_gdt();
void setGate(uint32_t num,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran );

#endif