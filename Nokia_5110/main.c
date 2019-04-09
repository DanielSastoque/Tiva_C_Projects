#include "PLL.h"
#include "Nokia_5110.h"
#include "SSI.h"

int main(){
    Nokia_5110_LCD_init();
    clear_all();
    set_x_y(79, 5);
    
    SSI0_write(0xF8);
    SSI0_write(0x24);
    SSI0_write(0x22);
    SSI0_write(0x24);
    SSI0_write(0xF8);
    
    while(1){
        
    }
    
    return 0;
}
