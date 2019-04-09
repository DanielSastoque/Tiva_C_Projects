#include "PLL.h"
#include "Nokia_5110.h"
#include "SSI.h"

int main(){
    Nokia_5110_LCD_init();
    
    while(1){
        SSI0_write(0xF8);
        SSI0_write(0x24);
        SSI0_write(0x22);
        SSI0_write(0x24);
        SSI0_write(0xF8);
        SSI0_write(0x00);
        
        SSI0_write(0x70);
        SSI0_write(0xA8);
        SSI0_write(0xA8);
        SSI0_write(0xA8);
        SSI0_write(0x90);
        SSI0_write(0x00);
    }
    
    return 0;
}
