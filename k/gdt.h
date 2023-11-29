#ifndef GDT_H
#define GDT_H
#include <k/types.h>
#include "stdint.h"
struct gdt_entry_struct
{
   uint16_t limit; //2 octets
   uint16_t base_low; //2
   uint8_t base_middle; //1
   uint8_t access; //1
   uint8_t flags; //1
   uint8_t base_high; //1
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
   uint16_t limit;
   unsigned int base;
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

void init_gdt();
void setGate(uint32_t num,uint32_t base,uint32_t limit,uint8_t access,uint8_t gran );

#endif