#include "Nokia_5110.h"
#include "SSI.h"
#include "SysTick.h"
#include "ADC.h"

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int main(){
    int xj = 0, yj = 0, i = 0, j = 0, jp = 0, k = 0;
    
    SysTickInit();
    Nokia_5110_LCD_init();
    clear_all();
    
    ADCO_init();
    ADC1_init();
    
    while(1){
        SysTick_delay_ms(100, 16);
        
        xj = read_ADC1();
        yj = read_ADC0();
        
        i  = 42 * (xj - 2115) / 1980 + 42;
        jp = -24 * (yj - 2079) / 2079 + 24;
        
        i  = MIN(83, MAX(0, i));
        jp = MIN(47, MAX(0, jp));
        
        j  = jp / 8;
        k  = jp % 8;
        
        clear_all();
        set_x_y(i, j);
        SSI0_write(0b11 << k);
        SSI0_write(0b11 << k);
    }
    
    return 0;
}
