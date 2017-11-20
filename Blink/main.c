#include "led.h"

int main(){
    ledInit();

    while(1){
        ledToggle();
        delay_ms(1000);
    }
    return 0;
}
