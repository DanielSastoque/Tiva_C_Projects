// Run Mode Clock Gating Control Register 2
#define RCGC2 (*(volatile unsigned int*)(0x400FE000 + 0x108))

// GPIO Direction
#define GPIODIR_F (*(volatile unsigned int*)(0x40025000 + 0x400))

// GPIO Alternate Function Select
#define GPIOAFSEL_F (*(volatile unsigned int*)(0x40025000 + 0x420))

// GPIO Digital Enable
#define GPIODEN_F (*(volatile unsigned int*)(0x40025000 + 0x51C))

// GPIO Data
// Modification allowed only for Pin 1 of Port F: 0x008 (mask for bit-specific addressing)
#define GPIODATA_F (*(volatile unsigned int*)(0x40025000 + 0x008))

void ledInit(){
    RCGC2       |= (1 << 5);    // Enable clock for Port F (remember gating clock for energy save)
    GPIODIR_F   |= (1 << 1);    // Pin 1 of port F as output
    GPIOAFSEL_F &= 0x0;         // All Port F pins as GPIO
    GPIODEN_F   |= (1 << 1);    // Enable Pin 1 of Port F (remember tri-state logic)
}

void ledToggle(){
    GPIODATA_F ^= (1 << 1);     // Switch state of Pin 1 of Port F
}

#define CYCLES_PER_MS (1000)

void delay_ms(int delay){
    long volatile cycles = delay * CYCLES_PER_MS;
    while (cycles != 0){
        cycles--;
    }
}
