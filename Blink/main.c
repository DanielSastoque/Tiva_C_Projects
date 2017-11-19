#include "led.h"

int main(){
    ledInit();

    while(1){
        ledToggle();
        delay_ms(500);
    }
    return 0;
}
