#ifndef __led_control_h
#define __led_control_h


#include <stdint.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"
#include "ble_hci.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_gpio.h"



//花园灯初始化
#define GardenLight_Init()  do{\
nrf_gpio_cfg_output(18);\
}while(0)

//花园灯开关
#define GardenLight_on()  do{\
nrf_gpio_pin_set(18);\
}while(0)

#define GardenLight_off()  do{\
nrf_gpio_pin_clear(18);\
}while(0)


//大厅灯 
#define halllight_seting_init() do{\
nrf_gpio_cfg_output(22);\
}while(0)

#define halllight_on()  do{\
nrf_gpio_pin_set(22);\
}while(0)

#define hallight_off()  do{\
nrf_gpio_pin_clear(22);\
}while(0)



//窗帘

#define curtain_init() do{\
nrf_gpio_cfg_output(26);\
}while(0)

#define curtain_on()  do{\
nrf_gpio_pin_set(26);\
}while(0)

#define curtain_off()  do{\
nrf_gpio_pin_clear(26);\
}while(0)


//晾衣架

#define clothes_shores_init() do{\
nrf_gpio_cfg_output(2);\
}while(0)

#define clothes_shores_on()  do{\
nrf_gpio_pin_set(2);\
}while(0)

#define clothes_shores_off()  do{\
nrf_gpio_pin_clear(2);\
}while(0)


//设备大门

#define door_init() do{\
nrf_gpio_cfg_output(25);\
}while(0)

#define door_on()  do{\
nrf_gpio_pin_set(25);\
}while(0)

#define door_off()  do{\
nrf_gpio_pin_clear(25);\
}while(0)


//入户灯

#define hourseholdlight_init() do{\
nrf_gpio_cfg_output(24);\
}while(0)

#define hourseholdlight_on()  do{\
nrf_gpio_pin_set(24);\
}while(0)

#define hourseholdlight_off()  do{\
nrf_gpio_pin_clear(24);\
}while(0)


//卧室灯

#define bedroomlight_init() do{\
nrf_gpio_cfg_output(20);\
}while(0)

#define bedroomlight_on()  do{\
nrf_gpio_pin_set(20);\
}while(0)

#define bedroomlight_off()  do{\
nrf_gpio_pin_clear(20);\
}while(0)


//书房

#define studyroom_init() do{\
nrf_gpio_cfg_output(19);\
}while(0)

#define studyroom_on()  do{\
nrf_gpio_pin_set(19);\
}while(0)

#define studyroom_off()  do{\
nrf_gpio_pin_clear(19);\
}while(0)



void  led_init(void);



#endif



