#include "led.h"

int main(){
    ledInit();
    buttonInit();

    while(1){
        if(buttonPressed()){
            ledOn();
        }else{
            ledOff();
        }
    }
    return 0;
}
