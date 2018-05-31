#ifndef __NUS_MASTER_DATAHANDLE_H
#define __NUS_MASTER_DATAHANDLE_H


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "nordic_common.h"
#include "ble_db_discovery.h"




typedef enum{
	START_INDEX   = 0,					//起始索引
	DATA_LENGTH_INDIX_LOW = 1,          //数据长度地位
	DATA_LENGTH_INDIX_HIGH = 2,         //数据长度高位
    DATA_DEVICE_TYPE_INDEX = 4,			//设备类型
	DATA_DEVICE_MAC_INDEX = 5,			//设备mac 地址索引
	DATA_COMMOND_WORD = 11,             //控制字索引
	DATA_CONTENT_INDEX = 13			    //数据内容索引
	
}data_indix;







bool NUS_C_Filter_Connected_Handle(uint32_t handle);   
void nus_data_handle(uint32_t nus_c_conn_handle, uint8_t *data, uint8_t length);





#endif



