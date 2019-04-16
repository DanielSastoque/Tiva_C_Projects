// Analog-to-Digital Converter Run Mode Clock Gating Control
#define RCGCADC       (*(volatile unsigned int*)(0x400FE000 + 0x638))

// General-Purpose Input/Output Run Mode Clock Gating Control
#define RCGCGPIO      (*(volatile unsigned int*)(0x400FE000 + 0x608))

// GPIO Alternate Function Select
#define GPIOAFSEL_E   (*(volatile unsigned int*)(0x40024000 + 0x420))

// GPIO Digital Enable
#define GPIODEN_E     (*(volatile unsigned int*)(0x40024000 + 0x51C))

// GPIO Analog Mode Select
#define GPIOAMSEL_E   (*(volatile unsigned int*)(0x40024000 + 0x528))

// ADC Active Sample Sequencer ADC0
#define ADCACTSS_0    (*(volatile unsigned int*)(0x40038000))

// ADC Active Sample Sequencer ADC1
#define ADCACTSS_1    (*(volatile unsigned int*)(0x40039000))

// ADC Event Multiplexer Select ADC0
#define ADCEMUX_0     (*(volatile unsigned int*)(0x40038000 + 0x014))

// ADC Event Multiplexer Select ADC1
#define ADCEMUX_1     (*(volatile unsigned int*)(0x40039000 + 0x014))

// ADC Sample Sequence Input Multiplexer Select 3 ADC0
#define ADCSSMUX3_0   (*(volatile unsigned int*)(0x40038000 + 0x0A0))

// ADC Sample Sequence Input Multiplexer Select 3 ADC1
#define ADCSSMUX3_1   (*(volatile unsigned int*)(0x40039000 + 0x0A0))

// ADC Sample Sequence Control 3 ADC0
#define ADCSSCTL3_0   (*(volatile unsigned int*)(0x40038000 + 0x0A4))

// ADC Sample Sequence Control 3 ADC1
#define ADCSSCTL3_1   (*(volatile unsigned int*)(0x40039000 + 0x0A4))

// ADC Sample Sequence FIFO 3 Status ADC0
#define ADCSSFSTAT3_0 (*(volatile unsigned int*)(0x40038000 + 0x0AC))

// ADC Sample Sequence FIFO 3 Status ADC1
#define ADCSSFSTAT3_1 (*(volatile unsigned int*)(0x40039000 + 0x0AC))

// ADC Sample Sequence Result FIFO 3 Status ADC0
#define ADCSSFIFO3_0  (*(volatile unsigned int*)(0x40038000 + 0x0A8))

// ADC Sample Sequence Result FIFO 3 Status ADC1
#define ADCSSFIFO3_1  (*(volatile unsigned int*)(0x40039000 + 0x0A8))


void ADCO_init(){
    /*
    PE3 -> AIN0
    */
    
    RCGCADC     |= 1;             // Enable the ADC clock
    RCGCGPIO    |= (1 << 4);      // Enable and provide a clock to GPIO Port E
    
    GPIOAFSEL_E |= (1 << 3);      // PE3 Alternate hardware function
    GPIODEN_E   &= ~(1 << 3);     // PE3 Digital functions disabled
    GPIOAMSEL_E |= (1 << 3);      // PE3 Analog function enabled
    
    ADCACTSS_0  &= ~(1 << 3);     // Sample Sequencer 3 (SS3) is disabled
    ADCEMUX_0   |= (0xF << 12);   // Trigger for SS3: Always (continuously sample)
    ADCSSMUX3_0  = 0x0;           // Using SS3, samples come from AIN0
    ADCSSCTL3_0  = 0x2;           // Using SS3, sample is end of sequence, no temp sensor, 
                                  // no differential input, no interrupts
    ADCACTSS_0  |= (1 << 3);      // Sample Sequencer 3 (SS3) is enabled
}

void ADC1_init(){
    /*
    PE2 -> AIN1
    */
    
    RCGCADC     |= 0b10;          // Enable the ADC clock
    RCGCGPIO    |= (1 << 4);      // Enable and provide a clock to GPIO Port E
    
    GPIOAFSEL_E |= (1 << 2);      // PE2 Alternate hardware function
    GPIODEN_E   &= ~(1 << 2);     // PE2 Digital functions disabled
    GPIOAMSEL_E |= (1 << 2);      // PE2 Analog function enabled
    
    ADCACTSS_1  &= ~(1 << 3);     // Sample Sequencer 3 (SS3) is disabled
    ADCEMUX_1   |= (0xF << 12);   // Trigger for SS3: Always (continuously sample)
    ADCSSMUX3_1  = 0x1;           // Using SS3, samples come from AIN1
    ADCSSCTL3_1  = 0x2;           // Using SS3, sample is end of sequence, no temp sensor, 
                                  // no differential input, no interrupts
    ADCACTSS_1  |= (1 << 3);      // Sample Sequencer 3 (SS3) is enabled
}


int read_ADC0(){
    while( ( (ADCSSFSTAT3_0 >> 8) & 1) != 0){} // Wait if buffer is empty
    return ADCSSFIFO3_0;
}

int read_ADC1(){
    while( ( (ADCSSFSTAT3_1 >> 8) & 1) != 0){} // Wait if buffer is empty
    return ADCSSFIFO3_1;
}
