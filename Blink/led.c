// Run Mode Clock Gating Control Register 2
#define RCGC2 (*(volatile unsigned int*)(0x400FE000 + 0x108))

// GPIO High-Performance Bus Control
#define GPIOHBCTL (*(volatile unsigned int*)(0x400FE000 + 0x06C))

// GPIO Alternate Function Select
#define GPIOAFSEL_F (*(volatile unsigned int*)(0x4005D000+0x420))

// GPIO Digital Enable
#define GPIODEN_F (*(volatile unsigned int*)(0x4005D000+0x51C))

// GPIO Direction
#define GPIODIR_F (*(volatile unsigned int*)(0x4005D000+0x400))

// GPIO Data
#define GPIODATA_F (*(volatile unsigned int*)(0x42000000 + 0x4))


void ledInit(){
    RCGC2     |= (1 << 5);
    GPIOHBCTL |= (1 << 5);
    GPIOAFSEL_F &= ~ 0xFF;
    GPIODIR_F |= 0x10;
    GPIODEN_F |= 0x10;
}

void ledToggle(){
    GPIODATA_F ^= 0x1;
}

#define CYCLES_PER_MS (80000)

void delay_ms(int delay){
    long volatile cycles = delay * CYCLES_PER_MS;
    while (cycles != 0){
        cycles--;
    }
}


void SystemInit(){}
