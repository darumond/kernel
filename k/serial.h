#ifndef SERIAL_H
#define SERIAL_H

#define PORT 0x3f8 // COM1

#include "io.h"

int init_serial();

int is_transmit_empty();

void write_serial(char a);

int write(const char *buf, size_t count);


#endif