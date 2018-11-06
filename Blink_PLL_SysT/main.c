#include "led.h"
#include "PLL.h"
#include "SysTick.h"

int main(){
    setPLL_MHz(50);
    SysTickInit();
    ledInit();

    while(1){
        ledToggle();
        SysTick_delay_ms(30, 50);
    }
    return 0;
}
