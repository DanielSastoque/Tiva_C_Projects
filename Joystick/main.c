#include "Nokia_5110.h"
#include "SSI.h"
#include "SysTick.h"
#include "ADC.h"


int main(){
    SysTickInit();
    Nokia_5110_LCD_init();
    clear_all();
    
    ADCO_init();
    ADC1_init();
    
    while(1){
        SysTick_delay_ms(100, 16);
        if(read_ADC0() > 3080){
            SSI0_write(0xFF);
        }
        if(read_ADC1() > 3080){
            SSI0_write(0xF0);
        }
    }
    
    return 0;
}
