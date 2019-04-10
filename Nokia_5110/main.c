#include "PLL.h"
#include "Nokia_5110.h"
#include "SSI.h"
#include "SysTick.h"

#include "IMAGE.h"

int main(){
    Nokia_5110_LCD_init();
    clear_all();
    
    while(1){
        draw_image(daniel);
        SysTick_delay_ms(5000, 16);
        draw_image(stark);
        SysTick_delay_ms(5000, 16);
    }
    
    return 0;
}
