#include "pit.h"

uint64_t ticks;
const uint32_t freq = 100;

void onIrq0(){
    ticks += 1;
    printf("test");
}

void initPIT(){
    ticks = 0;
    irq_install_handler(0,&onIrq0);

    //119318.16666 Mhz
    uint32_t divisor = 1193180/freq;

    //0011 0110
    outb(0x43,0x36); //0X43 = Mode/Command register 0x36 = 0011 0110 -> Setting square wave generator and Channel 0 and access mode lo/hi byte
    outb(0x40,(uint8_t)(divisor & 0xFF)); //0x40 Channel 0 data port
    outb(0x40,(uint8_t)((divisor >> 8) & 0xFF)); //0x40 Channel 0 data port
}
