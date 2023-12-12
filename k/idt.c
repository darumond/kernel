#include "idt.h"

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

extern void idt_load(uint32_t);
extern void isr0();
extern void irq0();

char *exception_messages[] =
    {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Reserved",
        "Reserved"};
void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt[num].base_low = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags | 0x60;
}

void init_pic()
{
    // ICW1 (Initialization Command Word 1)
    outb(0x20, 0x11); // Initialize master PIC
    outb(0xA0, 0x11); // Initialize slave PIC

    // ICW2 (Initialization Command Word 2)
    outb(0x21, 0x20); // Master PIC starts at IRQ 32 (0x20)
    outb(0xA1, 0x28); // Slave PIC starts at IRQ 40 (0x28)

    // ICW3 (Initialization Command Word 3)
    outb(0x21, 0x04); // Tell master PIC that there is a slave at IRQ 32
    outb(0xA1, 0x02); // Tell slave PIC its cascade identity

    // ICW4 (Initialization Command Word 4)
    outb(0x21, 0x01); // Enable 8086/88 (MCS-80/85) mode
    outb(0xA1, 0x01); // Enable 8086/88 (MCS-80/85) mode

    // MASK
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void init_idt()
{
    idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_ptr.base = (uint32_t)&idt;

    memset(&idt, 0, sizeof(idt_entry_t) * 256);
    // PIC
    // 0X20 Master commands port A
    // 0X21 Master data port B
    // 0XA0 Slave commands port A
    // 0XA1 Slave data port B

    // Init PIC
    // init_pic();
    for (size_t i = 0; i < 256; i++)
    {
        idt_set_gate(i, (unsigned)isr0, 0x08, 0x8E);
    }

    // idt_set_gate(32, (unsigned)irq0, 0x08, 0x8E);

    idt_load((uint32_t)&idt_ptr);
}
void fault_handler(int32_t num)
{

    printf("toto2\n");
    printf("%x", num);
    if (num < 32)
    {
        puts(exception_messages[num]);
        puts(" Exception. System Halted!\n");
        for (;;);
    }
}
void *irq_routines[16] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};
/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

void irq_handler(struct regs *r)
{
    /* This is a blank function pointer */
    void (*handler)(struct regs *r);

    /* Find out if we have a custom handler to run for this
     *  IRQ, and then finally, run it */
    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    /* If the IDT entry that was invoked was greater than 40
     *  (meaning IRQ8 - 15), then we need to send an EOI to
     *  the slave controller */
    if (r->int_no >= 40)
    {
        outb(0xA0, 0x20);
    }

    /* In either case, we need to send an EOI to the master
     *  interrupt controller too */
    outb(0x20, 0x20);
}