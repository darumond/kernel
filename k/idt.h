#ifndef IDT_H
#define IDT_H
#include <k/types.h>
#include "stdint.h"
#include "io.h"
#include <../../libs/libc/include/string.h>
#include <../../libs/libc/include/stdio.h>

struct idt_entry
{
    uint16_t base_low;
    uint16_t sel;    /* kernel segment*/
    uint8_t always0; /* ALWAYS set to 0! */
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));
typedef struct idt_entry idt_entry_t;

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

void init_idt();
void setIdtGates(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags);
void fault_handler(int32_t num);
void irq_install_handler(int irq, void (*handler)());

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();


extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

#endif