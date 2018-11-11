// Universal Asynchronous Receiver/Transmitter Run Mode Clock Gating Control 
#define RCGCUART    (*(volatile unsigned int*)(0x400FE000 + 0x618))

// Run Mode Clock Gating Control Register 2
#define RCGC2       (*(volatile unsigned int*)(0x400FE000 + 0x108))

// GPIO Alternate Function Select
#define GPIOAFSEL_E (*(volatile unsigned int*)(0x40024000 + 0x420))

// GPIO Digital Enable 
#define GPIODEN_E   (*(volatile unsigned int*)(0x40024000 + 0x51C))

// GPIO Port Control 
#define GPIOPCTL_E  (*(volatile unsigned int*)(0x40024000 + 0x52C))

// UART Control 
#define UARTCTL_5   (*(volatile unsigned int*)(0x40011000 + 0x030))

// UART Integer Baud-Rate Divisor 
#define UARTIBRD_5  (*(volatile unsigned int*)(0x40011000 + 0x024))

// UART Fractional Baud-Rate Divisor 
#define UARTFBRD_5  (*(volatile unsigned int*)(0x40011000 + 0x028))

// UART Line Control 
#define UARTLCRH_5  (*(volatile unsigned int*)(0x40011000 + 0x02C))

// UART Clock Configuration
#define UARTCC_5    (*(volatile unsigned int*)(0x40011000 + 0xFC8))

// UART Flag 
#define UARTFR_5    (*(volatile unsigned int*)(0x40011000 + 0x018))

// UART Data 
#define UARTDR_5    (*(volatile unsigned int*)(0x40011000 + 0x000))

void UART5_init(){
    RCGCUART    |= (1 << 5);   // Enable and provide a clock to UART module 5
    RCGC2       |= (1 << 4);   // Enable clock for Port E
    GPIOAFSEL_E |= (1 << 4) + 
                   (1 << 5);   // Pins 4 and 5 of Port E for alternate func
    GPIODEN_E   |= (1 << 4) + 
                   (1 << 5);   // Pins 4 and 5 of Port E as digital
    GPIOPCTL_E  |= (1 << 16) + // Pins 4 and 5 of Port E for UART
                   (1 << 20);
                   
    // BRD = UARTSysClk / (ClkDiv * Baud Rate)
    // BRD = 50E6 / (16 * 9600) = 325.5208, therefore IBRD = 325 and FBRD = 0.5208
    
    // DIVFRAC = int(FBRD * 64 + 0.5)
    // DIVFRAC = int(0.5208 * 64 + 0.5) = 33
    
    UARTCTL_5  &= ~1;        // Disable the UART by clearing the UARTEN bit
    UARTIBRD_5  = 325;       // Integer portion of the BRD
    UARTFBRD_5  = 33;        // Fractional portion of the BRD
    UARTLCRH_5 |= (0x3 << 5);// UART Word Length = 8
    UARTLCRH_5 |= (1 << 4);  // FIFO buffers are enabled
    UARTCC_5    = 0;         // System clock for UART Baud Clock Source
    UARTCTL_5  |= 1;         // Enable UART
}

void UART5_write(unsigned char text){
    while( ( (UARTFR_5 >> 5) & 1) != 0){} // Wait if the transmitter is full.
    UARTDR_5 = text;
}

unsigned char UART5_read(){
    while( ( (UARTFR_5 >> 6) & 1) != 0){} // Wait if the receiver is full.
    return (unsigned char) UARTDR_5 & 0xFF;
}
