#ifndef _system_variable_h
#define _system_variable_h


#include <stdio.h>
#include <string.h>
#include "nordic_common.h"
#include "nrf.h"

typedef struct{

    uint8_t device_mac_addr[6];   //从机设备mac 地址



}_sys_work;


extern  _sys_work system_work;   //系统变量

#endif



