// Run Mode Clock Gating Control Register 2
#define RCGC2       (*(volatile unsigned int*)(0x400FE000 + 0x108))

// GPIO Direction
#define GPIODIR_A   (*(volatile unsigned int*)(0x40004000 + 0x400))

// GPIO Alternate Function Select
#define GPIOAFSEL_A (*(volatile unsigned int*)(0x40004000 + 0x420))

// GPIO Analog Mode Select 
#define GPIOAMSEL_A (*(volatile unsigned int*)(0x40004000 + 0x528))

// GPIO Digital Enable 
#define GPIODEN_A   (*(volatile unsigned int*)(0x40004000 + 0x51C))

// GPIO Port Control 
#define GPIOPCTL_A  (*(volatile unsigned int*)(0x40004000 + 0x52C))

// GPIO Data
// Modification allowed only for Pin 6 and 7 of Port A: 0x300 (mask for bit-specific addressing)
#define GPIODATA_A (*(volatile unsigned int*)(0x40004000 + 0x300))

// Already setup for system clock
#define SYS_CLK_MHZ 16
#define DELAY_DC_RST 1


#include "SSI.h"
#include "SysTick.h"

void Nokia_5110_LCD_init(){
    /*
    PA2  SSI0Clk -> CLK
    PA3  SSI0Fss -> CE
    PA4  SSI0Rx  -> -
    PA5  SSI0Tx  -> DIN
    
    PA6  -> DC
    PA7  -> RST
    */
    
    SysTickInit();
    SSI0_init();
    
    // Setup
    GPIOAMSEL_A &= ~0b11000000; // Pins 6,7 of Port A disabled for analog func
    GPIODEN_A   |= 0b11000000;  // Pins 6,7 of Port A as digital
    GPIODIR_A   |= 0b11000000;  // Pins 6,7 of Port A as output
    GPIOAFSEL_A &= ~0b11000000; // Pins 6,7 of Port A disabled for alternate func
    GPIOPCTL_A  &= ~0xFF000000; // Pins 6,7 of Port A for GPIO
    
    GPIODATA_A &= ~(1 << 7);    // Reset pulse
    SysTick_delay_ms(DELAY_DC_RST, SYS_CLK_MHZ);
    GPIODATA_A |=  (1 << 7);
    SysTick_delay_ms(DELAY_DC_RST, SYS_CLK_MHZ);
    
    GPIODATA_A &= ~(1 << 6);    // DC low, incoming SPI bits as a command.
    SysTick_delay_ms(DELAY_DC_RST, SYS_CLK_MHZ);
    
    SSI0_write(0x21);           // Select extended instruction set
    SSI0_write(0xB1);           // Set contrast
    SSI0_write(0x04);           // Set temp coefficient
    SSI0_write(0x14);           // LCD Bias mode
    SSI0_write(0x20);           // Display control
    SSI0_write(0x0C);           // Display control (Direct mode)
    
    SysTick_delay_ms(DELAY_DC_RST, SYS_CLK_MHZ);
    GPIODATA_A |= (1 << 6);     // DC high, incoming SPI bits as data to display.
}
