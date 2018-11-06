// SysTick Control and Status Register
#define STCTRL    (*(volatile unsigned int*)(0xE000E000 + 0x010))

// SysTick Reload Value Register
#define STRELOAD  (*(volatile unsigned int*)(0xE000E000 + 0x014))

// SysTick Current Value Register
#define STCURRENT (*(volatile unsigned int*)(0xE000E000 + 0x018))

void SysTickInit(){
    STCTRL &= ~(1 << 2); // PIOSC divided by 4 as Clock Source
    STCTRL |= (1 << 2);  // System clock as Clock Source
    STCTRL |= 1;         // Enables SysTick
}

void SysTick_delay_ms(int delay, int PLL_frec_MHz){
    STCURRENT = 0;
    STRELOAD = delay * PLL_frec_MHz * 1000 - 1;
    
    while ((STCTRL >> 16) == 0);
}
