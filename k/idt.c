#include "idt.h"

idt_entry_t idt[256];
idt_ptr_t idt_ptr;

extern void idt_load(uint32_t);

char *exception_messages[] =
    {
        "Division By Zero",
        "Debug",
        "Non Maskable Interrupt",
        "Breakpoint",
        "Into Detected Overflow",
        "Out of Bounds",
        "Invalid Opcode",
        "No Coprocessor",
        "Double fault",
        "Coprocessor Segment Overrun",
        "Bad TSS",
        "Segment not present",
        "Stack fault",
        "General protection fault",
        "Page fault",
        "Unknown Interrupt",
        "Coprocessor Fault",
        "Alignment Fault",
        "Machine Check",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved",
        "Reserved"};
void setIdtGates(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
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
    outb(0x21, 0xFC);
    outb(0xA1, 0xFC);
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
    init_pic();

    setIdtGates(0, (unsigned)isr0, 0x08, 0x8E);
    setIdtGates(1, (unsigned)isr1, 0x08, 0x8E);
    setIdtGates(2, (uint32_t)isr2, 0x08, 0x8E);
    setIdtGates(3, (uint32_t)isr3, 0x08, 0x8E);
    setIdtGates(4, (uint32_t)isr4, 0x08, 0x8E);
    setIdtGates(5, (uint32_t)isr5, 0x08, 0x8E);
    setIdtGates(6, (uint32_t)isr6, 0x08, 0x8E);
    setIdtGates(7, (uint32_t)isr7, 0x08, 0x8E);
    setIdtGates(8, (uint32_t)isr8, 0x08, 0x8E);
    setIdtGates(9, (uint32_t)isr9, 0x08, 0x8E);
    setIdtGates(10, (uint32_t)isr10, 0x08, 0x8E);
    setIdtGates(11, (uint32_t)isr11, 0x08, 0x8E);
    setIdtGates(12, (uint32_t)isr12, 0x08, 0x8E);
    setIdtGates(13, (uint32_t)isr13, 0x08, 0x8E);
    setIdtGates(14, (uint32_t)isr14, 0x08, 0x8E);
    setIdtGates(15, (uint32_t)isr15, 0x08, 0x8E);
    setIdtGates(16, (uint32_t)isr16, 0x08, 0x8E);
    setIdtGates(17, (uint32_t)isr17, 0x08, 0x8E);
    setIdtGates(18, (uint32_t)isr18, 0x08, 0x8E);
    setIdtGates(19, (uint32_t)isr19, 0x08, 0x8E);
    setIdtGates(20, (uint32_t)isr20, 0x08, 0x8E);
    setIdtGates(21, (uint32_t)isr21, 0x08, 0x8E);
    setIdtGates(22, (uint32_t)isr22, 0x08, 0x8E);
    setIdtGates(23, (uint32_t)isr23, 0x08, 0x8E);
    setIdtGates(24, (uint32_t)isr24, 0x08, 0x8E);
    setIdtGates(25, (uint32_t)isr25, 0x08, 0x8E);
    setIdtGates(26, (uint32_t)isr26, 0x08, 0x8E);
    setIdtGates(27, (uint32_t)isr27, 0x08, 0x8E);
    setIdtGates(28, (uint32_t)isr28, 0x08, 0x8E);
    setIdtGates(29, (uint32_t)isr29, 0x08, 0x8E);
    setIdtGates(30, (uint32_t)isr30, 0x08, 0x8E);
    setIdtGates(31, (uint32_t)isr31, 0x08, 0x8E);

    setIdtGates(32, (uint32_t)irq0, 0x08, 0x8E);
    setIdtGates(33, (uint32_t)irq1, 0x08, 0x8E);
    setIdtGates(34, (uint32_t)irq2, 0x08, 0x8E);
    setIdtGates(35, (uint32_t)irq3, 0x08, 0x8E);
    setIdtGates(36, (uint32_t)irq4, 0x08, 0x8E);
    setIdtGates(37, (uint32_t)irq5, 0x08, 0x8E);
    setIdtGates(38, (uint32_t)irq6, 0x08, 0x8E);
    setIdtGates(39, (uint32_t)irq7, 0x08, 0x8E);
    setIdtGates(40, (uint32_t)irq8, 0x08, 0x8E);
    setIdtGates(41, (uint32_t)irq9, 0x08, 0x8E);
    setIdtGates(42, (uint32_t)irq10, 0x08, 0x8E);
    setIdtGates(43, (uint32_t)irq11, 0x08, 0x8E);
    setIdtGates(44, (uint32_t)irq12, 0x08, 0x8E);
    setIdtGates(45, (uint32_t)irq13, 0x08, 0x8E);
    setIdtGates(46, (uint32_t)irq14, 0x08, 0x8E);
    setIdtGates(47, (uint32_t)irq15, 0x08, 0x8E);
    idt_load((uint32_t)&idt_ptr);
}
void fault_handler(int32_t num)
{

    // printf("toto2\n");
    // printf("%x", num);
    if (num < 32)
    {
        puts(exception_messages[num]);
        puts(" Exception. System Halted!\n");
        for (;;)
            ;
    }
}
void *irq_routines[16] =
    {
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0};

void irq_install_handler(int irq, void (*handler)())
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

void irq_handler(int32_t num)
{
    if (num == 33)
    {
        printf("A LAIIDEEEEE \n");
    }
    // printf("IN handler %d", num);
    void (*handler)();

    handler = irq_routines[num - 32];
    if (handler)
    {
        handler();
    }

    if (num >= 40)
    {
        outb(0xA0, 0x20);
    }
    outb(0x20, 0x20);
}