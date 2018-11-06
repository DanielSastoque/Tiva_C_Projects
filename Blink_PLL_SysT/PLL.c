// Run-Mode Clock Configuration 2
#define RCC2 (*(volatile unsigned int*)(0x400FE000 + 0x070))

// Run-Mode Clock Configuration 
#define RCC  (*(volatile unsigned int*)(0x400FE000 + 0x060))

// Raw Interrupt Status
#define RIS  (*(volatile unsigned int*)(0x400FE000 + 0x050))

void PLL_Init(int divider){
    RCC2 |= (0b11 << 30);// Use RCC2 instead RCC, and 400 MHz
    RCC2 |= (1 << 11);   // The system clock is derived from the OSC source 
                         // and divided by the divisor specified.
    RCC  |= (0x15 << 6); // Value of Crystal attached to the main oscillator (16 MHz).
    RCC2 &= ~(1 << 13);  // The PLL turns on.
    
    RCC2 &= ~(0x7F << 22);   // Clear bits of divider
    RCC2 |= (divider << 22); // Set the desired system divider (PLL MHz / (7 + 1)).
    
    while(((RIS >> 6) & 1) == 0); // Wait until PLL gets ready.
    RCC2 &= ~(1 << 11);  // The system clock is the PLL output clock divided by 
                         // the divisor specified.
}

void setPLL_MHz(int frecuency){
    int divider = 400 / frecuency;
    PLL_Init(divider);
}
