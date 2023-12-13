#include "serial.h"

// WHEN DLAB = 0 (Read | Write)
// PORT = RBR THR
// PORT + 1 =  IER IER
// PORT + 2 =  IIR FCR
// PORT + 3 =  LCR LCR
// PORT + 4 =  MCR MCR
// PORT + 5 =  LSR FACTORY TEST
// PORT + 6 =  MSR NOT USED
// PORT + 7 =  SCR SCR

// WHEN DLAB = 1 (Read | Write)
// PORT = DLL DLL
// PORT + 1 =  DLM DLM
// PORT + 2 =  IIR FCR
// PORT + 3 =  LCR LCR
// PORT + 4 =  MCR MCR
// PORT + 5 =  LSR FACTORY TEST
// PORT + 6 =  MSR NOT USED
// PORT + 7 =  SCR SCR

int init_serial()
{
   outb(PORT + 1, 0b00000000); // Disable all interrupts
   outb(PORT + 3, 0b10000000); // Enable DLAB (set baud rate divisor) 10000000 set DLAB to 1
   // BAUD RATE
   outb(PORT + 0, 0b00000011); // Set divisor to 3 (lo byte) 38400 baud 00000011
   outb(PORT + 1, 0b00000000); //                   (hi byte)

   outb(PORT + 3, 0b00000011); // 8 bits, no parity, one stop bit
   outb(PORT + 2, 0b11000111); // Enable FIFO, clear them, with 14-byte threshold
   outb(PORT + 4, 0b00001011); // IRQs enabled, RTS/DSR set
   outb(PORT + 4, 0b00011110); // Set in loopback mode, test the serial chip
   outb(PORT + 0, 0b10101110); // Test serial chip (send byte 0xAE and check if serial returns same byte)

   if (inb(PORT + 0) != 0xAE)
   {
      return 1;
   }

   //Turn back to normal mode
   outb(PORT + 4, 0x0F);
   return 0;
}
int is_transmit_empty()
{
   return inb(PORT + 5) & 0x20;
}

void write_serial(char a)
{
   while (is_transmit_empty() == 0)
      ;

   outb(PORT, a);
}
int write(const char *buf, size_t count)
{
   for (size_t i = 0; i < count; i++)
   {
      write_serial(buf[i]);
   }
   return count;
}