// Run Mode Clock Gating Control Register 2
#define RCGC2 (*(volatile unsigned int*)(0x400FE000 + 0x108))

// GPIO Direction
#define GPIODIR_F (*(volatile unsigned int*)(0x40025000 + 0x400))

// GPIO Alternate Function Select
#define GPIOAFSEL_F (*(volatile unsigned int*)(0x40025000 + 0x420))

// GPIO Digital Enable
#define GPIODEN_F (*(volatile unsigned int*)(0x40025000 + 0x51C))

// GPIO Data
#define GPIODATA_F (*(volatile unsigned int*)(0x40025000 + 0x03FC))

void ledInit(){
    RCGC2       |= (1 << 5);
    GPIODIR_F   |= (1 << 1);
    GPIOAFSEL_F &= ~ 0xFF;
    GPIODEN_F   |= (1 << 1);
}

void ledToggle(){
    GPIODATA_F ^= (1 << 1);
}

#define CYCLES_PER_MS (80000)

void delay_ms(int delay){
    long volatile cycles = delay * CYCLES_PER_MS;
    while (cycles != 0){
        cycles--;
    }
}


void SystemInit(){}
