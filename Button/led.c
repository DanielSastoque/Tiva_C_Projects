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
    GPIOPUR_F   |= (1 << 4);    // Enable weak Pull-up resitor to Pin 4 of Port F
    GPIODEN_F   |= (1 << 4);    // Enable Pin 4 of Port F (remember tri-state logic)
}

void ledOff(){
    GPIODATA_F &= ~(1 << 1);    // Set 0 to Pin 1 of Port F
}

void ledOn(){
    GPIODATA_F |= (1 << 1);     // Set 1 to Pin 1 of Port F
}

int buttonPressed(){
    int status = (GPIODATA_F & (1 << 4)) == 0;  // Check if Pin 4 of Port F has send to ground
    return status; 
}
