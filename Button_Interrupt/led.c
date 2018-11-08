// Run Mode Clock Gating Control Register 2
#define RCGC2 (*(volatile unsigned int*)(0x400FE000 + 0x108))

// GPIO Direction
#define GPIODIR_F (*(volatile unsigned int*)(0x40025000 + 0x400))

// GPIO Alternate Function Select
#define GPIOAFSEL_F (*(volatile unsigned int*)(0x40025000 + 0x420))

// GPIO Digital Enable
#define GPIODEN_F (*(volatile unsigned int*)(0x40025000 + 0x51C))

// GPIO Data
// Modification allowed only for Pin 1 and 4 of Port F: 0x048 (mask for bit-specific addressing)
#define GPIODATA_F (*(volatile unsigned int*)(0x40025000 + 0x048))

// GPIO Pull-Up Select
#define GPIOPUR_F (*(volatile unsigned int*)(0x40025000 + 0x510))

// GPIO Interrupt Mask
#define GPIOIM_F  (*(volatile unsigned int*)(0x40025000 + 0x410))

// NVIC Interrupt 0-31 Set Enable (EN0)
#define EN0       (*(volatile unsigned int*)(0xE000E000 + 0x100))

// How to get x of PRIx, and lsb of the bit field from IRQ number?
// x = int(IRQ / 4),  lsb = 8 * IRQ - 32 * x + 5
// If  IRQ = 30 (Port F) then x = 7, lsb = 21

// NVIC Interrupt 28-31 Priority (PRI7)
#define PRI7      (*(volatile unsigned int*)(0xE000E000 + 0x41C))

// GPIO Interrupt Sense
#define GPIOIS_F  (*(volatile unsigned int*)(0x40025000 + 0x404))

// GPIO Interrupt Both Edges 
#define GPIOIBE_F (*(volatile unsigned int*)(0x40025000 + 0x408))

// GPIO Interrupt Event 
#define GPIOIEV_F (*(volatile unsigned int*)(0x40025000 + 0x40C))

// GPIO Interrupt Clear 
#define GPIOICR_F (*(volatile unsigned int*)(0x40025000 + 0x41C))

void ledInit(){
    RCGC2       |= (1 << 5);    // Enable clock for Port F (remember gating clock for energy save)
    GPIODIR_F   |= (1 << 1);    // Pin 1 of port F as output
    GPIOAFSEL_F &= 0x0;         // All Port F pins as GPIO
    GPIODEN_F   |= (1 << 1);    // Enable Pin 1 of Port F (remember tri-state logic)
}

void buttonInit(){
                                // Clock for Port F already enabled
                                // Pin 4 of port F already as input
                                // All Port F pins as GPIO
                                
    EN0         |= (1 << 30);   // Enable IRQ(30) (Port F) in NVIC
    PRI7        |= (3 << 21);   // Set priority 3 to IRQ 30 
    GPIOIS_F    &= ~(1 << 4);   // Pin 4 of Port F as edge-sensitive
    GPIOIBE_F   &= ~(1 << 4);   // Pin 4 of Port F with single edge detection
    GPIOIEV_F   |= (1 << 4);    // Pin 4 of Port F with rising edge detection
    
    GPIOPUR_F   |= (1 << 4);    // Enable weak Pull-up resitor to Pin 4 of Port F
    GPIODEN_F   |= (1 << 4);    // Enable Pin 4 of Port F (remember tri-state logic)
    
    GPIOICR_F   |= (1 << 4);    // Clear Pin 4 of Port F interrupt
    GPIOIM_F    |= (1 << 4);    // Allows interrupts in Pin 4 of Port F
}

void ledToggle(){
    GPIOICR_F  |= (1 << 4);     // Clear Pin 4 of Port F interrupt
    GPIODATA_F ^= (1 << 1);     // Switch state of Pin 1 of Port F
}
