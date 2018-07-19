#include "led_control.h"




void led_init(void)
{
    GardenLight_Init(); 
    halllight_seting_init();
    curtain_init();
    clothes_shores_init();
    door_init();
    hourseholdlight_init();
    bedroomlight_init();
    studyroom_init();
}


