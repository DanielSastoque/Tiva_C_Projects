#include "led.h"
#include "PLL.h"
#include "UART.h"

int main(){
    setPLL_MHz(50);
    ledInit();
    UART5_init();

    while(1){
        if(UART5_read() == '1'){
            ledToggle();
            UART5_write('!');
        }
    }
    return 0;
}
