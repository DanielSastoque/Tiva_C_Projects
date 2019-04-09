// Synchronous Serial Interface Run Mode Clock Gating Control
#define RCGCSSI     (*(volatile unsigned int*)(0x400FE000 + 0x61C))

// Run Mode Clock Gating Control Register 2
#define RCGC2       (*(volatile unsigned int*)(0x400FE000 + 0x108))

// GPIO Alternate Function Select
#define GPIOAFSEL_A (*(volatile unsigned int*)(0x40004000 + 0x420))

// GPIO Analog Mode Select 
#define GPIOAMSEL_A (*(volatile unsigned int*)(0x40004000 + 0x528))

// GPIO Digital Enable 
#define GPIODEN_A   (*(volatile unsigned int*)(0x40004000 + 0x51C))

// GPIO Port Control 
#define GPIOPCTL_A  (*(volatile unsigned int*)(0x40004000 + 0x52C))

// SSI Control 1 
#define SSICR1_0    (*(volatile unsigned int*)(0x40008000 + 0x004))

// SSI Clock Configuration 
#define SSICC_0     (*(volatile unsigned int*)(0x40008000 + 0xFC8))

// SSI Clock Prescale 
#define SSICPSR_0   (*(volatile unsigned int*)(0x40008000 + 0x010))

// SSI Control 0 
#define SSICR0_0    (*(volatile unsigned int*)(0x40008000 + 0x000))

// SSI Data 
#define SSIDR_0     (*(volatile unsigned int*)(0x40008000 + 0x008))

// SSI Status 
#define SSISR_0     (*(volatile unsigned int*)(0x40008000 + 0x00C))


void SSI0_init(){
    /*
    PA2  SSI0Clk
    PA3  SSI0Fss
    PA4  SSI0Rx
    PA5  SSI0Tx
    */
    
    RCGCSSI     |= 1;          // Enable and provide a clock to SSI module
    RCGC2       |= 1;          // Enable clock for Port A
    
    GPIOAFSEL_A |= 0b00111100; // Pins 2-5 of Port A for alternate func
    GPIOAMSEL_A &= ~0b00111100;// Pins 2-5 of Port A disabled for analog func
    GPIODEN_A   |= 0b00111100; // Pins 2-5 of Port A as digital
    
    GPIOPCTL_A  |= 0x00202200; // Pins 2-5 of Port A for SSI
    
    SSICR1_0    &= ~(1 << 1);  // SSI0 operation is disabled
    SSICR1_0    &= ~(1 << 2);  // Select SSI0 is a master
    SSICC_0      = 0;          // System clock for SSI0 Baud Clock Source
    
    // SSInClk = SysClk / (CPSDVSR * (1 + SCR))
    // SSInClk = 16E6 / (4 * (1 + 1)) = 70 KHz (Bit rate)
    SSICPSR_0 = 76;            // SSI Clock Prescale Divisor, CPSDVSR = 2
    SSICR0_0 |= (2 << 8);      // SSI Serial Clock Rate, SCR = 1
    
    SSICR0_0 |= 0x7;           // Data Size = 8-bit data
    SSICR0_0 &= ~(0b11 << 4);  // Freescale SPI Frame Format
    SSICR1_0 |= (1 << 1);      // SSI0 operation is enabled
}

void SSI0_write(unsigned int text){
    while( ( ~(SSISR_0 >> 1) & (SSISR_0 >> 4) & 1) != 0){} // Wait if the transmitter is full.
    SSIDR_0 = 0xFF & text;
    while( ( ~(SSISR_0 >> 1) & (SSISR_0 >> 4) & 1) != 0){} // Wait if the transmitter is full.    
}
