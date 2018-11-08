#include "led.h"

int main(){
    ledInit();
    buttonInit();
    EnableInterrupts();

    WaitForInterrupt();
    return 0;
}
